#include "Button.h"

Button::Button(int pin) : pin(pin), lastState(HIGH), clicked(false), lastDebounceTime(0) {}

void Button::setup() {
    pinMode(pin, INPUT_PULLUP); // assuming button pulls LOW when pressed
}

int Button::update(int dt) {
    bool currentState = digitalRead(pin);
    unsigned long currentTime = millis();
    
    if ((currentTime - lastDebounceTime) > debounceDelay) {
        if (lastState == HIGH && currentState == LOW) {
            clicked = true;
        }
    }

    if (currentState != lastState) {
        lastDebounceTime = currentTime;
    }

    lastState = currentState;
    return 0;
}

bool Button::getClick() {
    if (clicked) {
        clicked = false;
        return true;
    }
    return false;
}

void Button::resetClick(){
    this->clicked = false;
}
