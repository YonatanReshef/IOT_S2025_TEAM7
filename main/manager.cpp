
#include "manager.h"

Manager::Manager():id(-1), state(PRE_GAME), comm(), board_layout()
{
}

void Manager::setup(){
    
    /* ==== comm ==== */
    comm.setup();
    id = comm.getMyId();

    /* ==== board_layout ==== */
    board_layout.setup(id);

    /* ==== game ==== */
    
}

void Manager::update(int dt){

    /* ==== State independant logic ====*/

    board_layout.update(dt);

    /* ==== State dependant logic ====*/

    switch (state)
    {
    case PRE_GAME:
        /* code */
        break;
    
    case INIT_GAME:
        /* code */
        break;
    
    case GAME:
        /* code */
        break;
    
    case END_GAME:
        /* code */
        break;
    }
}
