#ifndef SIDE_MSG_H
#define SIDE_MSG_H

#include <esp_now.h>
#include <WiFi.h>

#pragma once

// Message structure
typedef struct struct_message {
  char msg[32];
} struct_message;


extern esp_now_peer_info_t peerNow;
extern struct_message msgData;


void send_side(int side, const uint8_t *dest_addr);




#endif