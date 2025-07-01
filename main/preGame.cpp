
#include "preGame.h"



PreGame::PreGame(): state(WAITING_FOR_START), led_matrix(nullptr), maze_maps(nullptr), start_button(nullptr), 
                    m_participating_mask(0), m_map_id(-1), m_should_start(false), timeout(REPLY_TIMEOUT), tick(0){}

void PreGame::setup(LedMatrix* matrix, MazeMaps* mazes, Button* button){
    led_matrix = matrix;
    maze_maps = mazes;
    start_button = button;
    for (int x = 0; x < 16; ++x)
    for (int y = 0; y < 16; ++y)
    brightness[x][y] = 0;
}

void PreGame::update(int dt) {

    
    // ========== Handle Display ==========
    tick += dt;
    // Randomly light up a pixel
    if (tick % 500 == 0) {  // Adjust frequency
        int x = rand() % 16;
        int y = rand() % 16;
        brightness[x][y] = 255;
        // Convert brightness to color (white-ish)
        uint8_t val = brightness[x][y];
        uint32_t color = val;
        led_matrix->setPixelColor(x, y, color);
    }
    
    // Update pixels
    if(tick > 1000){
        for (int x = 0; x < 16; ++x) {
            for (int y = 0; y < 16; ++y) {
                if (brightness[x][y] > 0) {
                    // Fade out
                    brightness[x][y] = (brightness[x][y] > 15) ? brightness[x][y] - 15 : 0;
                    
                    // Convert brightness to color (white-ish)
                    uint8_t val = brightness[x][y];
                    uint32_t color = val;
                    led_matrix->setPixelColor(x, y, color);
                } else {
                    led_matrix->setPixelColor(x, y, 0); // Off
                }
            }
        }
        tick = 0;
    }
    // ========== Handle button and "handshake" ==========
    ESPTransceiver& comm = ESPTransceiver::getInstance();
    // debug
    // Serial.println(state);
    switch (state)
    {
    case WAITING_FOR_START:
        if(start_button->getClick()){
            ESPTransceiver::GameRequestMessage msg = {0};
            comm.send(-1, ESPTransceiver::MessageType::GAME_REQUEST, (char*)&msg);
            state = WAITING_FOR_ACCEPT;
            m_participating_mask = (1 << comm.getMyId());
        }
        else if(!comm.gameRequestQueue.empty()){
            // TODO: pop msg, send accept
            int senderId;
            ESPTransceiver::GameRequestMessage recved_msg;
            
            std::tie(recved_msg, senderId) = comm.gameRequestQueue.front();
            comm.gameRequestQueue.pop();
            
            ESPTransceiver::ReadyInitMessage send_msg = {0};
            comm.send(senderId, ESPTransceiver::MessageType::READY_INIT, (char*)&send_msg);
            state = WAITING_FOR_INIT_DATA;
        }
        break;

    case WAITING_FOR_ACCEPT:
        while(!comm.readyInitQueue.empty()){
            int senderId;
            ESPTransceiver::ReadyInitMessage recved_msg;
            
            std::tie(recved_msg, senderId) = comm.readyInitQueue.front();
            comm.readyInitQueue.pop();
            
            // insert senderId to mask
            m_participating_mask |= (1 << senderId);
        }

        timeout -= dt;
        if(timeout <= 0){ // Reached timeout for accept, start with the current mask!
            m_map_id = millis() % maze_maps->num_maps;
            int player_id = 0;
            int players_mask = m_participating_mask;
            while (players_mask) {
                if ((players_mask & 1) && (player_id != comm.getMyId())) {
                    ESPTransceiver::GameInitMessage msg_struct = {m_map_id, m_participating_mask};
                    ESPTransceiver::getInstance().send(player_id, ESPTransceiver::MessageType::GAME_INIT, (char*)&msg_struct);
                }
                players_mask >>= 1; // move to next bit
                ++player_id;
            }

            m_should_start = true;
            state = DISABLE;
        }
        break;

    case WAITING_FOR_INIT_DATA:
        timeout -= dt;
        if(!comm.gameInitQueue.empty()){
            int senderId;
            ESPTransceiver::GameInitMessage recved_msg;
            
            std::tie(recved_msg, senderId) = comm.gameInitQueue.front();
            comm.gameInitQueue.pop();

            // may add a check of senderId
            m_map_id = recved_msg.map_id;
            m_participating_mask = recved_msg.participating_mask;
            m_should_start = true;
            state = DISABLE;
        }
        else if(timeout <= 0){ // Reached timeout for INIT_DATA, ABORT.
            // do not know what to do here really...
            state = WAITING_FOR_START;
        }
        break;
    }
}

bool PreGame::shouldStart(int& participating_mask, int& map_id){
    participating_mask = m_participating_mask;
    map_id = m_map_id;
    return m_should_start;
}

void PreGame::reset(){
    this->start_button->resetClick();
    this->m_should_start = false;
    this->timeout = REPLY_TIMEOUT;
    this->state = WAITING_FOR_START;
    this->m_participating_mask = 0;

    for (int x = 0; x < 16; ++x)
    for (int y = 0; y < 16; ++y)
    brightness[x][y] = 0;

    this->tick = 0;
    this->m_map_id = -1;
}
