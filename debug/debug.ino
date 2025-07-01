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
        Logger::getInstance().log(Logger::GYRO, "Started GYRO."); // should be printed
        Logger::getInstance().logf(Logger::GYRO, "dfajkf %d", 5); // should be printed
        Logger::getInstance().log(Logger::OPTICTRANSCEIVER, "Started OPTICTRANSCEIVER."); // should not be printed
    }

}
