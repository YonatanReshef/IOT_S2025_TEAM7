//
// Created on 6/13/2025.
//

#include "ESPTransceiver.h"
#include <esp_wifi.h>
#include <WiFi.h>
#include <Arduino.h>

const uint8_t ESPTransceiver::knownMacs[ESPTransceiver::macCount][6] = {
        {0xB0, 0xA7, 0x32, 0xD7, 0x84, 0x3C},
        {0xCC, 0xDB, 0xA7, 0x5A, 0x5B, 0x1C},
        {0xF4, 0x65, 0x0B, 0xE9, 0x5E, 0x34},
        {0xb0, 0xa7, 0x32, 0xde, 0x9e, 0x98}
};

const uint8_t ESPTransceiver::broadcast[6] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

// --- Singleton Accessor ---
ESPTransceiver& ESPTransceiver::getInstance() {
    static ESPTransceiver instance;
    return instance;
}

// --- Constructor/Destructor ---
ESPTransceiver::ESPTransceiver() {
    Serial.println("ESPTransceiver Constructor Called");
}

ESPTransceiver::~ESPTransceiver() {
    Serial.println("ESPTransceiver Destructor Called");
}

// --- Setup Method ---
void ESPTransceiver::setup() {
    WiFi.mode(WIFI_STA);
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);  // All devices must match
    esp_wifi_set_promiscuous(false);
    
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, selfMac);
    if (ret == ESP_OK) {
        Serial.printf("Self MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
                      selfMac[0], selfMac[1], selfMac[2],
                      selfMac[3], selfMac[4], selfMac[5]);
    } else {
        Serial.println("Failed to read MAC address");
    }

    myId = getId(selfMac);

    esp_now_register_recv_cb([](const uint8_t* mac, const uint8_t* data, int len) {
        ESPTransceiver::getInstance().onReceiveWrapper(mac, data, len);
    });
    tick = 0;
}


int ESPTransceiver::getParticipatingMask(){
    int my_id = getMyId();
    int participating_mask = 0;

    for(int i = 0; i < macCount; i++){
        if(isAlive(i) && (i != my_id)){
            participating_mask |= (1 << i);
        }
    }

    return participating_mask;
}

void ESPTransceiver::update(int dt){

    for(int i = 0; i < macCount; ++i){
        timeoutVals[i] -= dt;
        if(timeoutVals[i] < 0){
            timeoutVals[i] = 0;
        }
    }
    
    int id;
    LivenessMessage msg;
    while (!livenessQueue.empty()) {
        auto [queuedMsg, queuedId] = livenessQueue.front();
        livenessQueue.pop();
        msg = queuedMsg;
        id = queuedId;
        timeoutVals[id] = timeout;
    }

    int my_id = getMyId();
    timeoutVals[my_id] = timeout;

    tick += dt;
    if (tick > liveness_send_delay) {
        tick = 0;
        LivenessMessage sendMsg = {1};  // requires ctor
        send(-1, LIVENESS, reinterpret_cast<char*>(&sendMsg));
    }
}

bool ESPTransceiver::isAlive(int id){
    return 0 != timeoutVals[id];
}

// --- Message Sending ---
void ESPTransceiver::send(int idReceiver, MessageType msgType, char* msg) {
    const uint8_t* mac;

    if (idReceiver == -1) {
        mac = broadcast;
    } else if (idReceiver >= 0 && idReceiver < macCount) {
        mac = knownMacs[idReceiver];
    } else {
        Serial.println("Invalid receiver ID");
        return;
    }

    int msgSize = getStructSize(msgType);
    size_t totalSize = sizeof(uint8_t) + msgSize;

    uint8_t* buffer = new uint8_t[totalSize];
    buffer[0] = static_cast<uint8_t>(msgType);
    memcpy(buffer + 1, msg, msgSize);

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, mac, 6);
    peerInfo.channel = 0;       // 0 means "current channel"
    peerInfo.encrypt = false;   // true if using encryption

    if (!esp_now_is_peer_exist(mac)) {
        if (esp_now_add_peer(&peerInfo) != ESP_OK) {
            Serial.println("Failed to add peer");
            return;
        }
    }

    esp_err_t result = esp_now_send(mac, buffer, totalSize);

    if (result != ESP_OK) {
        Serial.printf("Failed to send to ID %d: %s (code: 0x%x)\n", idReceiver, esp_err_to_name(result), result);
    } else {
        Serial.printf("Sent message of type %d to ID %d\n", msgType, idReceiver);
    }

    delete[] buffer;
}

