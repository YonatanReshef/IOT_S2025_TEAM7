
#ifndef PREGAME
#define PREGAME

#include "ledMatrix.h"

class PreGame
{
    private:
    /* data */

    public:
    PreGame();
    ~PreGame() = default;

    void setup(LedMatrix* matrix);
    void update(int dt);
    bool shouldStart(int& participating_mask, int& map_id);
};

#endif // PREGAME