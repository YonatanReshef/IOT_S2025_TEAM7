#ifndef GAME_H
#define GAME_H

#include "gyro.h"
#include "ledMatrix.h"
#include "mazeMaps.h"
#include "button.h"
#include "espTransceiver.h"


class Game
{
private:

    int tick;
    bool win;
    bool stopped;

    /* ==== Movement Option ==== */
    enum MovementOption {
        VALID,
        HIT_WALL,
        CROSS_BORDER,
        OUT_OF_BOUNDS, 
        WIN
    };


    /* ==== Game map ==== */
    MazeMaps::BlockType map[18][18];


    uint32_t colors[4] = {0x000000, 0xFF0000, 0x00FF00, 0x0000FF};


    /*===== Participating =======*/

    int participating_mask;
    int map_id;

    bool allAlive;




    /* ==== Player ==== */
    typedef struct {
        int x;
        int y;
    } Position;

    
    Position ball;
    bool is_player_here;
    Gyro::SIDE move_to_side;


    /* ==== Gyro and Matrix ==== */
    Gyro* gyro;
    LedMatrix* matrix;
    MazeMaps* maze_maps;
    BoardLayout* board_layout;
    Button* button;
    


    /* ==== inner funcs ==== */
    Position calcNextPos();
    BoardLayout::SIDE calcCrossingSide(Position pos);
    MovementOption checkPos(Position pos);
    void performMovement(MovementOption option, Position pos);
    void victory();
    void checkBall();
    void paintMatrix();

    int calcOtherSideCrossingIdx(BoardLayout::SIDE other_side, BoardLayout::SIDE my_side, Position pos);

    void updateMatrix();

    bool handleBallCrossing();

    void updateBallCrossing(BoardLayout::SIDE my_side, int my_idx);

    int getGameId(int id);

    int getNumParticipating();
    
    void checkWin();
    
    void checkSides();

    bool handleStop();

public:
    Game();
    ~Game() = default;

    void setup(Gyro* gyro, LedMatrix* matrix, MazeMaps* maze_maps, BoardLayout* board_layout, Button* button);
    void update(int dt);

    void initGame(int participating, int map_id);

    bool isWin();
    bool isStopped();
    bool isAllAlive();

    void playVictoryAnimationBallPulse();

    bool isParticipatingAlive(int participating_mask);

    void sendWinMessages(int win_stop);
};


#endif // GAME_H


/*
 *
 * notes:
 * - why "isAllAlive" needed?? - this is for the "Game aborted", I dont like this "isAllAlive" name
 * -
 *
 * */