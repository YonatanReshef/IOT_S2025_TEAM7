//
// Created on 6/19/2025.
//

#ifndef IOT_S2025_TEAM7_LOGGER_H
#define IOT_S2025_TEAM7_LOGGER_H

#include <string>
#include <fstream>

class Logger {
public:
    static Logger& getInstance(const std::string& filename = "log.txt");

    void log(const std::string& message);
    void log(const char* message);
    bool isOpen() const;

private:
    Logger(const std::string& filename);
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::ofstream logFile;
};

#endif //IOT_S2025_TEAM7_LOGGER_H
