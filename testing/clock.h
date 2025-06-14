
#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>

class Clock
{
private:
    unsigned long t_start = 0;
    unsigned long delay;
    bool first = true;

public:
    Clock(unsigned long delay_time) {
        delay = delay_time * 1000;
    }

    ~Clock() = default;

    int tick() {
        unsigned long now = micros();
        if (first) {
            t_start = now;
            first = false;
            return 0; // No time passed since first tick
        }

        unsigned long elapsed = now - t_start;

        // Wait until delay has passed since last t_start
        if (elapsed < delay) {
            delayMicroseconds(delay - elapsed); // blocking wait
        }

        unsigned long actual_now = micros();
        int actual_elapsed = actual_now - t_start;
        t_start = t_start + delay; // maintain consistent scheduling

        return actual_elapsed / 1000;
    }
};

#endif