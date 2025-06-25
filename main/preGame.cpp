
#include "preGame.h"


static int sendStartMessages(){
    int participating_mask = ESPTransceiver::getInstance().getParticipatingMask();
    int map_id = generateMapId();

    int player_id = 0;
    int players_mask = participating_mask;
    while (players_mask) {
        if (players_mask & 1) {
            ESPTransceiver::GameInitMessage msg_struct = {map_id, participating_mask};
            ESPTransceiver::getInstance().send(player_id, ESPTransceiver::MessageType::GAME_INIT, (char*)&msg_struct);
        }
        players_mask >>= 1; // move to next bit
        ++player_id;
    }

    return participating_mask;
}


PreGame::PreGame():led_martrix(nullptr), m_participating_mask(0), m_map_id(-1), m_should_start(false){}


void PreGame::setup(LedMatrix* matrix){
    led_martrix = matrix;
    for (int x = 0; x < 16; ++x)
        for (int y = 0; y < 16; ++y)
            brightness[x][y] = 0;
}


void PreGame::update(int dt) {

    // ========== Handle Display ==========

    // Randomly light up a pixel
    if (dt % 100 == 0) {  // Adjust frequency
        int x = rand() % 16;
        int y = rand() % 16;
        brightness[x][y] = 255;
    }

    // Update pixels
    for (int x = 0; x < 16; ++x) {
        for (int y = 0; y < 16; ++y) {
            if (brightness[x][y] > 0) {
                // Fade out
                brightness[x][y] = (brightness[x][y] > 15) ? brightness[x][y] - 15 : 0;

                // Convert brightness to color (white-ish)
                uint8_t val = brightness[x][y];
                uint32_t color = led_martrix->pixels.Color(val, val, val);
                led_martrix->setPixelColor(x, y, color);
            } else {
                led_martrix->setPixelColor(x, y, 0); // Off
            }
        }
    }

    led_martrix->update(dt);

    // ========== Handle button and "hanshake" ==========

    

}


bool PreGame::shouldStart(int& participating_mask, int& map_id){
    participating_mask = m_participating_mask;
    map_id = m_map_id;
    return m_should_start
}
