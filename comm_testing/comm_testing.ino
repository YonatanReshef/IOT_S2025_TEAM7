
#include <Arduino.h>
#include "espTransceiver.h"


void setup() {
    Serial.begin(9600);
    sleep(1);

    // init all others
    ESPTransceiver::getInstance().setup();

    sleep(1);
    Serial.println("Setup Success");
}


void loop() {

    // Create a test message
    ESPTransceiver::BallCrossingMessage msg;
    msg.side = 1;
    msg.idx = 7;

    // Send it to device 0 (adjust if needed)
    ESPTransceiver::getInstance().send(0, ESPTransceiver::BALL_CROSSING, (char*)&msg);

    Serial.println("Test message sent.");
    delay(2000);

}
