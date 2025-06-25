
#include "manager.h"
#include "config.h"
#include <random>

Manager::Manager(): id(-1), state(PRE_GAME), // TODO: change to PRE_GAME
                    board_layout(), gyro(), matrix(PIN_MAT_IN), button(PIN_START_BTN),
                    maze_maps(), game()
{}


int Manager::getNumParticipating(int paricipating_mask){
    int num_participating = 0;

    while (paricipating_mask) {
        if (paricipating_mask & 1) {
            num_participating += 1;
        }
        paricipating_mask >>= 1; // move to next bit
    }

    return num_participating;
}

int Manager::generateMapId(){
    int time = millis();

    return time % maze_maps.num_maps;
}

int Manager::sendStartMessages(){
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

void Manager::setup(){
    
    /* ==== comm ==== */
    ESPTransceiver::getInstance().setup();
    id = ESPTransceiver::getInstance().getMyId();
    Serial.print("id: ");
    Serial.println(id);
    id = 0; // TODO: temp, change this
    /* ==== HW ====*/
    gyro.setup();
    matrix.setup();
    button.setup();

    /* ==== board_layout ==== */
    board_layout.setup(id);

    /* ==== game ==== */
    game.setup(&gyro, &matrix, &maze_maps, &board_layout);
}

void Manager::update(int dt){

    /* ==== State independant logic ====*/

    board_layout.update(dt);
    gyro.update(dt);
    matrix.update(dt);
    button.update(dt);

    // TODO:
    ESPTransceiver::getInstance().update(dt);

    /* ==== State dependant logic ====*/
    
    // Change according to liveness
    int map_id = 0, participating_mask = 0;

    switch (state)
    {
    case PRE_GAME:
        /* code */
        // TODO: pre-game logic
        if(pre_game.shouldStart(map_id, participating_mask)){
            state = INIT_GAME;
            Serial.println("PRE -> INIT");
        }
        
        break;
    
    case INIT_GAME:
        game.initGame(participating_mask, map_id);
        // wait for successeful init
        state = GAME;
        Serial.println("INIT -> GAME");
        break;
    
    case GAME:
        game.update(dt);
        if(game.isWin()){
            state = END_GAME;
            Serial.println("GAME -> END");
        }
        break;
        
        case END_GAME:
        /* code */
        // TODO: Display win msg
        state = PRE_GAME;
        Serial.println("END -> PRE");
        break;
    }
}


