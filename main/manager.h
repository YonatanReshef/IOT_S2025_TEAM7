#ifndef MANAGER
#define MANAGER

#include "boardLayout.h"
#include "espTransciever.h"
#include "game.h"
#include "gyro.h"
#include "ledMatrix.h"
// #include "game.h"

class Manager
{
private:

    enum State{
        PRE_GAME,
        INIT_GAME,
        GAME,
        END_GAME
    };

    /* ==== State ====*/
    int id;
    State state;

    /* ==== components ==== */
    BoardLayout board_layout;
    ESPTransceiver comm;

    Gyro gyro;
    LedMatrix matrix;

    Game game;
    

public:
    Manager();
    ~Manager() = default;

    void setup();
    void update(int dt);
};


#endif