#ifndef ANIMATION
#define ANIMATION

#include "ledMatrix.h"



class Animation
{
public:

    enum Type{
        WIN,
        DISCONNECTED,
        STOPPED
    };

private:

    static const int DISCONNECTED_FRAME_NUM = 7;
    static const int STOPPED_FRAME_NUM = 9;

    static const int WIN_FRAME_NUM = 15;
    static const int MAX_RADIUS = 7;
    static const int NUM_CYCLES = 2;

    uint32_t colors[4] = {0x000000, 0xFF0000, 0x00FF00, 0x0000FF};



    Type type;
    int frame;
    int cycle;

    int tick;


    bool is_animation_done;

    LedMatrix* matrix;


    void winAnimation();
    void disconnectedAnimation();
    void stoppedAnimation();


public:

    Animation(LedMatrix* matrix);
    ~Animation() = default;

    void update(int dt);

    void setup(Type type);

    bool isDone();

};






#endif