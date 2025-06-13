#include "game.h"



















void Game::setup() {
    /*
    Initialize the game setup here.
    Initialize:
    map
    is_player_here
    ball
    */

    this->ball = {-1, -1};
    this->is_player_here = false;
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 18; ++j) {
            this->map[i][j] = EMPTY;
        }
    }
}


Position Game::calcNextPos() {
    // Calculate the next position of the ball based on the current gyro data
    // and return it as an array of two integers [x, y].
    Position next_pos;
    next_pos.x = this->ball.x;
    next_pos.y = this->ball.y;

    // Example logic for calculating next position
    if (this->move_to_side == LEFT) {
        next_pos.x -= 1;
    } else if (this->move_to_side == RIGHT) {
        next_pos.x += 1;
    } else if (this->move_to_side == UP) {
        next_pos.y -= 1;
    } else if (this->move_to_side == DOWN) {
        next_pos.y += 1;
    }

    return next_pos;
}



MovementOption Game::checkPos(Position pos) {
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


SIDE Game::calcCrossingSide(Position pos) {
    // Determine which side the player is crossing based on the position
    if (pos.x == 0) {
        return LEFT;
    } else if (pos.x == 17) {
        return RIGHT;
    } else if (pos.y == 0) {
        return UP;
    } else if (pos.y == 17) {
        return DOWN;
    }
    
    return LEFT; // Default case, should not happen
}




// Perform the movement based on the option
void Game::preformMovement(MovementOption option, Position pos) {
    
    if (option == VALID) {
        this->map[this->ball.y][this->ball.x] = EMPTY; 
        this->ball = pos; 
        this->map[pos.y][pos.x] = BALL;

        
    } else if (option == CROSS_BORDER) {
        SIDE crossing_side = calcCrossingSide(pos);
        // Logic to send message to other side about ball crossing
    }
}




void Game::update() {
    //update map and move_to_side here somehow

    Position next_pos = calcNextPos();
    MovementOption option = checkPos(next_pos);

}