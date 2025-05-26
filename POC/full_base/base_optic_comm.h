#ifndef BASE_OPTIC_COMM_H
#define BASE_OPTIC_COMM_H

#include <tuple>

#pragma once

// Transmission data: 6-bit preamble + 4-bit message
extern const int TRANSMISSION_SIZE;
extern int send_dataL[12];
extern int send_dataR[12];

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
  int ticksWaitPreamble;
  int sync_val;
  int bits_read;
  int received_data[6];
} Receiver;


extern Receiver receiverL;
extern Receiver receiverR;



int find_mac_index(const uint8_t* mac);
void update_optic_data();
void readMacAddress();

int receive_logic(Receiver& r);
int binaryArrayToInt(int* binary_arr, int size);
void update_side_macs(int leftId, int rightId);
void copy_mac(uint8_t* dest, const uint8_t* src);
void default_mac(uint8_t* mac);


#endif