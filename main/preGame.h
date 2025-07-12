
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

    uint32_t colors[4][4] = {
    //         EMPTY     WALL      BALL      FINISH
    { 0x000000, 0xFFA500, 0x2ACB12, 0x3B3455 }, // Theme 0: "Orange"
                                               // Wall: Bright orange (#FFA500)
                                               // Ball: Leafy green (#2ACB12)
                                               // Finish: Muted blue-violet (#3B3455)

    { 0x000000, 0xFF0000, 0x1FAF0B, 0x181A4C }, // Theme 1: "Brown"
                                               // Wall: Saddle brown (#8B4513)
                                               // Ball: Deep green (#1FAF0B)
                                               // Finish: Deep blue (#181A4C)

    { 0x000000, 0xFFC0CB, 0x1EBF33, 0x1C1BBF }, // Theme 2: "Pink"
                                               // Wall: Classic soft pink (#FFC0CB)
                                               // Ball: Bright green (#1EBF33)
                                               // Finish: Royal blue (#1C1BBF)

    { 0x000000, 0x008080, 0x33CC26, 0x3C3BBF }  // Theme 3: "Teal"
                                               // Wall: Pure teal (#008080)
                                               // Ball: Minty green (#33CC26)
                                               // Finish: Dusty blue (#3C3BBF)
};




    int color_id;
    int master_id;

    static const int REPLY_TIMEOUT = 3000; //ms
    static const int INIT_TIMEOUT = 4000; //ms

public:
    PreGame();
    ~PreGame() = default;

    void setup(LedMatrix* matrix, MazeMaps* mazes, Button* button);
    void update(int dt);
    bool shouldStart(int& participating_mask, int& map_id);
    void reset();

    int getMasterId();
};

#endif // PREGAME