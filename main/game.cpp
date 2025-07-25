#include "game.h"
#include "config.h"
#include "espTransceiver.h"
#include <tuple>

void Game::setup(Gyro* gyro, LedMatrix* matrix, MazeMaps* maze_maps, BoardLayout* board_layout, Button* button){
    this->gyro = gyro;
    this->matrix = matrix;
    this->maze_maps = maze_maps;
    this->board_layout = board_layout;
    this->button = button;
}

void Game::initGame(int participating_mask, int map_id, int color_id){
    this->tick = 0;
    this->participating_mask = participating_mask;
    this->map_id = map_id;
    this->color_id = color_id;

    int my_id = ESPTransceiver::getInstance().getMyId();
    int game_id = getGameId(my_id);
    int num_screens = getNumParticipating();

    this->win = false;
    this->stopped = false;
    this->maze_maps->getMapPart(num_screens, map_id, game_id, this->map);
    this->allAlive = true;

    this->move_to_side = Gyro::SIDE::STAY;

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

int Game::getGameId(int id){
    int player_index = 0;
    int game_id = 0;
    int players_mask = this->participating_mask;

    bool id_in_game = false;
    while (players_mask) {
        if((player_index == id) && (players_mask & 1)){
            id_in_game = true;
            break;
        }

        if (players_mask & 1) {
            game_id += 1;
        }

        players_mask >>= 1; // move to next bit
        ++player_index;
    }

    if(id_in_game){
        return game_id;
    }
    
    return -1;
}

void Game::paintMatrix(){
    uint32_t map_colors[256];

    for(int y=0; y<16; y++){
        for(int x=0; x<16; x++){
            MazeMaps::BlockType t = this->map[y+1][x+1];
            /*Serial.print(t);
            Serial.print(" ");*/
            map_colors[y*16 + x] = this->colors[this->color_id][t];
        }
    }
    //Serial.println("");
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
        next_pos.y += 1;
    } else if (this->move_to_side == Gyro::SIDE::DOWN) {
        next_pos.y -= 1;
    }

    return next_pos;
}

Game::MovementOption Game::checkPos(Position pos) {
    // Check if the position is valid (within bounds and not a wall)
    if (pos.x < 0 || pos.x >= 18 || pos.y < 0 || pos.y >= 18) {
        return OUT_OF_BOUNDS; // Out of bounds
    }

    if (this->map[pos.y][pos.x] == MazeMaps::BlockType::WALL || this->map[pos.y][pos.x] == MazeMaps::BlockType::BORDER) {
        //Serial.println("WALL OR BORDER");
        return HIT_WALL; // Hit a wall or border
    }

    if (pos.x == 0 || pos.x == 17 || pos.y == 0 || pos.y == 17) {
        return CROSS_BORDER; // Crossed the finish line
    }

    if(this->map[pos.y][pos.x] == MazeMaps::BlockType::FINISH){
        //Serial.println("WIN");
        return WIN;
    }

    //Serial.println("VALID");
    return VALID; // Valid position
}

BoardLayout::SIDE Game::calcCrossingSide(Position pos) {
    // Determine which side the player is crossing based on the position
    if (pos.x == 17) {
        return BoardLayout::SIDE::RIGHT;
    } else if (pos.x == 0) {
        return BoardLayout::SIDE::LEFT;
    } else if (pos.y == 17) {
        return BoardLayout::SIDE::UP;
    } else if (pos.y == 0) {
        return BoardLayout::SIDE::DOWN;
    }
    
    return BoardLayout::SIDE::LEFT; // Default case, should not happen
}

