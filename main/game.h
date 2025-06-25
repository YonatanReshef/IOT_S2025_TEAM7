#ifndef GAME_H
#define GAME_H

#include "gyro.h"
#include "ledMatrix.h"
#include "mazeMaps.h"
#include "espTransceiver.h"


class Game
{
private:

    int tick;
    bool win;

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


    uint32_t colors[4] = {0x000000, 0xFFFFFF, 0x00FF00, 0x0000FF};


    /*===== Participating =======*/

    int participating_mask;




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

    void handleBallCrossing();

    void updateBallCrossing(BoardLayout::SIDE my_side, int my_idx);

    int getGameId();

    int getNumParticipating();

public:
    Game();
    ~Game() = default;

    void setup(Gyro* gyro, LedMatrix* matrix, MazeMaps* maze_maps, BoardLayout* board_layout);
    void update(int dt);

    void initGame(int participating, int map_id);

    bool isWin();

    void sendWinMessages()
};


#endif // GAME_H