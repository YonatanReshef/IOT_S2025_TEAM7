#ifndef GAME_H
#define GAME_H

#include "gyro.h"
#include "ledMatrix.h"
#include "mazeMaps.h"


class Game
{
private:

    int tick;

    /* ==== Movement Option ==== */
    enum MovementOption {
        VALID,
        HIT_WALL,
        CROSS_BORDER,
        OUT_OF_BOUNDS
    };


    /* ==== Game map ==== */
    MazeMaps::BlockType map[18][18];




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



    /* ==== inner funcs ==== */
    Position calcNextPos();
    Gyro::SIDE calcCrossingSide(Position pos);
    MovementOption checkPos(Position pos);
    void preformMovement(MovementOption option, Position pos);

    void updateMatrix();

public:
    Game(Gyro* gyro, LedMatrix* matrix);
    ~Game() = default;

    void setup();
    void update(int dt);
};


#endif // GAME_H