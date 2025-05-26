#include <esp_now.h>
#include <WiFi.h>
#include <Arduino.h>

#include "globals.h"
#include "side_msg.h"

esp_now_peer_info_t peerNow;
struct_message msgData;
 
void send_side(int side, const uint8_t *dest_addr) {

    memcpy(peerNow.peer_addr, dest_addr, 6);
    peerNow.channel = 0; // Use correct WiFi channel
    peerNow.encrypt = false;

    if (!esp_now_is_peer_exist(dest_addr)) {
        if(esp_now_add_peer(&peerNow) != ESP_OK) {
            Serial.println("Failed to add peer");
            return;
        }
    }

    // Send message via ESP-NOW
    if (side == 1) {
        strcpy(msgData.msg, "r");
    } else if (side == 0) {
        strcpy(msgData.msg, "l");
    } else {
        Serial.println("Invalid side specified");
        return;
    }

    esp_err_t result = esp_now_send(dest_addr, (uint8_t *) &msgData, sizeof(msgData));
    if (result != ESP_OK) {
        Serial.println("Error sending the data");
        return;
    }

    //Serial.print("Sent message: ");
    //Serial.println(msgData.msg);
    //Serial.print("To MAC: ");
    //for (int i = 0; i < 6; i++) {
    //    Serial.printf("%02X", dest_addr[i]);
    //    if (i < 5) Serial.print(":");
    //}
    //Serial.println();
    //Serial.println("==========================");

}