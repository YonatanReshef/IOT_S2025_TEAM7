#include "light_matrix.h"
#include <Adafruit_NeoPixel.h>
#include "globals.h"

#define PIN        14
#define NUMPIXELS  256  // 16x16 matrix
#define BRIGHTNESS 20

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Draw your own center 4x4 mini-matrix with top row highlighted
void drawMyMiniMatrix(uint32_t fillColor, uint32_t topColor) {
  for (int y = 6; y < 10; ++y) {
    for (int x = 6; x < 10; ++x) {
      int index = getPixelIndex(x, y);

      bool isTop = (y == 6);
      pixels.setPixelColor(index, isTop ? topColor : fillColor);
    }
  }
}


// Draws the neighbor's mini matrix based on orientation
void drawNeighborMatrix(const int mySide, const int neighborSide, uint32_t fillColor, uint32_t topColor) {
  const int myCenterX = 6;
  const int myCenterY = 6;

  int dx = 0, dy = 0;

  if (mySide == 0){  
    dx = 5; //left
    sub_matL = 1;
  }
  else if (mySide == 1){
    dx = -5; //right
    sub_matR = 1;
  }

  int startX = myCenterX + dx;
  int startY = myCenterY;

  bool sameOrientation = neighborTopIsSameOrientation(mySide, neighborSide);

  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      int drawX = startX + x;
      int drawY = startY + y;

      // Decide which row is "top" in neighbor mini matrix
      bool isTop = sameOrientation ? (y == 3) : (y == 0);

      uint32_t color = isTop ? topColor : fillColor;

      if (drawX >= 0 && drawX < 16 && drawY >= 0 && drawY < 16) {
        int pixelIndex = getPixelIndex(drawX, drawY);
        pixels.setPixelColor(pixelIndex, color);
      }
    }
  }
}


int getPixelIndex(int x, int y) {
  if (y % 2 == 0) {
    // Even row: left to right
    return y * 16 + x;
  } else {
    // Odd row: right to left
    return y * 16 + (15 - x);
  }
}




// Returns true if the neighbor's top corresponds to y == 0 row, false if y == 3 (opposite)
bool neighborTopIsSameOrientation(const int mySide, const int neighborSide) {
  return mySide == neighborSide;
}


void matrix_setup() {
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
  pixels.clear();

  // Draw your own center mini-matrix in green
  drawMyMiniMatrix(matColors[my_index], pixels.Color(255, 255, 255));

  // Test neighbors on all four sides
  //drawNeighborMatrix("left", "left", pixels.Color(0, 0, 255),   pixels.Color(255, 255, 255));  // Top neighbor, top row red
  pixels.show();
}