#ifndef ANIMATION
#define ANIMATION

#include "ledMatrix.h"



class Animation
{
public:

    enum Type{
        WIN,
        DISCONNECTED
    };

private:

    static const int DISCONNECTED_FRAME_NUM = 15;

    static const int WIN_FRAME_NUM = 15;
    static const int MAX_RADIUS = 7;
    static const int NUM_CYCLES = 3;



    Type type;
    int frame;
    int cycle;

    int tick;


    bool is_animation_done;

    LedMatrix* matrix;


    void winAnimation();
    void disconnectedAnimation();


public:

    Animation(LedMatrix* matrix);
    ~Animation() = default;

    void update(int dt);

    void setup(Type type);

    bool isDone();

}






#endif