#ifndef SIDE_MSG_H
#define SIDE_MSG_H

#pragma once

extern esp_now_peer_info_t peerNow;
extern struct_message msgData;


void send_side(int side, const uint8_t *dest_addr);




#endif