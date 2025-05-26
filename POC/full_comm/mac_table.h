#ifndef MAC_TABLE_H
#define MAC_TABLE_H

#include <cstdint>
#include <esp_now.h>

#pragma once

#define MAX_MACS 5

// Message structure
typedef struct struct_message {
  char msg[32];
} struct_message;

extern struct_message myData;

// Table of known MACs (each is 6 bytes)
extern uint8_t knownMacs[MAX_MACS][6];
extern int macCount;

// Get our own MAC address
extern uint8_t selfMac[6];
extern uint8_t broadcast[];


int compareMacs(const uint8_t* a, const uint8_t* b);
void insertMac(const uint8_t* mac);
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void printMacTable();

void mac_map_setup();


#endif