#include "optic_comm.h"
#include "globals.h"
#include "mac_table.h"
#include "side_msg.h"
#include "send_recv.h"
#include "light_matrix.h"
#include <tuple>  // Required for std::tuple
#include <Arduino.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>


void setup() {
  Serial.begin(9600);
  sleep(1);
  pinMode(analogOutPin, OUTPUT);

  //mac_map_setup();
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // setup handlers
  esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);



  matrix_setup();
  Serial.println("Setup Success");
}

void loop() {
  tick++;

  //if(tick % 2000 == 0 ) {
  //    printMacTable();
  //    esp_now_send(broadcast, (uint8_t *) &myData, sizeof(myData));
  //}
  std::tuple<int, int> recieved_ids = optic_comm(tick);
  int idL = std::get<0>(recieved_ids);
  int idR = std::get<1>(recieved_ids);

  if(idL != leftId && idL != -2) {
    Serial.print("Left ID: ");
    Serial.println(idL);
    leftId = idL;
    update_side_macs(leftId, rightId);
  }
  if(idR != rightId && idR != -2) {
    Serial.print("Right ID: ");
    Serial.println(idR);
    rightId = idR;
    update_side_macs(leftId, rightId);
  }

  delay(1);
}
