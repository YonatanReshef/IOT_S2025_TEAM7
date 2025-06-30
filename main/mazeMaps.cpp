#include "mazeMaps.h"

#include "mazeMaps.h"

#include <Arduino.h>

MazeMaps::MazeMaps() {

    /*
    // ==== MAP 1: Single Board ====

    MazeMaps::BlockType temp_maps_for_1[16][16] = {
        { BALL, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, FINISH },
        { EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL },
        { EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL },
        { EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL },
        { EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL },
        { EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL },
        { EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL },
        { EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { EMPTY, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL }
    };

     for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            maps_for_1[0][0][i][j] = temp_maps_for_1[i][j];
        }
     }


    // ==== MAP 2: Single Board ====

    MazeMaps::BlockType temp_maps_for_2_1[16][16] = {
        { BALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, WALL, FINISH, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, WALL, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL, WALL, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, WALL },
        { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL }
    };

    MazeMaps::BlockType temp_maps_for_2_2[16][16] = {
        { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL }
    };

     for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            maps_for_2[0][0][i][j] = temp_maps_for_2_1[i][j];
            maps_for_2[0][1][i][j] = temp_maps_for_2_2[i][j];
        }
     }

    // ==== MAP 3: Single Board ====

    MazeMaps::BlockType temp_maps_for_3_1[16][16] = {
        { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, BALL, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL },
        { WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL }
    };

    MazeMaps::BlockType temp_maps_for_3_2[16][16] = {
        { EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { EMPTY, WALL, WALL, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, EMPTY, EMPTY, WALL },
        { EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, WALL, WALL, WALL, WALL },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL },
        { WALL, EMPTY, WALL, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY },
        { WALL, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { WALL, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, EMPTY, EMPTY, WALL, WALL, WALL, EMPTY, WALL }
    };

    MazeMaps::BlockType temp_maps_for_3_3[16][16] = {
        { WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, EMPTY, WALL, WALL },
        { EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL, WALL, WALL, FINISH },
        { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL },
        { EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, EMPTY, WALL },
        { WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL }
    };

    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            maps_for_3[0][0][i][j] = temp_maps_for_3_1[i][j];
            maps_for_3[0][1][i][j] = temp_maps_for_3_2[i][j];
            maps_for_3[0][2][i][j] = temp_maps_for_3_3[i][j];
        }
     }


    // ==== MAP 4: Single Board ====

    MazeMaps::BlockType temp_maps_for_4_1[16][16] = {
        { WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
        { WALL, BALL, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, EMPTY },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL },
        { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL }
    };

    MazeMaps::BlockType temp_maps_for_4_2[16][16] = {
        { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
        { EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, WALL, WALL, WALL, WALL, EMPTY, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, WALL, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, WALL, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, EMPTY, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL }
    };

    MazeMaps::BlockType temp_maps_for_4_3[16][16] = {
        { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
        { EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL }
    };

    MazeMaps::BlockType temp_maps_for_4_4[16][16] = {
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL },
        { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, WALL },
        { WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL },
        { WALL, FINISH, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
        { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL }
    };

    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            maps_for_4[0][0][i][j] = temp_maps_for_4_1[i][j];
            maps_for_4[0][1][i][j] = temp_maps_for_4_2[i][j];
            maps_for_4[0][2][i][j] = temp_maps_for_4_3[i][j];
            maps_for_4[0][3][i][j] = temp_maps_for_4_4[i][j];
        }
     }
    */

    // ==== MAP 1: Single Board ====

    for (int x = 0; x < 16; ++x)
        for (int y = 0; y < 16; ++y)
            maps_for_1[0][0][x][y] = EMPTY;

    maps_for_1[0][0][0][0] = BALL;
    maps_for_1[0][0][15][15] = FINISH;

    for (int x = 1; x < 15; ++x)
        maps_for_1[0][0][x][8] = WALL;

    // ==== MAP 2: Two Boards ====
    for (int s = 0; s < 2; ++s)
        for (int x = 0; x < 16; ++x)
            for (int y = 0; y < 16; ++y)
                maps_for_2[0][s][x][y] = EMPTY;

    maps_for_2[0][0][0][0] = BALL;
    maps_for_2[0][1][15][15] = FINISH;

    for (int y = 4; y < 12; ++y)
        maps_for_2[0][0][8][y] = WALL;
    for (int x = 4; x < 12; ++x)
        maps_for_2[0][1][x][8] = WALL;

    // ==== MAP 3: Three Boards ====
    for (int s = 0; s < 3; ++s)
        for (int x = 0; x < 16; ++x)
            for (int y = 0; y < 16; ++y)
                maps_for_3[0][s][x][y] = EMPTY;

    maps_for_3[0][0][0][0] = BALL;
    maps_for_3[0][2][15][15] = FINISH;

    for (int x = 0; x < 16; ++x)
        if (x % 2 == 0)
            maps_for_3[0][1][x][7] = WALL;

    // ==== MAP 4: Four Boards ====
    for (int s = 0; s < 4; ++s)
        for (int x = 0; x < 16; ++x)
            for (int y = 0; y < 16; ++y)
                maps_for_4[0][s][x][y] = EMPTY;

    maps_for_4[0][0][0][0] = BALL;
    maps_for_4[0][3][15][15] = FINISH;

    // Zigzag walls across boards
    for (int i = 0; i < 16; ++i)
        if (i % 3 == 0) {
            maps_for_4[0][1][i][i / 2] = WALL;
            maps_for_4[0][2][15 - i][i / 2] = WALL;
        }
    
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

    default:
        break;
    }
    
}


void MazeMaps::fillBorder(int num_screens, int map_id, int other_screen_id, BoardLayout::SIDE my_side, BoardLayout::SIDE other_side, BlockType (&out_map)[18][18]){
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

    default:
        break;
    }


    //copy to out_map
    switch (my_side)
    {
    case BoardLayout::SIDE::DOWN:
        for(int i = 1; i < 17; i++){
            out_map[17][i] = other_border[i];
        }
        break;
    
    case BoardLayout::SIDE::UP:
        for(int i = 1; i < 17; i++){
            out_map[0][i] = other_border[i];
        }
        break;
    
    case BoardLayout::SIDE::LEFT:
        for(int i = 1; i < 17; i++){
            out_map[i][0] = other_border[i];
        }
        break;

    case BoardLayout::SIDE::RIGHT:
        for(int i = 1; i < 17; i++){
            out_map[i][17] = other_border[i];
        }
        break;
    
    default:
        break;
    }

}