void Game::updateBallCrossing(BoardLayout::SIDE my_side, int my_idx){
    switch (my_side)
    {
    case BoardLayout::SIDE::DOWN:
        this->ball = {my_idx, 1};
        break;
    case BoardLayout::SIDE::UP:
        this->ball = {my_idx, 17};
        break;
    case BoardLayout::SIDE::LEFT:
        this->ball = {1, my_idx};
        break;
    case BoardLayout::SIDE::RIGHT:
        this->ball = {17, my_idx};
        break;
    
    default:
        break;
    }


    Serial.print("Ball crossed to side: ");
    if(my_side == BoardLayout::SIDE::RIGHT){
            Serial.println("RIGHT");
        }
        if(my_side == BoardLayout::SIDE::LEFT){
            Serial.println("LEFT");
        }
        if(my_side == BoardLayout::SIDE::UP){
            Serial.println("UP");
        }
        if(my_side == BoardLayout::SIDE::DOWN){
            Serial.println("DOWN");
    }

    Serial.print("And is at: X- ");
    Serial.print(this->ball.x);
    Serial.print(" Y- ");
    Serial.println(this->ball.y);

    if(this->map[this->ball.y][this->ball.x] == MazeMaps::BlockType::FINISH){
        this->map[this->ball.y][this->ball.x] = MazeMaps::BlockType::EMPTY;
        sendWinMessages(1);
        this->win = true;
    }
    else{
        this->matrix->setPixelColor(this->ball.x - 1, this->ball.y - 1, this->colors[this->color_id][MazeMaps::BlockType::BALL]);
    }



    this->is_player_here = true;


}

bool Game::handleBallCrossing(){
    if (!ESPTransceiver::getInstance().ballCrossingQueue.empty()) {
        // Get the front tuple
        auto frontTuple = ESPTransceiver::getInstance().ballCrossingQueue.front();
        ESPTransceiver::getInstance().ballCrossingQueue.pop();

        // Unpack the tuple
        ESPTransceiver::BallCrossingMessage msg;
        int senderId;
        std::tie(msg, senderId) = frontTuple;

        /*Serial.print("Sender is ");
        Serial.println(senderId);*/

        BoardLayout::SIDE my_side = msg.side;
        int my_idx = msg.idx;

        /*Serial.print("My Side is ");
        Serial.println(my_side);

        Serial.print("My Idx is ");
        Serial.println(my_idx);*/

        updateBallCrossing(my_side, my_idx);

        return true;
    }

    return false;
}

void Game::checkWin(){
    if (!ESPTransceiver::getInstance().victoryQueue.empty()) {
        // Get the front tuple
        auto frontTuple = ESPTransceiver::getInstance().victoryQueue.front();

        ESPTransceiver::VictoryMessage msg;
        int senderId;
        std::tie(msg, senderId) = frontTuple;

        if(msg.win_stop == 1){ // == win
            ESPTransceiver::getInstance().victoryQueue.pop();
            this->win = true;
        } 
    }
}

