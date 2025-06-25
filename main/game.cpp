#include "game.h"
#include "config.h"
#include "espTransceiver.h"
#include <tuple>

void Game::setup(Gyro* gyro, LedMatrix* matrix, MazeMaps* maze_maps, BoardLayout* board_layout){
    this->gyro = gyro;
    this->matrix = matrix;
    this->maze_maps = maze_maps;
    this->board_layout = board_layout;
}

void Game::initGame(int participating_mask, int map_id){
    this->participating_mask = participating_mask;
    int game_id = getGameId();
    int num_screens = getNumParticipating();

    this->win = false;
    this->maze_maps->getMapPart(num_screens, map_id, game_id, this->map);
    checkBall();

    paintMatrix();
}


int Game::getNumParticipating(){
    int num_participating = 0;
    int players_mask = this->participating_mask;

    while (players_mask) {
        if (players_mask & 1) {
            num_participating += 1;
        }
        players_mask >>= 1; // move to next bit
    }

    return num_participating;
}



int Game::getGameId(){
    int my_id = ESPTransceiver::getInstance().getMyId();

    int player_index = 0;
    int game_id = 0;
    int players_mask = this->participating_mask;
    while (players_mask) {
        if(player_index == my_id){
            break;
        }

        if (players_mask & 1) {
            game_id += 1;
        }

        players_mask >>= 1; // move to next bit
        ++player_index;
    }

    return game_id;
}

void Game::paintMatrix(){
    uint32_t map_colors[256];

    for(int y=0; y<16; y++){
        for(int x=0; x<16; x++){
            MazeMaps::BlockType t = this->map[y+1][x+1];
            Serial.print(t);
            Serial.print(" ");
            map_colors[y*16 + x] = this->colors[t];
        }
    }
    Serial.println("");
    this->matrix->setBoard(map_colors); // Set the initial board colors
}

void Game::checkBall(){
    for(int y = 1; y <= 16; y++){
        for(int x = 1; x <= 16; x++){
            if(this->map[y][x] == MazeMaps::BlockType::BALL){
                this->is_player_here = true;
                this->ball = {x, y};
                return;
            }
        }
    }

    this->is_player_here = false;
    this->ball = {-1, -1};
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

    if (this->map[pos.y][pos.x] == MazeMaps::BlockType::WALL || this->map[pos.y][pos.x] == MazeMaps::BlockType::BORDER) {
        return HIT_WALL; // Hit a wall or border
    }

    if (pos.x == 0 || pos.x == 17 || pos.y == 0 || pos.y == 17) {
        return CROSS_BORDER; // Crossed the finish line
    }

    if(this->map[pos.y][pos.x] == MazeMaps::BlockType::FINISH){
        return WIN;
    }

    return VALID; // Valid position
}

BoardLayout::SIDE Game::calcCrossingSide(Position pos) {
    // Determine which side the player is crossing based on the position
    if (pos.x == 0) {
        return BoardLayout::SIDE::LEFT;
    } else if (pos.x == 17) {
        return BoardLayout::SIDE::RIGHT;
    } else if (pos.y == 0) {
        return BoardLayout::SIDE::UP;
    } else if (pos.y == 17) {
        return BoardLayout::SIDE::DOWN;
    }
    
    return BoardLayout::SIDE::LEFT; // Default case, should not happen
}

void Game::updateBallCrossing(BoardLayout::SIDE my_side, int my_idx){
    switch (my_side)
    {
    case BoardLayout::SIDE::DOWN:
        this->ball = {my_idx, 16};
        break;
    case BoardLayout::SIDE::UP:
        this->ball = {my_idx, 1};
        break;
    case BoardLayout::SIDE::LEFT:
        this->ball = {1, my_idx};
        break;
    case BoardLayout::SIDE::RIGHT:
        this->ball = {16, my_idx};
        break;
    
    default:
        break;
    }

    this->matrix->setPixelColor(this->ball.x - 1, this->ball.y - 1, this->colors[MazeMaps::BlockType::BALL]);
}

void Game::handleBallCrossing(){
    if (!ESPTransceiver::getInstance().ballCrossingQueue.empty()) {
        // Get the front tuple
        auto frontTuple = ESPTransceiver::getInstance().ballCrossingQueue.front();
        ESPTransceiver::getInstance().ballCrossingQueue.pop();

        // Unpack the tuple
        ESPTransceiver::BallCrossingMessage msg;
        int senderId;
        std::tie(msg, senderId) = frontTuple;

        BoardLayout::SIDE my_side = msg.side;
        int my_idx = msg.idx;

        updateBallCrossing(my_side, my_idx);
    }
}


void Game::checkWin(){
    if (!ESPTransceiver::getInstance().victoryQueue.empty()) {
        // Get the front tuple
        auto frontTuple = ESPTransceiver::getInstance().victoryQueue.front();
        ESPTransceiver::getInstance().victoryQueue.pop();

        this->win = true;
    }
}

