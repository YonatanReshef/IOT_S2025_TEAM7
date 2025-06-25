//
// Created on 6/19/2025.
//

#include "Logger.h"

void Logger::setup(const std::string& filename) {
    getInstance().openFile(filename);
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::openFile(const std::string& filename) {
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Logger error: Cannot open file: " << filename << std::endl;
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

bool Logger::isOpen() const {
    return logFile.is_open();
}