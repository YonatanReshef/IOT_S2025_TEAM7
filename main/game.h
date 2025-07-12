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


    uint32_t colors[4][4] = {
    //         EMPTY     WALL      BALL      FINISH
    { 0x000000, 0xFFA500, 0x2ACB12, 0x3B3455 }, // Theme 0: "Orange"
                                               // Wall: Bright orange (#FFA500)
                                               // Ball: Leafy green (#2ACB12)
                                               // Finish: Muted blue-violet (#3B3455)

    { 0x000000, 0xFF0000, 0x1FAF0B, 0x181A4C }, // Theme 1: "Brown"
                                               // Wall: Saddle brown (#8B4513)
                                               // Ball: Deep green (#1FAF0B)
                                               // Finish: Deep blue (#181A4C)

    { 0x000000, 0xFFC0CB, 0x1EBF33, 0x1C1BBF }, // Theme 2: "Pink"
                                               // Wall: Classic soft pink (#FFC0CB)
                                               // Ball: Bright green (#1EBF33)
                                               // Finish: Royal blue (#1C1BBF)

    { 0x000000, 0x008080, 0x33CC26, 0x3C3BBF }  // Theme 3: "Teal"
                                               // Wall: Pure teal (#008080)
                                               // Ball: Minty green (#33CC26)
                                               // Finish: Dusty blue (#3C3BBF)
};





    /*===== Participating =======*/

    int participating_mask;
    int map_id;
    int color_id;

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

    void initGame(int participating, int map_id, int color_id);

    bool isWin();
    bool isStopped();
    bool isAllAlive();

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