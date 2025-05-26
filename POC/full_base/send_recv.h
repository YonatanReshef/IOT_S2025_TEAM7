#ifndef SEND_RECV_H
#define SEND_RECV_H



bool checkMacExists(const uint8_t *mac);
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

#endif