//
// Created on 6/13/2025.
//

#ifndef IOT_S2025_TEAM7_ESPTRANSCIEVER_H
#define IOT_S2025_TEAM7_ESPTRANSCIEVER_H

#include <WiFi.h>
#include <esp_wifi.h>
#include <queue>

class ESPTransceiver
{
    private:
        // add all the macs
        const uint8_t knownMacs[macCount][6] = {
            {0xB0, 0xA7, 0x32, 0xD7, 0x84, 0x3C},
            {0xCC, 0xDB, 0xA7, 0x5A, 0x5B, 0x1C},
            {0xF4, 0x65, 0x0B, 0xE9, 0x5E, 0x34}
        };

        const int macCount = 3;

        const uint8_t broadcast[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        const int broadcast_id = -1;

        uint8_t selfMac[6];

        std::queue<BallCrossingMessage> ballCrossingQueue;
        std::queue<GameInitMessage> gameInitQueue;
        std::queue<VictoryMessage> victoryQueue;
        std::queue<ReadyInitMessage> readyInitQueue;
        std::queue<ReadyConnectMessage> readyConnectQueue;
        std::queue<AckMessage> ackQueue;

        void onSendWrapper(const uint8_t* mac_addr, esp_now_send_status_t status);
        void onReceiveWrapper(const uint8_t* mac, const uint8_t* incomingData, int len);

        int getStructSize(MessageType msgType);

public:

    void setup();

    void send(int idReceiver, MessageType msgType, size_t msgSize, char* msg);

    int getId(uint8_t mac[6]);

    enum MessageType {
        BALL_CROSSING,
        GAME_INIT,
        VICTORY,
        READY_INIT,
        READY_CONNECT,
        ACK

    };

    typedef struct {
        int side;
        int idx;
    } BallCrossingMessage;

    typedef struct {
        int game_idx;
        int perp_mat[4];
    } GameInitMessage;

    typedef struct {
        int no_need_yet;
    } VictoryMessage;

    typedef struct {
        int no_need_yet;
    } ReadyInitMessage;

    typedef struct {
        int no_need_yet;
    } ReadyConnectMessage;

    typedef struct {
        int no_need_yet;
    } AckMessage;

};


#endif //IOT_S2025_TEAM7_ESPTRANSCIEVER_H
