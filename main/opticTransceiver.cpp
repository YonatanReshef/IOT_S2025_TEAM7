
#include "OpticTransceiver.h"
#include <Arduino.h>


OpticTransceiver::OpticTransceiver(int sender_pin, int receiver_pin)
  : trasmitter{sender_pin, 0}, receiver{receiver_pin, WAIT_PREAMBLE, 0, 0, 0, {0}, -1}, tick(0)
{}

void OpticTransceiver::setMessage(int msg){
  // Calculate the preamble size
  const int PREAMBLE_SIZE = TRANSMISSION_SIZE - MESSAGE_SIZE - 1; // |msg| + |zero_bit|

  // Write the preamble: PREAMBLE_SIZE - 1 ones, then a 0
  for (int i = 0; i < PREAMBLE_SIZE - 1; ++i) {
    trasmitter.send_data[i] = 1;
  }
  trasmitter.send_data[PREAMBLE_SIZE - 1] = 0;

  // Extract and write the 4 LSBs of the message
  int masked_msg = msg & 0xF; // 0b1111

  for (int i = 0; i < MESSAGE_SIZE; ++i) {
    trasmitter.send_data[PREAMBLE_SIZE + i] = (masked_msg >> i) & 1;
  }

  // zero bit
  trasmitter.send_data[PREAMBLE_SIZE + MESSAGE_SIZE] = 0;
}

void OpticTransceiver::transmitLogic(){
  if (tick % BIT_PERIOD_MS == 0) {
    int outputValue = trasmitter.send_data[trasmitter.current_bit] * PWM_MAX;
    analogWrite(trasmitter.analogOutPin, outputValue);
    trasmitter.current_bit = (trasmitter.current_bit + 1) % TRANSMISSION_SIZE;
  }
}


/*
  Sets the receiver.msg to be the msg received.
  Succsesful recv sets the msg.
  If a preamble read fails, or stopbit fails, the an invalid read occurs and msg =-1

  While none of the events occur, the msg values does not change.
*/
void OpticTransceiver::receiveLogic(){
    switch (receiver.state) {
    case WAIT_PREAMBLE:
      if (tick % SAMPLE_INTERVAL_MS == 0) {
        int sensorValue = analogRead(receiver.analogInPin);
        if (sensorValue < LIGHT_THRESHOLD) {
          receiver.ticksOnPreamble += SAMPLE_INTERVAL_MS;
        } else {
          if (receiver.ticksOnPreamble >= PREAMBLE_DURATION_MS) {
            receiver.state = GET_DATA;
          }
          else{
            receiver.msg = -1;
          }
          receiver.ticksOnPreamble = 0;
          receiver.sync_val = tick % BIT_PERIOD_MS;
        }
      }
      break;

    case GET_DATA:
      if (tick % BIT_PERIOD_MS == receiver.sync_val) {
        int sensorValue = analogRead(receiver.analogInPin);
        int bit = (sensorValue < LIGHT_THRESHOLD) ? 1 : 0;

        if (receiver.bits_read < MESSAGE_SIZE) {
          receiver.received_data[receiver.bits_read] = bit;
        }
        else if(receiver.bits_read == MESSAGE_SIZE){ // ZERO_BIT - now reading zero_bit
          int zero_bit = bit;

          if(zero_bit != 0){ // error
            receiver.msg = -1;
            receiver.bits_read = 0;
            receiver.state = WAIT_PREAMBLE;
            receiver.ticksOnPreamble = 0;
          }

        }   
        else if (receiver.bits_read == MESSAGE_SIZE + 1) { // STOP_BIT - now reading stop_bit
          receiver.bits_read = 0;
          receiver.state = WAIT_PREAMBLE;
          receiver.ticksOnPreamble = BIT_PERIOD_MS;
          
          int stop_bit = bit;
          // Serial.print("[PIN ");
          // Serial.print(receiver.analogInPin);
          // Serial.print("] Received: ");
          // for (int i = 0; i < MESSAGE_SIZE; ++i) {
            //   Serial.print(receiver.received_data[i]);
            // }
            // Serial.println();
            if (stop_bit == 1) {
              // Serial.println("Valid.");
              
              // build msg:
              receiver.msg = 0;
              for(int i = 0; i < MESSAGE_SIZE; ++i){
                receiver.msg |= receiver.received_data[i] << i;
              }
              //===========
              
            } else {
              // Serial.println("Invalid message: missing stop bit.");
              receiver.msg = -1;
            }
            // Serial.println("===========");
          }
          receiver.bits_read++;
      }
      break;
  }
}

void OpticTransceiver::setup(int msg){
  pinMode(trasmitter.analogOutPin, OUTPUT);
  setMessage(msg);
}

int OpticTransceiver::update(int dt){
  tick += dt;
  tick = tick % (BIT_PERIOD_MS * SAMPLE_INTERVAL_MS); // Avoid overflow

  // TRANSMIT
  transmitLogic();
  
  // RECEIVE
  receiveLogic();

  return receiver.msg;
}
