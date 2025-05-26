#include "base_optic_comm.h"
#include "globals.h"
#include <Arduino.h>
#include "side_msg.h"
#include "light_matrix.h"
#include "send_recv.h"
#include <WiFi.h>
#include <esp_wifi.h>




// Communication using LED and light sensor via PWM and analog read.


// Transmission configuration
const int PWM_MAX = 255;
const int BIT_PERIOD_MS = 100;
const int SAMPLE_INTERVAL_MS = 10;

// Thresholds
const int LIGHT_THRESHOLD = 250;
const int PREAMBLE_DURATION_MS = 500;

// Transmission data: 6-bit preamble + 4-bit message
const int TRANSMISSION_SIZE = 10;
int send_data[TRANSMISSION_SIZE] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0}; 
//                                 |----preamble----|----data----|

// Transmission state
int current_bit = 0;

const int MESSAGE_SIZE = 4; // 4 data bits


Receiver receiverL = {.analogInPin = 33 , WAIT_PREAMBLE, 0, 0, 0, 0, {0}};
Receiver receiverR = {.analogInPin = 32 , WAIT_PREAMBLE, 0, 0, 0, 0, {0}};




void readMacAddress(){
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, ownMac);
  if (ret == ESP_OK) {
    /*Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                  baseMac[0], baseMac[1], baseMac[2],
                  baseMac[3], baseMac[4], baseMac[5]);*/
  } else {
    Serial.println("Failed to read MAC address");
  }
}

int find_mac_index(const uint8_t* mac) {
  int numMacs = sizeof(baseMacs) / sizeof(*baseMacs);
  Serial.print("numMacs: ");
  Serial.println(numMacs);
  for (int i = 0; i < numMacs; i++) { //3 is num of macs
    if (compareMacs(baseMacs[i], mac) == 0) {
      return i;
    }
  }
  return -1; // Not found
}


void update_optic_data() {
    readMacAddress();
    int index = find_mac_index(ownMac);
    Serial.print("Updated MAC index: ");
    Serial.println(index);
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
          r.ticksWaitPreamble = 0;
          r.ticksOnPreamble += SAMPLE_INTERVAL_MS;
        } else {
          if (r.ticksWaitPreamble >= PREAMBLE_DURATION_MS * 1.5){
            r.ticksWaitPreamble = 0;
            return -3;
          }
          if (r.ticksOnPreamble >= PREAMBLE_DURATION_MS) {
            r.state = GET_DATA;
          }

          r.ticksOnPreamble = 0;
          r.ticksWaitPreamble += SAMPLE_INTERVAL_MS;
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
          /*Serial.print("[PIN ");
          if(r.analogInPin == 33){
            Serial.print("L");
          } else if(r.analogInPin == 32){
            Serial.print("R");
          }
          Serial.print("] Received: ");*/
          int id = binaryArrayToInt(r.received_data, MESSAGE_SIZE);
          /*for (int i = 0; i < MESSAGE_SIZE; ++i) {
            Serial.print(r.received_data[i]);
          }
          Serial.println();*/

          

          if (stop_bit == 1) {
            return id;
            Serial.println("===========");
            //Serial.println("Valid.");
          } else {
            Serial.println("Invalid message: missing stop bit.");
            return -1;
          }
        }
      }
      break;
  }
  return -2;
}

/*void loop() {
  tick++;
  tick = tick % (BIT_PERIOD_MS * SAMPLE_INTERVAL_MS); // Avoid overflow

  // TRANSMIT
  if (tick % BIT_PERIOD_MS == 0) {
    int outputValue = send_data[current_bit] * PWM_MAX;
    analogWrite(analogOutPin, outputValue);
    current_bit = (current_bit + 1) % TRANSMISSION_SIZE;
  }

  // RECEIVE
  receive_logic(receiverL);
  receive_logic(receiverR);

  delay(1);
}*/


void copy_mac(uint8_t* dest, const uint8_t* src) {
    for (int i = 0; i < 6; i++) {
        dest[i] = src[i];
    }
}

void default_mac(uint8_t* mac) {
    for (int i = 0; i < 6; i++) {
        mac[i] = 0xFF;
    }
}


void update_side_macs(int idL, int idR){
  bool leftChanged = false;
  bool rightChanged = false;

  if (idL != leftId && idL != -2) {
      leftId = idL;
      leftChanged = true;
      if (leftId >= 0 && leftId < 3) {
          Serial.print("Updating left mac with id: ");
          Serial.println(leftId);
          copy_mac(leftMac, baseMacs[leftId]);
          Serial.print("Drawing left matrix");
          drawNeighborMatrix(0, 1, pixels.Color(0, 0, 255), pixels.Color(255, 255, 255));
          pixels.show();
      }
      else if(leftId == -3 || leftId == -1){
          Serial.println("Defaulting left mac");
          default_mac(leftMac);
      }
  }
  else{
      leftChanged = false;
  }


  if (idR != rightId && idR != -2) {
      rightId = idR;
      rightChanged = true;
      if(rightId >= 0 && rightId < 3) {
          Serial.print("Updating right mac with id: ");
          Serial.println(rightId);
          copy_mac(rightMac, baseMacs[rightId]);
          Serial.print("Drawing right matrix");
          drawNeighborMatrix(1, 1, pixels.Color(0, 0, 255), pixels.Color(255, 255, 255));
          pixels.show();
      }
      else if(rightId == -3 || rightId == -1) {
          Serial.println("Defaulting right mac");
          default_mac(rightMac);
      }
  }
  else{
      rightChanged = false;
  }

  if(leftChanged) {
    Serial.print("Left mac: ");
    for (int i = 0; i < 6; i++) {
      Serial.print(leftMac[i], HEX);
      if (i < 5) Serial.print(":");
    }
    Serial.println("=-------------------------------------");

    if (leftId >= 0 && leftId < 3) {
      //send_side(0, leftMac);
    }
    else if(leftId == -3 || leftId == -1) {
      drawNeighborMatrix(0, 1, pixels.Color(0, 0, 0),   pixels.Color(0, 0, 0));  // Top neighbor, top row red
      pixels.show();
    }
    
  }

  if(rightChanged) {
    Serial.print("Right mac: ");
    for (int i = 0; i < 6; i++) {
      Serial.print(rightMac[i], HEX);
      if (i < 5) Serial.print(":");
    }
    Serial.println("=-------------------------------------");

    if (rightId >= 0 && rightId < 3) {
      //send_side(1, rightMac);
    }
    else if(rightId == -3 || rightId == -1) {
      // Test neighbors on all four sides
      drawNeighborMatrix(1, 1, pixels.Color(0, 0, 0),   pixels.Color(0, 0, 0));  // Top neighbor, top row red
      pixels.show();
    }
  }


  /*if(tick % 2058 == 0){
    if(leftId >= 0 && leftId < 3) {
      Serial.print("Sending left side message to: ");
      for (int i = 0; i < 6; i++) {
        Serial.print(leftMac[i], HEX);
        if (i < 5) Serial.print(":");
      }
      Serial.println();
      //send_side(0, leftMac);
    }
  
    if(rightId >= 0 && rightId < 3) {
        Serial.print("Sending right side message to: ");
        for (int i = 0; i < 6; i++) {
          Serial.print(rightMac[i], HEX);
          if (i < 5) Serial.print(":");
        }
        Serial.println();
        //send_side(1, rightMac);
    }
  }
  */

  
}
