/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground through 220 ohm resistor

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/analog/AnalogInOutSerial/
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = 2;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 12;  // Analog output pin that the LED is attached to

int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value output to the PWM (analog out)
int state = 0;
int tick = 0;

int ticksOnPreamble = 0; // 500
int sync_val = 0;
int bits_read = 0;

int send_data[10] = {1, 1, 1, 1, 1, 0, 1, 0, 1, 1};
//                  |----preamble----|----data----|
int current_bit = 0;

enum StateMachine{
  WAIT_PREAMBLE,
  GET_DATA
};

enum StateMachine recv_state;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  recv_state = WAIT_PREAMBLE;
}

void loop() {

  tick += 1;

  // transmit
  if(tick % 100 == 0){
    outputValue = send_data[current_bit] * 255;
    analogWrite(analogOutPin, outputValue);
    current_bit = (current_bit + 1) % 10;

    // Serial.print("read: ");
    // Serial.println(sensorValue);
    // Serial.print("state: ");
    // Serial.println(recv_state);
  }

  switch (recv_state){
    case WAIT_PREAMBLE:
      // read
      if(tick % 10 == 0){
        // Serial.print("ticksOnPreamble: ");
        // Serial.println(ticksOnPreamble);
        // read the analog in value:
        sensorValue = analogRead(analogInPin);
        if (sensorValue < 250){ // white
          ticksOnPreamble += 10;
        } 
        else{
          if(ticksOnPreamble > 500){ // threashold
            recv_state = GET_DATA;
          } 
          ticksOnPreamble = 0;
          sync_val = tick % 100;
        }
      }
      break;

    case GET_DATA:
      if(tick % 100 == sync_val){
        // read the analog in value:
        sensorValue = analogRead(analogInPin);
        Serial.print(sensorValue < 250 ? 1 : 0);
        bits_read++;

        if(bits_read == 4){
          bits_read = 0;
          recv_state = WAIT_PREAMBLE;
          Serial.println("");
          Serial.println("===========");
        }
      }

      break;
  }

  delay(1);
}
