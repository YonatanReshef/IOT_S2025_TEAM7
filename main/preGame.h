
#ifndef PREGAME
#define PREGAME

#include "ledMatrix.h"
#include <cstdlib>
#include <cstdint>

class PreGame
{
private:
    /* data */
    LedMatrix* led_matrix;
    int m_participating_mask;
    int m_map_id;
    bool m_should_start;

    uint8_t brightness[16][16]; // Per-pixel brightness (0–255)

public:
    PreGame();
    ~PreGame() = default;

    void setup(LedMatrix* matrix);
    void update(int dt);
    bool shouldStart(int& participating_mask, int& map_id);
};

#endif // PREGAME