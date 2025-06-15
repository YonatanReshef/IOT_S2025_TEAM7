
#ifndef BOARD_LAYOUT
#define BOARD_LAYOUT

#include "opticTransceiver.h"


class BoardLayout
{
private:
    /* 
    Order of sides:
        L, R, U, D
    */
   
   static const int NUM_SIDES = 4;
   OpticTransceiver transceivers[NUM_SIDES];
   int connectorsStates[NUM_SIDES];
   
public:

   enum SIDE {
       LEFT    = 0,
       RIGHT   = 1,
       UP      = 2,
       DOWN    = 3
   };
   
   BoardLayout();
   ~BoardLayout() = default;
   
    void setup(int id);
    void update(int dt);
    /*
        No connection: returns -1
        Connection: returns id and sets other_side
    */
    int getState(int my_side, int &other_side);
    void setMsgId(int id);
};

#endif