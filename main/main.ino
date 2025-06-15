
#include "config.h"
#include "clock.h"
#include "manager.h"
#include <Arduino.h>


namespace {
    Clock my_clock(DELAY_TIME);
    Manager manager();
}

void setup() {
  Serial.begin(9600);
  sleep(1);
  
  // init all others
  manager.setup();
  
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
  manager.update(dt);
}
