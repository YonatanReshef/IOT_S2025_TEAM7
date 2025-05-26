#include "globals.h"
#include "light_matrix.h"
#include <Adafruit_NeoPixel.h>

const int analogOutPinL = 12;
const int analogOutPinR = 13;
int tick = 0;
int my_index = 0;

uint8_t rightMac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t leftMac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t ownMac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Default MAC address

uint8_t baseMacs[3][6] = {
    {0xB0, 0xA7, 0x32, 0xD7, 0x84, 0x3C},
    {0xB0, 0xA7, 0x32, 0xDE, 0x9E, 0x98},
    {0xF4, 0x65, 0x0B, 0xE9, 0x5E, 0x34}
};

uint32_t matColors[3] = {
  pixels.Color(255, 0, 0), // Red
  pixels.Color(0, 255, 0), // Green
  pixels.Color(0, 0, 255)  // Blue
};


int sub_matL = 0;
int sub_matR = 0;

int leftId = -2;  // Default value indicating no ID
int rightId = -2; // Default value indicating no ID