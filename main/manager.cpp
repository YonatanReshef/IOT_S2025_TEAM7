
#include "manager.h"
#include "config.h"
#include <random>

Manager::Manager(): id(-1), state(PRE_GAME), // TODO: change to PRE_GAME
                    board_layout(), gyro(), matrix(PIN_MAT_IN), button(PIN_START_BTN),
                    maze_maps(), pre_game(), game()
{}


void Manager::setup(){
    
    /* ==== comm ==== */
    ESPTransceiver::getInstance().setup();
    id = ESPTransceiver::getInstance().getMyId();
    Serial.print("id: ");
    Serial.println(id);
    // id = 0; // TODO: temp, change this
    /* ==== HW ====*/
    gyro.setup();
    matrix.setup();
    button.setup();

    /* ==== board_layout ==== */
    board_layout.setup(id);

    /* ==== game ==== */
    pre_game.setup(&matrix, &maze_maps, &button);
    game.setup(&gyro, &matrix, &maze_maps, &board_layout);


    this->participating_mask = 0;
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
    int map_id = 0;

    switch (state)
    {
    case PRE_GAME:
        /* code */
        // TODO: pre-game logic
        pre_game.update(dt);
        if(pre_game.shouldStart(this->participating_mask, map_id)){
            state = INIT_GAME;
            Serial.println("PRE -> INIT");
        }
        break;
    
    case INIT_GAME:
        pre_game.shouldStart(this->participating_mask, map_id);
        /*Serial.println(map_id);
        Serial.println(this->participating_mask);*/
        game.initGame(this->participating_mask, map_id);
        // wait for successeful init
        state = GAME;
        Serial.println("INIT -> GAME");
        break;
    
    case GAME:

        game.update(dt);

        if(!game.isAllAlive()){
            Serial.println("ParticipatingDead=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
            state = END_GAME;
            Serial.println("GAME -> END");
            break;
        }

        if(game.isWin()){
            state = END_GAME;
            Serial.println("GAME -> END");
        }
        break;
        
    case END_GAME:
        /* code */
        // TODO: Display win msg
        // TODO: reset pregame, game, msg queues...
        state = PRE_GAME;

        this->game.playVictoryAnimationBallPulse();

        pre_game.reset();
        this->participating_mask = 0;
        Serial.println("END -> PRE");
        break;
    }
}


