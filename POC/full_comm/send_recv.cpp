#include <esp_now.h>
#include <WiFi.h>
#include "mac_table.h"
#include "side_msg.h"
#include "globals.h"
#include <Arduino.h>
#include "optic_comm.h"


bool checkMacExists(const uint8_t *mac) {
  if((compareMacs(mac, rightMac) == 0) || (compareMacs(mac, leftMac) == 0)) {
    return true;  // MAC exists in known sides
  }
  return false;  // MAC does not exist in known sides
}


// ESP-NOW recv callback
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  if (((char)incomingData[0] == 'r' || (char)incomingData[0] == 'l')) {
    if(!checkMacExists(mac)) {
      Serial.println("Received message from unknown MAC, ignoring");
      Serial.print("Known MACs: ");
      for (int i = 0; i < 6; i++){
        Serial.printf("%02X", rightMac[i]);
        if (i < 5) Serial.print(":");
      }
      Serial.print(" and ");
      for (int i = 0; i < 6; i++){
        Serial.printf("%02X", leftMac[i]);
        if (i < 5) Serial.print(":");
      }
      Serial.println();
      Serial.print("Received MAC: ");
      for (int i = 0; i < 6; i++) {
        Serial.printf("%02X", mac[i]);
        if (i < 5) Serial.print(":");
      }
      Serial.println();
      Serial.println("=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
      return;  // Ignore messages from unknown MACs
    }
    
    if((char)incomingData[0] == 'r') {
      Serial.print("Received right side message from known MAC: ");
      for (int i = 0; i < 6; i++) {
        Serial.printf("%02X", mac[i]);
        if (i < 5) Serial.print(":");
      }
      Serial.println("=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
    } else if ((char)incomingData[0] == 'l') {
      Serial.print("Received left side message from known MAC: ");
      for (int i = 0; i < 6; i++) {
        Serial.printf("%02X", mac[i]);
        if (i < 5) Serial.print(":");
      }
      Serial.println("=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
    } else {
      Serial.println("Unknown message received");
    }

    return;
  }

  insertMac(mac);  // Add sender MAC to list
  update_optic_data();  // Update data to send
}

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  //Serial.print("\r\nLast Packet Send Status:\t");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}