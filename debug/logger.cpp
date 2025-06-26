//
// Created on 6/19/2025.
//

#include "Logger.h"
#include <Arduino.h>

void Logger::setup(int flags[]) {
    Logger& instance = getInstance();
    for(int i=0; i<instance.num_flags;i++){
        instance.componentFlags[i] = flags[i];
    }
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::log(const std::string& message, ComponentsToDebug component) {
    if (getInstance().componentFlags[component] == 1) {
        Serial.println(message.c_str());
    }
}

void Logger::log(const char* message, ComponentsToDebug component) {
    if (getInstance().componentFlags[component] == 1) {
        Serial.println(message);
    }
}
