#ifndef GAME_H
#define GAME_H

#include "gyro.h"
#include "ledMatrix.h"


class Game
{
private:

    /* ==== Movement Option ==== */
    enum MovementOption {
        VALID,
        HIT_WALL,
        CROSS_BORDER,
        OUT_OF_BOUNDS
    };



    /* ==== Block type ==== */
    enum BlockType {
        EMPTY,
        WALL,
        BALL,
        FINISH,
        BORDER
    };


    /* ==== Game map ==== */
    BlockType map[18][18];




    /* ==== Player ==== */
    typedef struct {
        int x;
        int y;
    } Position;

    
    Position ball;
    bool is_player_here;
    SIDE move_to_side;


    /* ==== inner funcs ==== */
    Position calcNextPos();
    SIDE calcCrossingSide(Position pos);
    MovementOption checkPos(Position pos);
    void preformMovement(MovementOption option, Position pos);

    void updateMatrix();

public:
    Game();
    ~Game() = default;

    void setup();
    void update();
};














#endif // GAME_H