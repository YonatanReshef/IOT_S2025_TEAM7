
#include "clock.h"
#include "boardLayout.h"
#include <Arduino.h>


#define DELAY_TIME 10 

namespace {
    Clock my_clock(DELAY_TIME);
    
    // temp
    BoardLayout bl(0);
}

void setup() {
  Serial.begin(9600);
  sleep(1);
  
  // init all others
  bl.setup();
  
  sleep(1);
  Serial.println("Setup Success");
}


void loop() {
  
  int dt = my_clock.tick();
  dt = DELAY_TIME;
  /* 
  LOOP LOGIC 
  use dt instead of tick
  */
  bl.update(dt);
  
  // Serial.print("Loop!");
  // Serial.println(dt);
}
