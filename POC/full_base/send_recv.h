#ifndef SEND_RECV_H
#define SEND_RECV_H

int checkMacExists(const uint8_t *mac);
int compareMacs(const uint8_t* a, const uint8_t* b);
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

#endif