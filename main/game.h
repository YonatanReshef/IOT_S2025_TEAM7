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


    uint32_t colors[4] = {0x000000, 0xFFFFFF, 0x00FF00, 0x0000FF}




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
    void performMovement(MovementOption option, Position pos);

    void updateMatrix();

public:
    Game();
    ~Game() = default;

    void setup(Gyro* gyro, LedMatrix* matrix);
    void update(int dt);
};


#endif // GAME_H