
#ifndef PREGAME
#define PREGAME

#include "ledMatrix.h"
#include "mazeMaps.h"
#include "button.h"
#include "espTransceiver.h"
#include <cstdlib>
#include <cstdint>

class PreGame
{
private:

    enum StateMachine {
        WAITING_FOR_START,
        WAITING_FOR_ACCEPT, 
        WAITING_FOR_INIT_DATA,
        DISABLE
    };

    /*
                WAITING_FOR_START
                    /      \
                start       recved
                pressed     start
                /              \
    WAITING_FOR_ACCEPT      WAITING_FOR_INIT_DATA
                \               /
              timeout          /
                  \           /
              m_should_start = true
    */

    /* data */
    StateMachine state;
    LedMatrix* led_matrix;
    MazeMaps* maze_maps;
    Button* start_button;
    int m_participating_mask;
    int m_map_id;
    bool m_should_start;
    int timeout;
    int tick;

    uint8_t brightness[16][16]; // Per-pixel brightness (0–255)

    static const int REPLY_TIMEOUT = 3000; //ms

public:
    PreGame();
    ~PreGame() = default;

    void setup(LedMatrix* matrix, MazeMaps* mazes, Button* button);
    void update(int dt);
    bool shouldStart(int& participating_mask, int& map_id);
    void reset();
};

#endif // PREGAME