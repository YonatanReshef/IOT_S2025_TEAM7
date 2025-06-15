#ifndef IOT_S2025_TEAM7_ESPTRANSCEIVER_H
#define IOT_S2025_TEAM7_ESPTRANSCEIVER_H

#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include <queue>
#include <tuple>

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
        LIVENESS
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

    typedef struct {
        int status;
    } LivenessMessage;

    static ESPTransceiver& getInstance(); // Accessor for singleton instance

    void setup();
    void send(int idReceiver, MessageType msgType, char* msg);
    int getMyId();
    int getId(const uint8_t* mac);
    int getStructSize(MessageType msgType);
    void onReceiveWrapper(const uint8_t* mac, const uint8_t* incomingData, int len);

    std::queue<std::tuple<BallCrossingMessage, int>> ballCrossingQueue;
    std::queue<std::tuple<GameInitMessage, int>> gameInitQueue;
    std::queue<std::tuple<VictoryMessage, int>> victoryQueue;
    std::queue<std::tuple<ReadyInitMessage, int>> readyInitQueue;
    std::queue<std::tuple<ReadyConnectMessage, int>> readyConnectQueue;
    std::queue<std::tuple<AckMessage, int>> ackQueue;
    std::queue<std::tuple<LivenessMessage, int>> livenessQueue;

private:
    ESPTransceiver();                             // Private constructor
    ~ESPTransceiver();                            // Destructor

    ESPTransceiver(const ESPTransceiver&) = delete;             // Disable copy constructor
    ESPTransceiver& operator=(const ESPTransceiver&) = delete;  // Disable assignment

    static constexpr int macCount = 3;
    static const uint8_t knownMacs[macCount][6];
    static const uint8_t broadcast[6];
    const int broadcast_id = -1;

    uint8_t selfMac[6];
    int myId;
};

#endif // IOT_S2025_TEAM7_ESPTRANSCEIVER_H
