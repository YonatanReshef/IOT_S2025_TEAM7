#ifndef MANAGER
#define MANAGER

#include "boardLayout.h"
#include "espTransceiver.h"
#include "game.h"
#include "preGame.h"
#include "gyro.h"
#include "ledMatrix.h"
#include "mazeMaps.h"
#include "button.h"
#include "Animation.h"

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

    Gyro gyro;
    LedMatrix matrix;
    Button button;

    MazeMaps maze_maps;
    PreGame pre_game;
    Game game;
    Animation animation;


    /*==== FUNCS ==========*/
    

public:
    Manager();
    ~Manager() = default;

    void setup();
    void update(int dt);
};


#endif