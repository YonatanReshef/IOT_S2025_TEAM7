#ifndef BASE_OPTIC_COMM_H
#define BASE_OPTIC_COMM_H

#include <tuple>

#pragma once

// Transmission data: 6-bit preamble + 4-bit message
extern const int TRANSMISSION_SIZE;
extern int send_data[10];

// Transmission state
extern int current_bit;


extern int tick;
extern const int analogOutPin;


extern const int MESSAGE_SIZE; // 4 data bits

// Transmission configuration
extern const int PWM_MAX;
extern const int BIT_PERIOD_MS;
extern const int SAMPLE_INTERVAL_MS;

// Thresholds
extern const int LIGHT_THRESHOLD;
extern const int PREAMBLE_DURATION_MS;


// Receiver state machine
enum StateMachine {
  WAIT_PREAMBLE,
  GET_DATA
};

// Struct to hold receiver state and data
typedef struct {
  int analogInPin;
  StateMachine state;
  int ticksOnPreamble;
  int sync_val;
  int bits_read;
  int received_data[4];
} Receiver;


extern Receiver receiverL;
extern Receiver receiverR;





void receive_logic(Receiver& r);


#endif