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

    MazeMaps();
    ~MazeMaps() = default;
    
    
    void getMapPart(int num_screens, int map_id, int screen_id, BlockType out_map[18][18]);
    
    void fillBorder(int num_screens, int map_id, int other_screen_id, BoardLayout::SIDE my_side, BoardLayout::SIDE other_side, BlockType (&out_map)[18][18]);
    
    //IF WE SAVE TO FILE, ADD A LOAD
    //GENERATE ~~~~~~~~~~
    
    //num maps for each num of screens
    static const int num_maps_1 = 4;
    static const int num_maps_2 = 2;
    static const int num_maps_3 = 1;
    static const int num_maps_4 = 1;

private:
    
    /* name[num_of_maps][num_of_boards][board_widht][board_height]*/

    BlockType maps_for_1[num_maps_1][1][16][16];

    BlockType maps_for_2[num_maps_2][2][16][16];

    BlockType maps_for_3[num_maps_3][3][16][16];

    BlockType maps_for_4[num_maps_4][4][16][16];
};

#endif