//
// Created on 6/19/2025.
//

#include "Logger.h"

Logger::Logger(const std::string& filename) {
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Logger error: Failed to open file: " << filename << std::endl;
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string& message) {
    if (logFile.is_open()) {
        logFile << message << std::endl;
    }
}

void Logger::log(const char* message) {
    if (logFile.is_open()) {
        logFile << message << std::endl;
    }
}
/* example of usage
 * int main() {
    Logger::getInstance("my_log.txt");  // First and only time you pass a filename
    // From now on, just use Logger::getInstance().log(...)
    }
    ...
    Logger::getInstance().log("This works anywhere");
    ...
 *
 */