// --- Message Receiving ---
void ESPTransceiver::onReceiveWrapper(const uint8_t* mac, const uint8_t* incomingData, int len) {
    if (len < 1) return;

    MessageType msgType = static_cast<MessageType>(incomingData[0]);
    const uint8_t* payload = incomingData + 1;
    int senderId = getId(mac);
    Serial.printf("Recved message of type %d from ID %d\n", msgType, senderId);
    switch (msgType) {
        case BALL_CROSSING: {
            int size = getStructSize(BALL_CROSSING);
            if (len >= 1 + size) {
                BallCrossingMessage msg;
                memcpy(&msg, payload, size);
                ballCrossingQueue.push({msg, senderId});
            }
            break;
        }
        case GAME_INIT: {
            int size = getStructSize(GAME_INIT);
            if (len >= 1 + size) {
                GameInitMessage msg;
                memcpy(&msg, payload, size);
                gameInitQueue.push({msg, senderId});
            }
            break;
        }
        case VICTORY: {
            int size = getStructSize(VICTORY);
            if (len >= 1 + size) {
                VictoryMessage msg;
                memcpy(&msg, payload, size);
                victoryQueue.push({msg, senderId});
            }
            break;
        }
        case READY_INIT: {
            int size = getStructSize(READY_INIT);
            if (len >= 1 + size) {
                ReadyInitMessage msg;
                memcpy(&msg, payload, size);
                readyInitQueue.push({msg, senderId});
            }
            break;
        }
        case READY_CONNECT: {
            int size = getStructSize(READY_CONNECT);
            if (len >= 1 + size) {
                ReadyConnectMessage msg;
                memcpy(&msg, payload, size);
                readyConnectQueue.push({msg, senderId});
            }
            break;
        }
        case ACK: {
            int size = getStructSize(ACK);
            if (len >= 1 + size) {
                AckMessage msg;
                memcpy(&msg, payload, size);
                ackQueue.push({msg, senderId});
            }
            break;
        }
        case LIVENESS: {
            int size = getStructSize(LIVENESS);
            if (len >= 1 + size) {
                LivenessMessage msg;
                memcpy(&msg, payload, size);
                livenessQueue.push({msg, senderId});
            }
            break;
        }
        case GAME_REQUEST: {
            int size = getStructSize(GAME_REQUEST);
            if (len >= 1 + size) {
                GameRequestMessage msg;
                memcpy(&msg, payload, size);
                gameRequestQueue.push({msg, senderId});
            }
            break;
        }
        default:
            Serial.println("Unknown message type received.");
            break;
    }
}

// --- Helper Methods ---
int ESPTransceiver::getId(const uint8_t* mac) {
    for (int i = 0; i < macCount; i++) {
        if (memcmp(knownMacs[i], mac, 6) == 0) {
            return i;
        }
    }
    return -1;
}

int ESPTransceiver::getStructSize(MessageType msgType) {
    switch (msgType) {
        case BALL_CROSSING: return sizeof(BallCrossingMessage);
        case GAME_INIT: return sizeof(GameInitMessage);
        case VICTORY: return sizeof(VictoryMessage);
        case READY_INIT: return sizeof(ReadyInitMessage);
        case READY_CONNECT: return sizeof(ReadyConnectMessage);
        case ACK: return sizeof(AckMessage);
        case LIVENESS: return sizeof(LivenessMessage);
        case GAME_REQUEST: return sizeof(GameRequestMessage);
        default: return 0;
    }
}

int ESPTransceiver::getMyId() {
    return myId;
}
