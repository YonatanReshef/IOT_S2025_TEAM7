#include "logger.h"

int COUNTER = 0;

void setup() {
    Serial.begin(9600);
    sleep(1);

    sleep(1);
    Serial.println("Setup Success");
}

void loop() {

    if(COUNTER == 0){
        int set[] = {1,0,0,0,0,0,0};
        Logger& instance = Logger::getInstance();
        Logger::setup(set);
        Logger::getInstance().log("Started GYRO.", Logger::GYRO); // should be printed
        Logger::getInstance().log("Started OPTICTRANSCEIVER.", Logger::OPTICTRANSCEIVER); // should not be printed
    }

}
