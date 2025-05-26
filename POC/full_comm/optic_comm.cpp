#include "optic_comm.h"
#include "globals.h"
#include "mac_table.h"
#include <tuple>  // Required for std::tuple
#include <Arduino.h>
#include "side_msg.h"

Receiver receiverL = {.analogInPin = 33 , WAIT_PREAMBLE, 0, 0, 0, {0}};
Receiver receiverR = {.analogInPin = 32 , WAIT_PREAMBLE, 0, 0, 0, {0}};

// Transmission data: 6-bit preamble + 4-bit message
const int TRANSMISSION_SIZE = 10;
int send_data[TRANSMISSION_SIZE] = {1, 1, 1, 1, 1, 0, 1, 1, 1, 1}; 
//                                 |----preamble----|----data----|

// Transmission state
int current_bit = 0;


const int MESSAGE_SIZE = 4; // 4 data bits

// Transmission configuration
const int PWM_MAX = 255;
const int BIT_PERIOD_MS = 100;
const int SAMPLE_INTERVAL_MS = 10;

// Thresholds
const int LIGHT_THRESHOLD = 250;
const int PREAMBLE_DURATION_MS = 500;



int find_mac_index(const uint8_t* mac) {
  for (int i = 0; i < macCount; i++) {
    if (compareMacs(knownMacs[i], mac) == 0) {
      return i;
    }
  }
  return -1; // Not found
}


void update_optic_data() {
    int index = find_mac_index(ownMac);
    for (int i = 0; i < MESSAGE_SIZE; ++i) {
        int data_idx = 6 + i; // Data starts after preamble
        send_data[data_idx] = (index >> (MESSAGE_SIZE - 1 - i)) & 1;
    }
}


int binaryArrayToInt(int* binary_arr, int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result = (result << 1) | binary_arr[i];  // Shift left and add bit
    }
    return result;
}



// Receive logic function
int receive_logic(Receiver& r) {
  switch (r.state) {
    case WAIT_PREAMBLE:
      if (tick % SAMPLE_INTERVAL_MS == 0) {
        int sensorValue = analogRead(r.analogInPin);
        if (sensorValue < LIGHT_THRESHOLD) {
          r.ticksOnPreamble += SAMPLE_INTERVAL_MS;
        } else {
          if (r.ticksOnPreamble >= PREAMBLE_DURATION_MS) {
            r.state = GET_DATA;
          }
          r.ticksOnPreamble = 0;
          r.sync_val = tick % BIT_PERIOD_MS;
        }
      }
      break;

    case GET_DATA:
      if (tick % BIT_PERIOD_MS == r.sync_val) {
        int sensorValue = analogRead(r.analogInPin);
        int bit = (sensorValue < LIGHT_THRESHOLD) ? 1 : 0;

        if (r.bits_read < MESSAGE_SIZE) {
          r.received_data[r.bits_read] = bit;
        }

        r.bits_read++;

        if (r.bits_read == MESSAGE_SIZE + 1) {
          r.bits_read = 0;
          r.state = WAIT_PREAMBLE;
          r.ticksOnPreamble = BIT_PERIOD_MS;

          int stop_bit = bit;
          //Serial.print("[PIN ");
          //Serial.print(r.analogInPin);
          //Serial.print("] Received: ");
          //for (int i = 0; i < MESSAGE_SIZE; ++i) {
          //  Serial.print(r.received_data[i]);
          //}
          //Serial.println();
          if (stop_bit == 1) {
            //Serial.println("Valid.");
            //Serial.println("===========");
            int received_id = binaryArrayToInt(r.received_data, MESSAGE_SIZE);
            return received_id; // Return the received data
          } else {
            //Serial.println("Invalid message: missing stop bit.");
            //Serial.println("===========");
            return -1; // Return null for invalid message
          }
          
        }
      }
      break;
  }

  return -2; // Return null if no data is ready
}



std::tuple<int, int> optic_comm(int tick){

    tick = tick % (BIT_PERIOD_MS * SAMPLE_INTERVAL_MS); // Avoid overflow

    // TRANSMIT
    if (tick % BIT_PERIOD_MS == 0) {
        int outputValue = send_data[current_bit] * PWM_MAX;
        analogWrite(analogOutPin, outputValue);
        current_bit = (current_bit + 1) % TRANSMISSION_SIZE;
    }

    // RECEIVE
    int resultL = receive_logic(receiverL);
    int resultR = receive_logic(receiverR);

    return std::make_tuple(resultL, resultR);

}


bool is_mac_empty(const uint8_t* mac) {
  for (int i = 0; i < 6; i++) {
    if (mac[i] != 0xFF) return false;
  }
  return true;
}


void update_side_macs(int leftId, int rightId) {
  if (leftId >= macCount) {
    //Serial.print("Left ID: ");
    //Serial.println(leftId);
    //Serial.println(" exceeds known MACs count, ignoring.");
  }
  else if (leftId == -1) {
    if(is_mac_empty(leftMac)) {
      //Serial.println("No left ID, ignoring.");
    } else {
      for (int i = 0; i < 6; i++) {
        leftMac[i] = 0xFF;
      }
    }
  }
  else if(leftId >= 0 && leftId < macCount) {
    for (int i = 0; i < 6; i++) {
      leftMac[i] = knownMacs[leftId][i];
    }
    
    send_side(0, leftMac); // Send left side message
  }

  if (rightId >= macCount) {
    //Serial.print("Right ID: ");
    //Serial.println(rightId);
    //Serial.println(" exceeds known MACs count, ignoring.");
  }
  else if (rightId == -1) {
    if(is_mac_empty(rightMac)) {
      //Serial.println("No right ID, ignoring.");
    } else {
      //Serial.println("right ID gone.");
      for (int i = 0; i < 6; i++) {
        rightMac[i] = 0xFF;
      }
    }
  }
  else if (rightId >= 0 && rightId < macCount) { 
    for (int i = 0; i < 6; i++) {
      rightMac[i] = knownMacs[rightId][i];
    }
    
    send_side(1, rightMac); // Send right side message
  }
}
