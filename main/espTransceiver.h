#ifndef IOT_S2025_TEAM7_ESPTRANSCEIVER_H
#define IOT_S2025_TEAM7_ESPTRANSCEIVER_H

#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include <queue>
#include <tuple>
#include <stdbool.h>
#include "boardLayout.h"

class ESPTransceiver
{
public:
    enum MessageType {
        BALL_CROSSING,
        GAME_INIT,
        VICTORY,
        READY_INIT,
        READY_CONNECT,
        ACK,
        LIVENESS,
        GAME_REQUEST
    };

    typedef struct {
        BoardLayout::SIDE side;
        int idx;
    } BallCrossingMessage;

    typedef struct {
        int map_id;
        int participating_mask;
    } GameInitMessage;

    typedef struct {
        int win_stop;
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

    typedef struct {
        int status;
    } LivenessMessage;
    
    typedef struct {
        int status;
    } GameRequestMessage;

    static ESPTransceiver& getInstance(); // Accessor for singleton instance

    void setup();
    void update(int dt);

    void send(int idReceiver, MessageType msgType, char* msg);
    int getMyId();
    int getId(const uint8_t* mac);
    int getStructSize(MessageType msgType);
    bool isAlive(int id);
    void onReceiveWrapper(const uint8_t* mac, const uint8_t* incomingData, int len);
    int getParticipatingMask();
    void reset();

    std::queue<std::tuple<BallCrossingMessage, int>> ballCrossingQueue;
    std::queue<std::tuple<GameInitMessage, int>> gameInitQueue;
    std::queue<std::tuple<VictoryMessage, int>> victoryQueue;
    std::queue<std::tuple<ReadyInitMessage, int>> readyInitQueue;
    std::queue<std::tuple<ReadyConnectMessage, int>> readyConnectQueue;
    std::queue<std::tuple<AckMessage, int>> ackQueue;
    std::queue<std::tuple<LivenessMessage, int>> livenessQueue;
    std::queue<std::tuple<GameRequestMessage, int>> gameRequestQueue;

private:
    ESPTransceiver();                             // Private constructor
    ~ESPTransceiver();                            // Destructor

    ESPTransceiver(const ESPTransceiver&) = delete;             // Disable copy constructor
    ESPTransceiver& operator=(const ESPTransceiver&) = delete;  // Disable assignment

    static constexpr int macCount = 4;
    static const uint8_t knownMacs[macCount][6];
    static const uint8_t broadcast[6];
    const int broadcast_id = -1;
    static constexpr int liveness_send_delay = 2000;
    static constexpr int timeout = liveness_send_delay * 2;
    
    uint8_t selfMac[6];
    int myId;
    int tick;
    int timeoutVals[macCount] = {timeout};
};

#endif // IOT_S2025_TEAM7_ESPTRANSCEIVER_H