// Perform the movement based on the option
void Game::performMovement(MovementOption option, Position pos) {
    
    if (option == VALID) {
        if(this->ball.x == pos.x && this->ball.y == pos.y){
            return;
        }
        this->map[this->ball.y][this->ball.x] = MazeMaps::BlockType::EMPTY; 
        this->matrix->setPixelColor(this->ball.x - 1, this->ball.y - 1, colors[this->color_id][0]); // Clear the old position
        this->ball = pos;
        this->map[this->ball.y][this->ball.x] = MazeMaps::BlockType::BALL;
        this->matrix->setPixelColor(this->ball.x - 1, this->ball.y - 1, colors[this->color_id][2]); // Set the new position

    } else if (option == WIN) {
        this->map[this->ball.y][this->ball.x] = MazeMaps::BlockType::EMPTY; 
        this->matrix->setPixelColor(this->ball.x - 1, this->ball.y - 1, colors[this->color_id][0]); // Clear the old position
        this->ball = pos;

        sendWinMessages(1);

        this->win = true;
 
    } else if (option == CROSS_BORDER) {
        //Serial.println("calcCrossingSide before");
        BoardLayout::SIDE crossing_side = calcCrossingSide(pos);
        //Serial.println("calcCrossingSide after");
        BoardLayout::SIDE other_side;
        //Serial.println("getState before, params");
        Serial.print("crossing side is: ");
        if(crossing_side == BoardLayout::SIDE::RIGHT){
            Serial.println("RIGHT");
        }
        if(crossing_side == BoardLayout::SIDE::LEFT){
            Serial.println("LEFT");
        }
        if(crossing_side == BoardLayout::SIDE::UP){
            Serial.println("UP");
        }
        if(crossing_side == BoardLayout::SIDE::DOWN){
            Serial.println("DOWN");
        }
        
        int id_receiver = this->board_layout->getState(crossing_side, other_side);
        Serial.print("id of esp in crossing side: ");
        Serial.println(id_receiver);

        if(id_receiver != -1){
            Serial.print("And his side is: ");
            if(other_side == BoardLayout::SIDE::RIGHT){
                Serial.println("RIGHT");
            }
            if(other_side == BoardLayout::SIDE::LEFT){
                Serial.println("LEFT");
            }
            if(other_side == BoardLayout::SIDE::UP){
                Serial.println("UP");
            }
            if(other_side == BoardLayout::SIDE::DOWN){
                Serial.println("DOWN");
            }

            int other_idx = calcOtherSideCrossingIdx(other_side, crossing_side, pos);
            Serial.println("Other crossing idx is: ");
            Serial.println(other_idx);



            ESPTransceiver::BallCrossingMessage msg_struct = {other_side, other_idx};
            
            //Serial.println("Send before");
            ESPTransceiver::getInstance().send(id_receiver, ESPTransceiver::MessageType::BALL_CROSSING, (char*)&msg_struct);
            //Serial.println("Send after");

            this->map[this->ball.y][this->ball.x] = MazeMaps::BlockType::EMPTY;
            this->matrix->setPixelColor(this->ball.x - 1, this->ball.y - 1, colors[this->color_id][0]); 
            this->is_player_here = false;
            this->ball = {-1, -1};

            /*Serial.print("Croosing to esp ");
            Serial.println(id_receiver);
            Serial.print("At his side ");
            Serial.println(other_side);*/
        }
    }
}

void Game::checkSides(){
    BoardLayout::SIDE other_side;
    int num_screens = getNumParticipating();
    int esp_game_id;

    BoardLayout::SIDE my_side = BoardLayout::SIDE::DOWN;
    int down_esp = this->board_layout->getState(my_side, other_side);
    if(down_esp != -1){
        //Serial.println("DOWN connected");
        esp_game_id = getGameId(down_esp);
        if(esp_game_id != -1){
            if(this->map[0][1] == MazeMaps::BlockType::BORDER){
                Serial.print("filling DOWN");
                this->maze_maps->fillBorder(num_screens, this->map_id, esp_game_id, BoardLayout::SIDE::DOWN, other_side, this->map);
            }
        }
    }
    else{
        if(this->map[0][1] != MazeMaps::BlockType::BORDER){
            Serial.print("emptying DOWN");
            //Serial.println("DOWN disconnected");
            for (int col = 0; col < 18; ++col) {
                this->map[0][col] = MazeMaps::BlockType::BORDER;      // bottom row
            }
        }
    }


    my_side = BoardLayout::SIDE::UP;
    int up_esp = this->board_layout->getState(my_side, other_side);
    if(up_esp != -1){
        //Serial.println("UP connected");
        esp_game_id = getGameId(up_esp);
        if(esp_game_id != -1){
            if(this->map[17][1] == MazeMaps::BlockType::BORDER){
                Serial.print("filling UP");
                this->maze_maps->fillBorder(num_screens, this->map_id, esp_game_id, BoardLayout::SIDE::UP, other_side, this->map);
            }
        }
    }
    else{
        if(this->map[17][1] != MazeMaps::BlockType::BORDER){
            Serial.print("emptying UP");
            //Serial.println("UP disconnected");
            for (int col = 0; col < 18; ++col) {
                this->map[17][col] = MazeMaps::BlockType::BORDER;       // top row
            }
        }
    }


    my_side = BoardLayout::SIDE::LEFT;
    int left_esp = this->board_layout->getState(my_side, other_side);
    if(left_esp != -1){
        //Serial.println("LEFT connected");
        esp_game_id = getGameId(left_esp);
        if(esp_game_id != -1){
            if(this->map[1][0] == MazeMaps::BlockType::BORDER){
                Serial.print("filling LEFT");
                this->maze_maps->fillBorder(num_screens, this->map_id, esp_game_id, BoardLayout::SIDE::LEFT, other_side, this->map);
            }
        }
    }
    else{
        if(this->map[1][0] != MazeMaps::BlockType::BORDER){
            Serial.print("emptying LEFT");
            //Serial.println("LEFT disconnected");
            for (int row = 0; row < 18; ++row) {
                this->map[row][0] = MazeMaps::BlockType::BORDER;       // left column
            }
        }
    }


    my_side = BoardLayout::SIDE::RIGHT;
    int right_esp = this->board_layout->getState(my_side, other_side);
    if(right_esp != -1){
        //Serial.println("RIGHT connected");
        esp_game_id = getGameId(right_esp);
        if(esp_game_id != -1){
            if(this->map[1][17] == MazeMaps::BlockType::BORDER){
                Serial.println("Border RIGHT before: ");
                for(int i=0; i < 16; i++){
                    Serial.print(this->map[i][17]);
                }
                Serial.print("filling RIGHT");
                this->maze_maps->fillBorder(num_screens, this->map_id, esp_game_id, BoardLayout::SIDE::RIGHT, other_side, this->map);

                Serial.println("Border RIGHT after: ");
                for(int i=0; i < 16; i++){
                    Serial.print(this->map[i][17]);
                }
            }
        }
    }
    else{
        if(this->map[1][17] != MazeMaps::BlockType::BORDER){
            Serial.print("emptying RIGHT");
            //Serial.println("RIGHT disconnected");
            for (int row = 0; row < 18; ++row) {
                this->map[row][17] = MazeMaps::BlockType::BORDER;      // right column
            }
        }
    }

    //this->paintMatrix();

}

