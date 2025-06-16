
#include "config.h"
#include "clock.h"
#include "manager.h"
#include <Arduino.h>


namespace {
    Clock my_clock(DELTA_TIME);
    Manager my_manager;
}

void setup() {
  Serial.begin(9600);
  sleep(1);
  
  // init all others
  my_manager.setup();
  
  sleep(1);
  Serial.println("Setup Success");
}


void loop() {
  
  int dt = my_clock.tick();
  dt = DELTA_TIME;
  /* 
  LOOP LOGIC 
  use dt instead of tick
  */
  my_manager.update(dt);
}
