
#include "manager.h"
#include "config.h"

Manager::Manager(): id(-1), state(INIT_GAME), // TODO: change to PRE_GAME
                    board_layout(), gyro(), matrix(PIN_MAT_IN), button(PIN_START_BTN),
                    maze_maps(), game()
{}

void Manager::setup(){
    
    /* ==== comm ==== */
    ESPTransceiver::setup();
    id = comm.getMyId();
    
    /* ==== HW ====*/
    gyro.setup()
    matrix.setup()
    button.setup()

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
    ESPTransceiver::update(dt);

    /* ==== State dependant logic ====*/
    
    // Change according to liveness
    int map_id = 1, num_screens = 1;

    switch (state)
    {
    case PRE_GAME:
        /* code */
        // TODO: pre-game logic
        if(button.getClick()){
            //TODO: logic of starting a game
            state = PRE_GAME;
        }
        break;
    
    case INIT_GAME:
        game.initGame(map_id, num_screens, this->id);
        // wait for successeful init
        state = GAME;
        break;
    
    case GAME:
        game.update();
        if game.isWin(){
            state = END_GAME;
        }
        break;
    
    case END_GAME:
        /* code */
        // TODO: Display win msg
        state = PRE_GAME;
        break;
    }
}


