//
// Created on 6/19/2025.
//

#include "Logger.h"
#include <Arduino.h>
#include <cstdarg>  // for va_list, va_start, va_end


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

void Logger::log(ComponentsToDebug component, const std::string& message) {
    if (getInstance().componentFlags[component] == 1) {
        Serial.println(message.c_str());
    }
}

void Logger::log(ComponentsToDebug component, const char* message) {
    if (getInstance().componentFlags[component] == 1) {
        Serial.println(message);
    }
}

void Logger::logf(ComponentsToDebug component, const char* format, ...) {
    if (getInstance().componentFlags[component] != 1) {
        return;
    }

    char buffer[256];  // Adjust size as needed
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);  // Format into buffer
    va_end(args);

    Serial.print(buffer);  // Works as printf-style output
}