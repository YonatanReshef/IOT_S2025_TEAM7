#include "game.h"
#include "config.h"

void Game::setup(){
    /*
    Initialize the game setup here.
    Initialize:
    map
    is_player_here
    ball
    */

    this->ball = {7, 9};
    this->is_player_here = true;


    MazeMaps::BlockType map[18][18] = {
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::FINISH, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::WALL, MazeMaps::BlockType::EMPTY, MazeMaps::BlockType::BORDER},
    {MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER, MazeMaps::BlockType::BORDER}
    };


    for (int y = 0; y < 18; ++y) {
        for (int x = 0; x < 18; ++x) {
            this->map[y][x] = init_map[y][x];
        }
    }

    uint32_t map_colors[256] = {
    // row 1
    0x000000, 0xFFFFFF, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000,
    0xFFFFFF, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000,
    // row 2
    0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
    0xFFFFFF, 0xFFFFFF, 0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0x000000,
    // row 3
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000,
    // row 4
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0xFFFFFF, 0xFFFFFF,
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0xFFFFFF, 0xFFFFFF, 0x000000, 0xFFFFFF,
    // row 5
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0xFFFFFF, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000,
    // row 6
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
    // row 7
    0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    // row 8
    0xFFFFFF, 0xFFFFFF, 0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
    0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000,
    // row 9
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x00FF00, 0xFFFFFF,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000,
    // row 10
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0xFFFFFF, 0xFFFFFF,
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0xFFFFFF, 0x000000,
    // row 11
    0x000000, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000,
    // row 12
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
    // row 13
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x0000FF, 0x000000,
    // row 14
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
    // row 15
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    // row 16
    0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000
};


    this->matrix.setup(); // Assuming LedMatrix has a setup method
    this->matrix.setBoard(map_colors); // Set the initial board colors

    this->gyro.setup(); // Assuming Gyro has a setup method
}


Game::Position Game::calcNextPos() {
    // Calculate the next position of the ball based on the current gyro data
    // and return it as an array of two integers [x, y].
    Position next_pos;
    next_pos.x = this->ball.x;
    next_pos.y = this->ball.y;

    // Example logic for calculating next position
    if (this->move_to_side == Gyro::SIDE::LEFT) {
        next_pos.x -= 1;
    } else if (this->move_to_side == Gyro::SIDE::RIGHT) {
        next_pos.x += 1;
    } else if (this->move_to_side == Gyro::SIDE::UP) {
        next_pos.y -= 1;
    } else if (this->move_to_side == Gyro::SIDE::DOWN) {
        next_pos.y += 1;
    }

    return next_pos;
}



Game::MovementOption Game::checkPos(Position pos) {
    // Check if the position is valid (within bounds and not a wall)
    if (pos.x < 0 || pos.x >= 18 || pos.y < 0 || pos.y >= 18) {
        return OUT_OF_BOUNDS; // Out of bounds
    }

    if (this->map[pos.y][pos.x] == WALL || this->map[pos.y][pos.x] == BORDER) {
        return HIT_WALL; // Hit a wall or border
    }

    if (pos.x == 0 || pos.x == 17 || pos.y == 0 || pos.y == 17) {
        return CROSS_BORDER; // Crossed the finish line
    }

    return VALID; // Valid position
}


Gyro::SIDE Game::calcCrossingSide(Position pos) {
    // Determine which side the player is crossing based on the position
    if (pos.x == 0) {
        return Gyro::SIDE::LEFT;
    } else if (pos.x == 17) {
        return Gyro::SIDE::RIGHT;
    } else if (pos.y == 0) {
        return Gyro::SIDE::UP;
    } else if (pos.y == 17) {
        return Gyro::SIDE::DOWN;
    }
    
    return Gyro::SIDE::LEFT; // Default case, should not happen
}




// Perform the movement based on the option
void Game::preformMovement(MovementOption option, Position pos) {
    
    if (option == VALID) {
        this->map[this->ball.y][this->ball.x] = EMPTY; 
        this->matrix.setPixelColor(this->ball.x - 1, this->ball.y - 1, 0x000000); // Clear the old position
        this->ball = pos;
        this->map[this->ball.y][this->ball.x] = BALL;
        this->matrix.setPixelColor(this->ball.x - 1, this->ball.y - 1, 0x00FF00); // Set the new position

        
    } else if (option == CROSS_BORDER) {
        //this->map[this->ball.y][this->ball.x] = EMPTY;
        //SIDE crossing_side = calcCrossingSide(pos);
        // Logic to send message to other side about ball crossing
    }
}




void Game::update(int dt) {
    this->tick += dt;

    this->move_to_side = this->gyro.update(); // Update gyro data

    //update map and move_to_side here somehow

    if(this->tick >= 500){

        Position next_pos = calcNextPos();

        MovementOption option = checkPos(next_pos);

        preformMovement(option, next_pos);
        this->tick = 0;
    }
}



Game::Game(): tick(0), matrix(PIN_MAT_IN){}