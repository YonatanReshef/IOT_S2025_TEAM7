#ifndef MAZE_MAPS
#define MAZE_MAPS

#include "boardLayout.h"


class MazeMaps{
public:
    enum BlockType {
            EMPTY = 0,
            WALL = 1,
            BALL = 2,
            FINISH = 3,
            BORDER = 4
    };

private:
    
    /* name[num_of_maps][num_of_boards][board_widht][board_height]*/

    BlockType maps_for_1[2][1][16][16];

    BlockType maps_for_2[2][2][16][16];

    BlockType maps_for_3[2][3][16][16];

    BlockType maps_for_4[2][4][16][16];


public:

    MazeMaps();
    ~MazeMaps() = default;


    void getMapPart(int num_screens, int map_id, int screen_id, BlockType out_map[18][18]);

    void fillBorder(int num_screens, int map_id, int other_screen_id, BoardLayout::SIDE my_side, BoardLayout::SIDE other_side, BlockType out_map[18][18]);

    //IF WE SAVE TO FILE, ADD A LOAD
    //GENERATE ~~~~~~~~~~

    //num maps for each num of screens
    int num_maps = 2;

};

#endif