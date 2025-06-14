//
// Created on 6/13/2025.
//

#ifndef IOT_S2025_TEAM7_ESPTRANSCIEVER_H
#define IOT_S2025_TEAM7_ESPTRANSCIEVER_H

#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include <queue>

class ESPTransceiver
{
    public:

        ESPTransceiver();
        ~ESPTransceiver();

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

        void setup();

        void send(int idReceiver, MessageType msgType, char* msg);
        void receive();

        int getId(uint8_t mac[6]);
        int getMyId();

        std::queue<BallCrossingMessage> ballCrossingQueue;
        std::queue<GameInitMessage> gameInitQueue;
        std::queue<VictoryMessage> victoryQueue;
        std::queue<ReadyInitMessage> readyInitQueue;
        std::queue<ReadyConnectMessage> readyConnectQueue;
        std::queue<AckMessage> ackQueue;

        void onSendWrapper(const uint8_t* mac_addr, esp_now_send_status_t status);
        void onReceiveWrapper(const uint8_t* mac, const uint8_t* incomingData, int len);

    private:

        // add all the macs
        static constexpr int macCount = 3;
        static const uint8_t knownMacs[macCount][6];

        static const uint8_t broadcast[6];
        const int broadcast_id = -1;

        uint8_t selfMac[6];
        int myId;

        int getStructSize(MessageType msgType);

};


#endif //IOT_S2025_TEAM7_ESPTRANSCIEVER_H
