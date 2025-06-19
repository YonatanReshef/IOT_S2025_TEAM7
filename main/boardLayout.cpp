
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


BoardLayout::BoardLayout()
    : transceivers{
        OpticTransceiver(PIN_LED_OUT_L, PIN_RECVR_L),
        OpticTransceiver(PIN_LED_OUT_R, PIN_RECVR_R),
        OpticTransceiver(PIN_LED_OUT_U, PIN_RECVR_U),
        OpticTransceiver(PIN_LED_OUT_D, PIN_RECVR_D)
    }, 
    connectorsStates{-1}
{}

void BoardLayout::setup(int id)
{
    for (size_t i = 0; i < NUM_SIDES; i++){
        transceivers[i].setup(setData(id, i));
        connectorsStates[i] = -1;
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

int BoardLayout::getState(SIDE my_side, SIDE &other_side){
    int id = -1;
    int other_side_int;
    if(connectorsStates[(int)my_side] != -1){
        getData(connectorsStates[(int)my_side], id, other_side_int);
        other_side = static_cast<SIDE>(other_side_int);
    }
    return id;
}

void BoardLayout::setMsgId(int id){
    for (size_t i = 0; i < NUM_SIDES; i++){
        transceivers[i].setMessage(setData(id, i));
    }
}
