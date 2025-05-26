#ifndef LIGHT_MATRIX_H
#define LIGHT_MATRIX_H

#include <cstdint>
#include <Adafruit_NeoPixel.h>


extern Adafruit_NeoPixel pixels;

void drawMyMiniMatrix(uint32_t fillColor, uint32_t topColor);
void drawNeighborMatrix(const int mySide, const int neighborSide, uint32_t fillColor, uint32_t topColor);
int getPixelIndex(int x, int y);
bool neighborTopIsSameOrientation(const int mySide, const int neighborSide);
void matrix_setup();





#endif