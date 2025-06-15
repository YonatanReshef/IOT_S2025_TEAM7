#ifndef MAZE_MAPS
#define MAZE_MAPS

#include "boardLayout.h"


class MazeMaps{
public:
    enum BlockType {
            EMPTY,
            WALL,
            BALL,
            FINISH,
            BORDER
    };

private:
    
    BlockType maps_for_1[2][1][16][16];

    BlockType maps_for_2[2][2][16][16];

    BlockType maps_for_3[2][3][16][16];

    BlockType maps_for_4[2][4][16][16];

    BlockType maps_for_5[2][5][16][16];


public:

    MazeMaps();
    ~MazeMaps();


    void getMapPart(int num_screens, int map_id, int screen_id, BlockType out_map[18][18]);

    void fillBorder(int num_screens, int map_id, int other_screen_id, BoardLayout::SIDE my_side, BoardLayout::SIDE other_side, BlockType out_map[18][18]);


};

#endif