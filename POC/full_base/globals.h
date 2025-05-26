#ifndef GLOBALS_H
#define GLOBALS_H

#include <cstdint>


#pragma once

// Declare global variables
extern const int analogOutPinL;
extern const int analogOutPinR;
extern int tick;
extern int my_index;


extern uint8_t ownMac[6];
extern uint8_t rightMac[6];
extern uint8_t leftMac[6];
extern uint8_t baseMacs[3][6];

extern uint32_t matColors[3];

extern int sub_matL;
extern int sub_matR;

extern int leftId;
extern int rightId;

#endif