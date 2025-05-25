// Communication using LED and light sensor via PWM and analog read.

// Pin configuration
const int analogOutPin = 12;     // PWM output pin for LED

// Transmission configuration
const int PWM_MAX = 255;
const int BIT_PERIOD_MS = 100;
const int SAMPLE_INTERVAL_MS = 10;

// Thresholds
const int LIGHT_THRESHOLD = 250;
const int PREAMBLE_DURATION_MS = 500;

// Transmission data: 6-bit preamble + 4-bit message
const int TRANSMISSION_SIZE = 10;
int send_data[TRANSMISSION_SIZE] = {1, 1, 1, 1, 1, 0, 1, 0, 1, 1}; 
//                                 |----preamble----|----data----|

// Transmission state
int current_bit = 0;
int tick = 0;

const int MESSAGE_SIZE = 4; // 4 data bits

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
  int received_data[MESSAGE_SIZE];
} Receiver;


Receiver receiverL = {.analogInPin = 4 , WAIT_PREAMBLE, 0, 0, 0, {0}};
Receiver receiverR = {.analogInPin = 2 , WAIT_PREAMBLE, 0, 0, 0, {0}};


// Receive logic function
void receive_logic(Receiver& r) {
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
          Serial.print("[PIN ");
          Serial.print(r.analogInPin);
          Serial.print("] Received: ");
          for (int i = 0; i < MESSAGE_SIZE; ++i) {
            Serial.print(r.received_data[i]);
          }
          Serial.println();
          if (stop_bit == 1) {
            Serial.println("Valid.");
          } else {
            Serial.println("Invalid message: missing stop bit.");
          }
          Serial.println("===========");
        }
      }
      break;
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(analogOutPin, OUTPUT);
}

void loop() {
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
}
