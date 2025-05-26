#include "optic_comm.h"
#include "globals.h"
#include "mac_table.h"
#include "side_msg.h"
#include "send_recv.h"
#include "light_matrix.h"
#include <tuple>  // Required for std::tuple
#include <Arduino.h>
#include <esp_now.h>


void setup() {
  Serial.begin(9600);
  sleep(1);
  pinMode(analogOutPin, OUTPUT);

  mac_map_setup();
  matrix_setup();
  Serial.println("Setup Success");
}

void loop() {
  tick++;

  if(tick % 2000 == 0 ) {
      //printMacTable();
      esp_now_send(broadcast, (uint8_t *) &myData, sizeof(myData));
  }
  std::tuple<int, int> recieved_ids = optic_comm(tick);
  int idL = std::get<0>(recieved_ids);
  int idR = std::get<1>(recieved_ids);

  update_side_macs(idL, idR);

  delay(1);
}