// Perform the movement based on the option
void Game::performMovement(MovementOption option, Position pos) {
    
    if (option == VALID) {
        if(this->ball.x == pos.x && this->ball.y == pos.y){
            return;
        }
        this->map[this->ball.y][this->ball.x] = MazeMaps::BlockType::EMPTY; 
        this->matrix->setPixelColor(this->ball.x - 1, this->ball.y - 1, 0x000000); // Clear the old position
        this->ball = pos;
        this->map[this->ball.y][this->ball.x] = MazeMaps::BlockType::BALL;
        this->matrix->setPixelColor(this->ball.x - 1, this->ball.y - 1, 0x00FF00); // Set the new position

    } else if (option == WIN) {
        this->map[this->ball.y][this->ball.x] = MazeMaps::BlockType::EMPTY; 
        this->matrix->setPixelColor(this->ball.x - 1, this->ball.y - 1, 0x000000); // Clear the old position
        this->ball = pos;

        this->win = true;
 
    } else if (option == CROSS_BORDER) {
        BoardLayout::SIDE crossing_side = calcCrossingSide(pos);
        BoardLayout::SIDE other_side;
        int id_receiver = this->board_layout->getState(crossing_side, other_side);

        int other_idx = calcOtherSideCrossingIdx(other_side, crossing_side, pos);

        ESPTransceiver::BallCrossingMessage msg_struct = {other_side, other_idx};

        ESPTransceiver::getInstance().send(id_receiver, ESPTransceiver::MessageType::BALL_CROSSING, (char*)&msg_struct);

        this->map[this->ball.y][this->ball.x] = MazeMaps::BlockType::EMPTY;
        this->matrix->setPixelColor(this->ball.x - 1, this->ball.y - 1, 0x000000); 
        this->is_player_here = false;
        this->ball = {-1, -1};
    }
}

int Game::calcOtherSideCrossingIdx(BoardLayout::SIDE other_side, BoardLayout::SIDE my_side, Position pos){
    int my_idx;

    if(my_side == BoardLayout::SIDE::DOWN || my_side == BoardLayout::SIDE::UP){
        my_idx = pos.x;
    }
    else{
        my_idx = pos.y;
    }
    
    switch (my_side)
    {
    case BoardLayout::SIDE::DOWN:
        switch (other_side)
        {
        case BoardLayout::SIDE::DOWN:
            return 15 - my_idx;
            break;
        case BoardLayout::SIDE::UP:
            return my_idx;
            break;
        case BoardLayout::SIDE::LEFT:
            return 15 - my_idx;
            break;
        case BoardLayout::SIDE::RIGHT:
            return my_idx;
            break;
        default:
            break;
        }
        break;
    
    case BoardLayout::SIDE::UP:
        switch (other_side)
        {
        case BoardLayout::SIDE::DOWN:
            return my_idx;
            break;
        case BoardLayout::SIDE::UP:
            return 15 - my_idx;
            break;
        case BoardLayout::SIDE::LEFT:
            return my_idx;
            break;
        case BoardLayout::SIDE::RIGHT:
            return 15 - my_idx;
            break;
        default:
            break;
        }
        break;
    
    case BoardLayout::SIDE::LEFT:
        switch (other_side)
        {
        case BoardLayout::SIDE::DOWN:
            return 15 - my_idx;
            break;
        case BoardLayout::SIDE::UP:
            return my_idx;
            break;
        case BoardLayout::SIDE::LEFT:
            return 15 - my_idx;
            break;
        case BoardLayout::SIDE::RIGHT:
            return my_idx;
            break;
        default:
            break;
        }
        break;
    
    case BoardLayout::SIDE::RIGHT:
        switch (other_side)
        {
        case BoardLayout::SIDE::DOWN:
            return my_idx;
            break;
        case BoardLayout::SIDE::UP:
            return 15 - my_idx;
            break;
        case BoardLayout::SIDE::LEFT:
            return my_idx;
            break;
        case BoardLayout::SIDE::RIGHT:
            return 15 - my_idx;
            break;
        default:
            break;
        }
        break;
    
    default:
        break;
    }
}

void Game::update(int dt) {
    this->tick += dt;

    //CHECK THIS ALWAYS TRACKS!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(this->tick == 250){
        handleBallCrossing();
    }

    if(this->tick >= 250){
        if(this->is_player_here){
            this->move_to_side = this->gyro->getCurDir();
            
            Position next_pos = calcNextPos();

            MovementOption option = checkPos(next_pos);

            performMovement(option, next_pos);
        }
        else{
            checkWin();
        }

        this->tick = 0;
    }
}


void Game::sendWinMessages(){

    int player_id = 0;
    int players_mask = this->participating_mask;
    while (players_mask) {
        if (players_mask & 1) {
            ESPTransceiver::VictoryMessage msg_struct = {0};
            ESPTransceiver::getInstance().send(player_id, ESPTransceiver::MessageType::VICTORY, (char*)&msg_struct);
        }
        players_mask >>= 1; // move to next bit
        ++player_id;
    }
}

bool Game::isWin(){
    return this->win;
}

Game::Game(): tick(0), win(false){}