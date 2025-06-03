#ifndef OPTIC_COMM_H
#define OPTIC_COMM_H

#include <tuple>

#pragma once

// Transmission data: 6-bit preamble + 4-bit message
extern const int TRANSMISSION_SIZE;
extern int send_data[10];

// Transmission state
extern int current_bit;


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





int find_mac_index(const uint8_t* mac);
void update_optic_data();
int receive_logic(Receiver& r);
std::tuple<int, int> optic_comm(int tick);
int binaryArrayToInt(int* binary_array, int size=4);
bool is_mac_empty(const uint8_t* mac);
void update_side_macs(int leftId, int rightId);

#endif