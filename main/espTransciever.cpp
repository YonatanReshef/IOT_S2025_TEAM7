//
// Created on 6/13/2025.
//

# include "espTransciever.h"

void ESPTransceiver::onSendWrapper(const uint8_t* mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void ESPTransceiver::setup(){

    WiFi.mode(WIFI_STA);
    WiFi.STA.begin();

    esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, this->selfMac);
    if (ret == ESP_OK) {
        Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                      baseMac[0], baseMac[1], baseMac[2],
                      baseMac[3], baseMac[4], baseMac[5]);
    } else {
        Serial.println("Failed to read MAC address");
    }
    esp_now_register_send_cb(onSendWrapper);

}

int ESPTransceiver::getId(uint8_t mac[6]) {
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
            return 4+4;
        case GAME_INIT:
            return 4+4*4;
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

    const uint8_t* mac = knownMacs[idReceiver];
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

    switch (msgType) {
        case BALL_CROSSING: {
            if (len >= 1 + sizeof(BallCrossingMessage)) {
                BallCrossingMessage msg;
                memcpy(&msg, payload, sizeof(BallCrossingMessage));
                ballCrossingQueue.push(msg);
            }
            break;
        }
        case GAME_INIT: {
            if (len >= 1 + sizeof(GameInitMessage)) {
                GameInitMessage msg;
                memcpy(&msg, payload, sizeof(GameInitMessage));
                gameInitQueue.push(msg);
            }
            break;
        }
        case VICTORY: {
            if (len >= 1 + sizeof(VictoryMessage)) {
                VictoryMessage msg;
                memcpy(&msg, payload, sizeof(VictoryMessage));
                victoryQueue.push(msg);
            }
            break;
        }
        case READY_INIT: {
            if (len >= 1 + sizeof(ReadyInitMessage)) {
                ReadyInitMessage msg;
                memcpy(&msg, payload, sizeof(ReadyInitMessage));
                readyInitQueue.push(msg);
            }
            break;
        }
        case READY_CONNECT: {
            if (len >= 1 + sizeof(ReadyConnectMessage)) {
                ReadyConnectMessage msg;
                memcpy(&msg, payload, sizeof(ReadyConnectMessage));
                readyConnectQueue.push(msg);
            }
            break;
        }
        case ACK: {
            if (len >= 1 + sizeof(AckMessage)) {
                AckMessage msg;
                memcpy(&msg, payload, sizeof(AckMessage));
                ackQueue.push(msg);
            }
            break;
        }
        default:
            Serial.println("Unknown message type received.");
            break;
    }
}


void ESPTransceiver::receive() {
    esp_now_register_recv_cb(onReceiveWrapper));
}