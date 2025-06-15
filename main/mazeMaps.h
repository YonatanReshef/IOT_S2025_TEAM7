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
    
    BlockType maps_for_1[1][1][16][16];

    BlockType maps_for_2[1][2][16][16];

    BlockType maps_for_3[1][3][16][16];

    BlockType maps_for_4[1][4][16][16];


public:

    MazeMaps();
    ~MazeMaps();


    void getMapPart(int num_screens, int map_id, int screen_id, BlockType out_map[18][18]);

    void fillBorder(int num_screens, int map_id, int other_screen_id, BoardLayout::SIDE my_side, BoardLayout::SIDE other_side, BlockType out_map[18][18]);

    //IF WE SAVE TO FILE, ADD A LOAD
    //GENERATE ~~~~~~~~~~

};

#endif