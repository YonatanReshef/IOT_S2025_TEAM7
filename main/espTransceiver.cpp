//
// Created on 6/13/2025.
//

# include "espTransceiver.h"
#include <esp_wifi.h>
#include <WiFi.h>
#include <Arduino.h>

const uint8_t ESPTransceiver::knownMacs[ESPTransceiver::macCount][6] = {
        {0xB0, 0xA7, 0x32, 0xD7, 0x84, 0x3C},
        {0xCC, 0xDB, 0xA7, 0x5A, 0x5B, 0x1C},
        {0xF4, 0x65, 0x0B, 0xE9, 0x5E, 0x34}
};

ESPTransceiver::ESPTransceiver() {
    Serial.println("ESPTransceiver Constructor Called");
}

const uint8_t ESPTransceiver::broadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


ESPTransceiver::~ESPTransceiver() {
    Serial.println("ESPTransceiver Destructor Called");
}


void ESPTransceiver::setup(){

    WiFi.mode(WIFI_STA);
    WiFi.STA.begin();

    esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, this->selfMac);
    if (ret == ESP_OK) {
        Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                      selfMac[0], selfMac[1], selfMac[2],
                      selfMac[3], selfMac[4], selfMac[5]);
    } else {
        Serial.println("Failed to read MAC address");
    }

    myId = getId(selfMac);

    esp_now_register_recv_cb(onReceiveWrapper);

}

int ESPTransceiver::getId(const uint8_t *mac) {
    for (int i = 0; i < macCount; i++) {
        if (memcmp(knownMacs[i], mac, 6) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

int ESPTransceiver::getStructSize(MessageType msgType){
    switch (msgType) {
        case BALL_CROSSING:
            return sizeof(BallCrossingMessage);
        case GAME_INIT:
            return sizeof(GameInitMessage);
        case VICTORY:
            return sizeof(VictoryMessage);
        case READY_INIT:
            return sizeof(ReadyInitMessage);
        case READY_CONNECT:
            return sizeof(ReadyConnectMessage);
        case ACK:
            return sizeof(AckMessage);
        case LIVENESS:
            return sizeof(LivenessMessage);
        default:
            return 0;
    }
}


void ESPTransceiver::send(int idReceiver, MessageType msgType, char* msg){
    const uint8_t* mac;

    if (idReceiver == -1) {
        mac = broadcast;
    } else if (idReceiver >= 0 && idReceiver < macCount) {
        mac = knownMacs[idReceiver];
    } else {
        Serial.println("Invalid receiver ID");
        return;
    }

    // Total message = 1 byte for type + msgSize
    int msgSize = getStructSize(msgType);
    size_t totalSize = sizeof(uint8_t) + msgSize;

    uint8_t* buffer = new uint8_t[totalSize];
    buffer[0] = static_cast<uint8_t>(msgType);
    memcpy(buffer + 1, msg, msgSize);

    esp_err_t result = esp_now_send(mac, buffer, totalSize);

    if (result != ESP_OK) {
        Serial.printf("Failed to send to ID %d\n", idReceiver);
    } else {
        Serial.printf("Sent message of type %d to ID %d\n", msgType, idReceiver);
    }

    delete[] buffer;
}

void ESPTransceiver::onReceiveWrapper(const uint8_t* mac, const uint8_t* incomingData, int len) {
    if (len < 1) return;

    MessageType msgType = static_cast<MessageType>(incomingData[0]);
    const uint8_t* payload = incomingData + 1;
    int senderId = getId(mac);

    switch (msgType) {
        case BALL_CROSSING: {
            int size = getStructSize(BALL_CROSSING);
            if (len >= 1 + size) {
                BallCrossingMessage msg;
                memcpy(&msg, payload, size);
                ballCrossingQueue.push(std::make_tuple(msg, senderId));
            }
            break;
        }
        case GAME_INIT: {
            int size = getStructSize(GAME_INIT);
            if (len >= 1 + size) {
                GameInitMessage msg;
                memcpy(&msg, payload, size);
                gameInitQueue.push(std::make_tuple(msg, senderId));
            }
            break;
        }
        case VICTORY: {
            int size = getStructSize(VICTORY);
            if (len >= 1 + size) {
                VictoryMessage msg;
                memcpy(&msg, payload, size);
                victoryQueue.push(std::make_tuple(msg, senderId));
            }
            break;
        }
        case READY_INIT: {
            int size = getStructSize(READY_INIT);
            if (len >= 1 + size) {
                ReadyInitMessage msg;
                memcpy(&msg, payload, size);
                readyInitQueue.push(std::make_tuple(msg, senderId));
            }
            break;
        }
        case READY_CONNECT: {
            int size = getStructSize(READY_CONNECT);
            if (len >= 1 + size) {
                ReadyConnectMessage msg;
                memcpy(&msg, payload, size);
                readyConnectQueue.push(std::make_tuple(msg, senderId));
            }
            break;
        }
        case ACK: {
            int size = getStructSize(ACK);
            if (len >= 1 + size) {
                AckMessage msg;
                memcpy(&msg, payload, size);
                ackQueue.push(std::make_tuple(msg, senderId));
            }
            break;
        }
        case LIVENESS: {
            int size = getStructSize(LIVENESS);
            if (len >= 1 + size) {
                LivenessMessage msg;
                memcpy(&msg, payload, size);
                livenessQueue.push(std::make_tuple(msg, senderId));
            }
            break;
        }
        default:
            Serial.println("Unknown message type received.");
            break;
    }
}


int ESPTransceiver::getMyId(){
    return myId;
}
