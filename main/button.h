#pragma once
#include <Arduino.h>
#include <stdbool.h>

class Button
{
private:
    int pin;
    bool lastState;
    bool clicked;
    unsigned long lastDebounceTime;
    const unsigned long debounceDelay = 50; // ms

public:
    Button(int pin);
    ~Button() = default;

    void setup();
    int update(int dt);
    bool getClick();  // returns true once per press
    void resetClick();
};
