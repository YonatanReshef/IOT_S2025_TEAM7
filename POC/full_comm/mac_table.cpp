#include <esp_now.h>
#include <WiFi.h>
#include "mac_table.h"
#include "globals.h"
#include <esp_wifi.h>


struct_message myData;

// Table of known MACs (each is 6 bytes)
uint8_t knownMacs[MAX_MACS][6];
int macCount = 0;

// Get our own MAC address
uint8_t selfMac[6];
uint8_t broadcast[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


// Helper to compare MACs (returns -1, 0, 1 like strcmp)
int compareMacs(const uint8_t* a, const uint8_t* b) {
  for (int i = 0; i < 6; i++) {
    if (a[i] < b[i]) return -1;
    if (a[i] > b[i]) return 1;
  }
  return 0;
}

// Insert MAC into sorted table (if not already there)
void insertMac(const uint8_t* mac) {
  // Check if already exists
  for (int i = 0; i < macCount; i++) {
    if (compareMacs(mac, knownMacs[i]) == 0) return;
  }

  // Prevent overflow
  if (macCount >= MAX_MACS) return;

  // Find insert position
  int pos = 0;
  while (pos < macCount && compareMacs(mac, knownMacs[pos]) > 0) pos++;

  // Shift others to the right
  for (int i = macCount; i > pos; i--) {
    memcpy(knownMacs[i], knownMacs[i - 1], 6);
  }

  // Insert new MAC
  memcpy(knownMacs[pos], mac, 6);
  macCount++;
}

void printMacTable() {
  // Print updated table
  Serial.println("=== MAC Address Table ===");
  for (int i = 0; i < macCount; i++) {
    for (int j = 0; j < 6; j++) {
      Serial.printf("%02X", knownMacs[i][j]);
      if (j < 5) Serial.print(":");
    }
    Serial.println();
  }
  Serial.println("=========================");
}


void readMacAddress(){
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, ownMac);
  if (ret != ESP_OK) {
    Serial.println("Failed to read own MAC address");
  }
}

// Setup
void mac_map_setup() {
  WiFi.mode(WIFI_STA);

  readMacAddress();

  // Get own MAC and insert it
  esp_read_mac(selfMac, ESP_MAC_WIFI_STA);
  insertMac(selfMac);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // setup handlers
  esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);

  // ==== setup hello broadcast ====
  strcpy(myData.msg, "hello");

  // Add peer if not already added (ESP-NOW needs this)
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcast, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (!esp_now_is_peer_exist(broadcast)) {
    esp_now_add_peer(&peerInfo);
  }
  // ==============================

}
