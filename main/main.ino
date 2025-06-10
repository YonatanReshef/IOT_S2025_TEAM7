
#include "clock.h"

#define DELAY_TIME 10 

namespace {
    Clock my_clock(DELAY_TIME);
}

void setup() {
  Serial.begin(9600);
  sleep(1);
  
  // init all others
  
  sleep(1);
  Serial.println("Setup Success");
}


void loop() {

    int dt = my_clock.tick();
    
    /* 
    LOOP LOGIC 
    use dt instead of tick
    */
   
    Serial.print("Loop!");
    Serial.println(dt);

}
