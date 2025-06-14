#include "LedMatrix.h"

#define MATRIX_WIDTH 16
#define MATRIX_HEIGHT 16
#define NUM_PIXELS (MATRIX_WIDTH * MATRIX_HEIGHT)

LedMatrix::LedMatrix(int pin)
    : pixels(NUM_PIXELS, pin, NEO_GRB + NEO_KHZ800) {}

void LedMatrix::setup() {
    pixels.begin();
    pixels.show();  // Turn off all pixels initially
}

int LedMatrix::update(int dt) {
    // pixels.show();
    return 0;
}

void LedMatrix::setPixelColor(int x, int y, uint32_t color) {
    if (x < 0 || x >= MATRIX_WIDTH || y < 0 || y >= MATRIX_HEIGHT)
        return;  // Avoid out-of-bounds access

    int index = getPixelIndex(x, y);
    pixels.setPixelColor(index, color);
    pixels.show();
}

void LedMatrix::setBoard(uint32_t* colors) {
    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
        for (int x = 0; x < MATRIX_WIDTH; ++x) {
            int index = getPixelIndex(x, y);
            int colorIndex = y * MATRIX_WIDTH + x;
            pixels.setPixelColor(index, colors[colorIndex]);
        }
    }
    pixels.show();
}

int LedMatrix::getPixelIndex(int x, int y) {
    if (y % 2 == 0) {
        // Even row: left to right
        return y * MATRIX_WIDTH + x;
    } else {
        // Odd row: right to left
        return y * MATRIX_WIDTH + (MATRIX_WIDTH - 1 - x);
    }
}
