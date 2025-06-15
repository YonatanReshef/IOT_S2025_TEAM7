#include "mazeMaps.h"

MazeMaps::MazeMaps(){
    //Initialize the different maps
}


void MazeMaps::getMapPart(int num_screens, int map_id, int screen_id, BlockType out_map[18][18]){
     // Fill top and bottom rows with BORDER
    for (int col = 0; col < 18; ++col) {
        out_map[0][col] = MazeMaps::BlockType::BORDER;       // top row
        out_map[17][col] = MazeMaps::BlockType::BORDER;      // bottom row
    }

    // Fill left and right columns with BORDER
    for (int row = 1; row < 17; ++row) {
        out_map[row][0] = MazeMaps::BlockType::BORDER;       // left column
        out_map[row][17] = MazeMaps::BlockType::BORDER;      // right column
    }


    // Copy inner 16x16 map into center
    switch (num_screens)
    {
    case 1:
        for (int i = 0; i < 16; ++i)
            for (int j = 0; j < 16; ++j)
                out_map[i + 1][j + 1] = maps_for_1[map_id][screen_id][i][j];
        break;
    
    case 2:
        for (int i = 0; i < 16; ++i)
            for (int j = 0; j < 16; ++j)
                out_map[i + 1][j + 1] = maps_for_2[map_id][screen_id][i][j];
        break;
    
    case 3:
        for (int i = 0; i < 16; ++i)
            for (int j = 0; j < 16; ++j)
                out_map[i + 1][j + 1] = maps_for_3[map_id][screen_id][i][j];
        break;

    case 4:
        for (int i = 0; i < 16; ++i)
            for (int j = 0; j < 16; ++j)
                out_map[i + 1][j + 1] = maps_for_4[map_id][screen_id][i][j];
        break;
    
    case 5:
        for (int i = 0; i < 16; ++i)
            for (int j = 0; j < 16; ++j)
                out_map[i + 1][j + 1] = maps_for_5[map_id][screen_id][i][j];
        break;
    
    default:
        break;
    }
    
}


void MazeMaps::fillBorder(int num_screens, int map_id, int other_screen_id, BoardLayout::SIDE my_side, BoardLayout::SIDE other_side, BlockType out_map[18][18]){
    bool his_row;
    int his_idx;
    BlockType other_border[16];

    //Find side and idx on other map
    switch (other_side)
    {
    case BoardLayout::SIDE::DOWN:
        his_row = true;
        his_idx = 15;
        break;
    
    case BoardLayout::SIDE::UP:
        his_row = true;
        his_idx = 0;
        break;
    
    case BoardLayout::SIDE::LEFT:
        his_row = false;
        his_idx = 0;
        break;

    case BoardLayout::SIDE::RIGHT:
        his_row = false;
        his_idx = 15;
        break; 
    
    default:
        break;
    }

    //copy other map border
    switch(num_screens){
    case 1:
        for(int i = 0; i < 16; i++){
            if(his_row){
                other_border[i] = this->maps_for_1[map_id][other_screen_id][his_idx][i];
            }
            else{
                other_border[i] = this->maps_for_1[map_id][other_screen_id][i][his_idx];
            }
        }
        break;
    
    case 2:
        for(int i = 0; i < 16; i++){
            if(his_row){
                other_border[i] = this->maps_for_2[map_id][other_screen_id][his_idx][i];
            }
            else{
                other_border[i] = this->maps_for_2[map_id][other_screen_id][i][his_idx];
            }
        }
        break;
    
    case 3:
        for(int i = 0; i < 16; i++){
            if(his_row){
                other_border[i] = this->maps_for_3[map_id][other_screen_id][his_idx][i];
            }
            else{
                other_border[i] = this->maps_for_3[map_id][other_screen_id][i][his_idx];
            }
        }
        break;

    case 4:
        for(int i = 0; i < 16; i++){
            if(his_row){
                other_border[i] = this->maps_for_4[map_id][other_screen_id][his_idx][i];
            }
            else{
                other_border[i] = this->maps_for_4[map_id][other_screen_id][i][his_idx];
            }
        }
        break;

    case 5:
        for(int i = 0; i < 16; i++){
            if(his_row){
                other_border[i] = this->maps_for_5[map_id][other_screen_id][his_idx][i];
            }
            else{
                other_border[i] = this->maps_for_5[map_id][other_screen_id][i][his_idx];
            }
        }
        break;

    default:
        break;
    }


    //copy to out_map
    switch (my_side)
    {
    case BoardLayout::SIDE::DOWN:
        for(int i = 0; i < 16; i++){
            out_map[15][i] = other_border[i];
        }
        break;
    
    case BoardLayout::SIDE::UP:
        for(int i = 0; i < 16; i++){
            out_map[0][i] = other_border[i];
        }
        break;
    
    case BoardLayout::SIDE::LEFT:
        for(int i = 0; i < 16; i++){
            out_map[i][0] = other_border[i];
        }
        break;

    case BoardLayout::SIDE::RIGHT:
        for(int i = 0; i < 16; i++){
            out_map[i][15] = other_border[i];
        }
        break;
    
    default:
        break;
    }

}