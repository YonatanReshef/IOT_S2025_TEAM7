
#include "preGame.h"



// Function to adjust color to the target brightness (0 to 255)
uint32_t adjust_brightness(uint32_t color, uint8_t target_brightness) {
    // Extract the RGB components from the uint32_t color
    uint8_t r = (color >> 16) & 0xFF;  // Red component
    uint8_t g = (color >> 8) & 0xFF;   // Green component
    uint8_t b = color & 0xFF;          // Blue component

    // Calculate the current brightness (perceived luminance)
    float current_brightness = 0.299 * r + 0.587 * g + 0.114 * b;

    // Calculate the scale factor to match the target brightness
    float scale_factor = target_brightness / current_brightness;

    // Adjust the RGB values by the scale factor, ensuring they stay within the 0-255 range
    r = (uint8_t)fmin(255, fmax(0, r * scale_factor));
    g = (uint8_t)fmin(255, fmax(0, g * scale_factor));
    b = (uint8_t)fmin(255, fmax(0, b * scale_factor));

    // Rebuild the color back into a uint32_t
    return (r << 16) | (g << 8) | b;
}



PreGame::PreGame(): state(WAITING_FOR_START), led_matrix(nullptr), maze_maps(nullptr), start_button(nullptr), 
                    m_participating_mask(0), m_map_id(-1), m_should_start(false), timeout(REPLY_TIMEOUT), tick(0), color_id(-1), master_id(-1){}

void PreGame::setup(LedMatrix* matrix, MazeMaps* mazes, Button* button){
    master_id = -1;
    led_matrix = matrix;
    maze_maps = mazes;
    start_button = button;
    for (int x = 0; x < 16; ++x)
    for (int y = 0; y < 16; ++y)
    brightness[x][y] = 0;


    ESPTransceiver& comm = ESPTransceiver::getInstance();
    this->color_id = comm.getMyId();
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
        uint32_t color = adjust_brightness(this->colors[color_id][1], brightness[x][y]);
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
                    uint32_t color = adjust_brightness(this->colors[color_id][1], brightness[x][y]);
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
            timeout = REPLY_TIMEOUT;
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
            timeout = INIT_TIMEOUT; 
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
           
            int num_players  = 0;
            int players_mask = m_participating_mask;
            while (players_mask) {
                if (players_mask & 1) {
                    num_players++;
                }
                players_mask >>= 1; // move to next bit
            }

            m_map_id = millis() % maze_maps->getNumMaps(num_players);
            int player_id = 0;
            players_mask = m_participating_mask;
            while (players_mask) {
                if ((players_mask & 1) && (player_id != comm.getMyId())) {
                    ESPTransceiver::GameInitMessage msg_struct = {m_map_id, m_participating_mask};
                    ESPTransceiver::getInstance().send(player_id, ESPTransceiver::MessageType::GAME_INIT, (char*)&msg_struct);
                }
                players_mask >>= 1; // move to next bit
                ++player_id;
            }

            master_id = comm.getMyId();
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

            master_id = senderId;
            m_should_start = true;
            state = DISABLE;
        }
        else if(timeout <= 0){ // Reached timeout for INIT_DATA, ABORT.
            // do not know what to do here really...
            state = WAITING_FOR_START;
            this->reset();
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
    this->master_id = -1;
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

    // clean queues!
    ESPTransceiver& comm = ESPTransceiver::getInstance();

    while (!comm.gameInitQueue.empty()) {
        comm.gameInitQueue.pop();
    }
    while (!comm.readyInitQueue.empty()) {
        comm.readyInitQueue.pop();
    }
    while (!comm.gameRequestQueue.empty()) {
        comm.gameRequestQueue.pop();
    }
}


int PreGame::getMasterId(){
    return this->master_id;
}
