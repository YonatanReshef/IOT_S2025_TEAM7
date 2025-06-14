
#include "boardLayout.h"
#include "config.h"
#include <Arduino.h>


static int setData(int my_id, int side) {
    return (my_id << 2) | (side & 0x03);
}

static void getData(int msg, int &id, int &side) {
    side = msg & 0x03;
    id = msg >> 2;
}


static void printSide(int side){
    switch (side)
    {
    case BoardLayout::SIDE::LEFT:
        Serial.print("LEFT");
        break;
    case BoardLayout::SIDE::RIGHT:
        Serial.print("RIGHT");
        break;
    case BoardLayout::SIDE::UP:
        Serial.print("UP");
        break;
    case BoardLayout::SIDE::DOWN:
        Serial.print("DOWN");
        break;
    }
}


static void printState(int my_side, int prev, int curr) {

    int id, side;

    Serial.print("[Connector ");
    printSide(my_side);
    Serial.print("] - ");
    if(prev == -1){
        Serial.print("Disconnected");
    }
    else{
        getData(prev, id, side);
        Serial.print("(");
        Serial.print(id);
        Serial.print(", ");
        printSide(side);
        Serial.print(")");
    }
    Serial.print(" --> ");
    if(curr == -1){
        Serial.print("Disconnected");
    }
    else{
        getData(curr, id, side);
        Serial.print("(");
        Serial.print(id);
        Serial.print(", ");
        printSide(side);
        Serial.print(")");
    }
}


BoardLayout::BoardLayout(int my_id)
    : transceivers{
        OpticTransceiver(PIN_LED_OUT_L, PIN_RECVR_L, setData(my_id, SIDE::LEFT)),
        OpticTransceiver(PIN_LED_OUT_R, PIN_RECVR_R, setData(my_id, SIDE::RIGHT)),
        OpticTransceiver(PIN_LED_OUT_U, PIN_RECVR_U, setData(my_id, SIDE::UP)),
        OpticTransceiver(PIN_LED_OUT_D, PIN_RECVR_D, setData(my_id, SIDE::DOWN))
    }, 
    connectorsStates{-1}
{}

void BoardLayout::setup()
{
    for (size_t i = 0; i < NUM_SIDES; i++){
        transceivers[i].setup();
    }
}

void BoardLayout::update(int dt)
{
    int msg, id, side;
    for (size_t i = 0; i < NUM_SIDES; i++){
        msg = transceivers[i].update(dt);
        if(msg != connectorsStates[i]){ // State Change!
            printState(i, connectorsStates[i], msg);
            connectorsStates[i] = msg;
        }
    }
}

int BoardLayout::getState(int my_side, int &other_side){
    int id = -1;
    if(connectorsStates[i] != -1){
        getData(connectorsStates[i], id, other_side);
    }
    return id;
}