int Game::calcOtherSideCrossingIdx(BoardLayout::SIDE other_side, BoardLayout::SIDE my_side, Position pos){

    Serial.println("other side");
    Serial.println(other_side);

    Serial.println("my side");
    Serial.println(my_side);

    Serial.println("Pos X");
    Serial.println(pos.x);
    Serial.println("Pos y");
    Serial.println(pos.y);

    int my_idx;

    if(my_side == BoardLayout::SIDE::DOWN || my_side == BoardLayout::SIDE::UP){
        my_idx = pos.x;
    }
    else{
        my_idx = pos.y;
    }

    Serial.println("my idx");
    Serial.println(my_idx);

    switch (my_side)
    {
    case BoardLayout::SIDE::DOWN:
        switch (other_side)
        {
        case BoardLayout::SIDE::DOWN:
            return 17 - my_idx;
            break;
        case BoardLayout::SIDE::UP:
            return my_idx;
            break;
        case BoardLayout::SIDE::LEFT:
            return my_idx;
            break;
        case BoardLayout::SIDE::RIGHT:
            return 17 - my_idx;
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
            return 17 - my_idx;
            break;
        case BoardLayout::SIDE::LEFT:
            return 17 - my_idx;
            break;
        case BoardLayout::SIDE::RIGHT:
            return my_idx;
            break;
        default:
            break;
        }
        break;
    
    case BoardLayout::SIDE::LEFT:
        switch (other_side)
        {
        case BoardLayout::SIDE::DOWN:
            return my_idx;
            break;
        case BoardLayout::SIDE::UP:
            return 17 - my_idx;
            break;
        case BoardLayout::SIDE::LEFT:
            return 17 - my_idx;
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
            return 17 - my_idx;
            break;
        case BoardLayout::SIDE::UP:
            return my_idx;
            break;
        case BoardLayout::SIDE::LEFT:
            return my_idx;
            break;
        case BoardLayout::SIDE::RIGHT:
            return 17 - my_idx;
            break;
        default:
            break;
        }
        break;
    
    default:
        break;
    }
}

