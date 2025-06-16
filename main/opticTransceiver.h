#ifndef OPTIC_TRANSCEIVER
#define OPTIC_TRANSCEIVER

class OpticTransceiver
{
  private:

  /* ==== Config ==== */
  
  // Transmission configuration
  static const int PWM_MAX = 255;
  static const int BIT_PERIOD_MS = 100;
  static const int SAMPLE_INTERVAL_MS = 10;

  // Thresholds
  static const int LIGHT_THRESHOLD = 250;
  static const int PREAMBLE_DURATION_MS = 500;

  // Bits
  static const int TRANSMISSION_SIZE = 10;
  static const int MESSAGE_SIZE = 4;

  /* ==== Transmitter ==== */

  typedef struct {
    int analogOutPin;
    int current_bit;
    // Transmission data: 6-bit preamble + 4-bit message
    int send_data[TRANSMISSION_SIZE]; // = {1, 1, 1, 1, 1, 0, 1, 0, 1, 1}; 
    //                                    |----preamble----|----data----|
  } Transmitter;

  Transmitter trasmitter;
  /* ==== Receiver ==== */
  
  // Receiver state machine
  enum StateMachine {
    WAIT_PREAMBLE,
    GET_DATA
  };
  
  typedef struct {
    int analogInPin;
    StateMachine state;
    int ticksOnPreamble;
    int sync_val;
    int bits_read;
    int received_data[MESSAGE_SIZE];
    int msg; // -1 for no msg
  } Receiver;
  
  Receiver receiver;

  /* ==== General State ==== */

  int tick;

  /* ==== inner funcs ==== */
  void transmitLogic();
  void receiveLogic();

  public:
  // 4-bit msg
  OpticTransceiver(int sender_pin, int receveier_pin);
  ~OpticTransceiver() = default;
  
  void setMessage(int msg);
  void setup(int msg);
  int update(int dt);
};

#endif