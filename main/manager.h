
#include "boardLayout.h"
#include "espTransciever.h"
// #include "game.h"

class Manager
{
private:

    enum State{
        PRE_GAME,
        INIT_GAME,
        GAME,
        END_GAME
    };

    /* ==== State ====*/
    int id;
    State state;

    /* ==== components ==== */
    BoardLayout board_layout;
    ESPTransceiver comm;
    

public:
    Manager();
    ~Manager() = default;

    void setup();
    void update(int dt);
};