/*
 * What should happen in update:
 * - Check game validity (aborted yes/no)
 * - update ball position
 * - ball crossing
 * - check win
 *
 * */
void Game::update(int dt) {
    this->tick += dt;

    if(this->tick >= 350){

        if(!isParticipatingAlive(this->participating_mask)){
            this->allAlive = false;
            this->tick = 0;
            return;
        }

        if(this->stopped || handleStop()){
            // Game stopped!
            this->stopped = true;
            return;
        }


        checkSides();
        bool is_crossing_in = handleBallCrossing();

        if(!is_crossing_in) {
            if (this->is_player_here) {
                this->move_to_side = this->gyro->getCurDir();

                /*Serial.print("Direction is ");
                if(this->move_to_side == Gyro::DOWN){
                    Serial.println("DOWN ----------");
                }
                if(this->move_to_side == Gyro::UP){
                    Serial.println("UP ----------");
                }
                if(this->move_to_side == Gyro::LEFT){
                    Serial.println("LEFT ----------");
                }
                if(this->move_to_side == Gyro::RIGHT){
                    Serial.println("RIGHT ----------");
                }
                if(this->move_to_side == Gyro::STAY){
                    Serial.println("STAY ----------");
                }
                /*
                Serial.print("Calc next POS from ");
                Serial.print(this->ball.x);
                Serial.print(" , ");
                Serial.println(this->ball.y);*/
                Position next_pos = calcNextPos();

                /*Serial.println("-----------------");

                Serial.print("To Pos ");
                Serial.print(next_pos.x);
                Serial.print(" , ");
                Serial.println(next_pos.y);*/

                MovementOption option = checkPos(next_pos);


                if (option == MovementOption::CROSS_BORDER) {
                    Serial.print("Option is ");
                    Serial.println("CROSS BORDER ----------");
                }
                if (option == MovementOption::HIT_WALL) {
                    Serial.print("Option is ");
                    Serial.println("WALL ----------");
                }
                if (option == MovementOption::OUT_OF_BOUNDS) {
                    Serial.print("Option is ");
                    Serial.println("OUT OF BOUNDS ----------");
                }

                performMovement(option, next_pos);
            } else {
                checkWin();
            }
        }

        this->tick = 0;
        //Serial.println("Game Update done---------------------");
    }

    
}

bool Game::handleStop(){
    if(this->button->getClick()){
        sendWinMessages(0);
        this->stopped = true;
    }
    else if (!ESPTransceiver::getInstance().victoryQueue.empty()) {
        // Get the front tuple
        auto frontTuple = ESPTransceiver::getInstance().victoryQueue.front();
        
        ESPTransceiver::VictoryMessage msg;
        int senderId;
        std::tie(msg, senderId) = frontTuple;

        if(msg.win_stop == 0){ // == stop
            ESPTransceiver::getInstance().victoryQueue.pop();
            this->stopped = true;
        } 
    }
    return false;
}

void Game::sendWinMessages(int win_stop){

    int player_id = 0;
    int players_mask = this->participating_mask;
    while (players_mask) {
        if (players_mask & 1) {
            ESPTransceiver::VictoryMessage msg_struct = {win_stop};
            ESPTransceiver::getInstance().send(player_id, ESPTransceiver::MessageType::VICTORY, (char*)&msg_struct);
        }
        players_mask >>= 1; // move to next bit
        ++player_id;
    }
}

bool Game::isParticipatingAlive(int participating_mask){ 
    int player_id = 0;
    while (participating_mask) {
        if (participating_mask & 1) {
            //Serial.println(player_id);
            if(!ESPTransceiver::getInstance().isAlive(player_id)){
                return false;
            }
        }
        participating_mask >>= 1; // move to next bit
        ++player_id;
    }
    
    return true;
}

bool Game::isWin(){
    return this->win;
}

bool Game::isStopped(){
    return this->stopped;
}

bool Game::isAllAlive(){
    return this->allAlive;
}

Game::Game(): tick(0), win(false), stopped(false){}