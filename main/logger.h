//
// Created on 6/19/2025.
//

#ifndef IOT_S2025_TEAM7_LOGGER_H
#define IOT_S2025_TEAM7_LOGGER_H

#include <string>
#include <iostream>
#include <cstdarg>  // for va_list


class Logger {
public:
    enum ComponentsToDebug {
        GYRO = 0,
        LED_MATRIX = 1,
        BUTTON = 2,
        ESPTRANSCEIVER = 3,
        OPTICTRANSCEIVER = 4,
        PREGAME = 5,
        GAME = 6
    };

    static void setup(int flags[]);
    static Logger& getInstance();

    void log(ComponentsToDebug component, const std::string& message);
    void log(ComponentsToDebug component, const char* message);

    // New printf-style log function (no automatic newline)
    void logf(ComponentsToDebug component, const char* format, ...);

private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static const int num_flags = 7; // Number of components to debug
    // appropriate to ComponentsToDebug
    // 0 - disabled, 1 - enabled
    int componentFlags[num_flags] = {0};

};

/*
 *  example of usage
    int main(){
        int set[] = {1,0,0,0,0,0,0};
        Logger& instance = Logger::getInstance();
        Logger::setup(set);
        Logger::getInstance().log("Started GYRO.", Logger::GYRO); // should be printed
        Logger::getInstance().log("Started OPTICTRANSCEIVER.", Logger::OPTICTRANSCEIVER); // should not be printed
    
        return 0;
    }
 */

#endif //IOT_S2025_TEAM7_LOGGER_H
