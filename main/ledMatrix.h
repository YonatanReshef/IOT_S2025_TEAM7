
#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <cstdint>
#include <Adafruit_NeoPixel.h>

class LedMatrix
{
private:
    Adafruit_NeoPixel pixels;
    int getPixelIndex(int x, int y);

public:
    LedMatrix(int pin);
    ~LedMatrix() = default;

    void setup();
    int update(int dt);
    void setPixelColor(int x, int y, uint32_t color);
    void setBoard(uint32_t *colors);

    void showAnimation(int type, int frame);

    //add an effect function
};

#endif