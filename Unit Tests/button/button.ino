#include <Arduino.h>
#include "Button.h"

Button testButton(4);  // Use GPIO 5 or any digital pin connected to your button

void setup() {
    Serial.begin(115200);
    testButton.setup();
    Serial.println("Button test started. Press the button...");
}

void loop() {
    // Update button state; dt not used currently, so pass 0
    testButton.update(0);

    // Check for click
    if (testButton.getClick()) {
        Serial.println("Button clicked!");
    }

    // Optional: print raw state (for debugging)
    // Serial.println(digitalRead(5));

    delay(10);  // Small delay to prevent flooding Serial Monitor
}
