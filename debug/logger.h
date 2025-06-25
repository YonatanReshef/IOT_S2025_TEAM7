//
// Created on 6/19/2025.
//

#ifndef IOT_S2025_TEAM7_LOGGER_H
#define IOT_S2025_TEAM7_LOGGER_H

#include <string>
#include <fstream>

class Logger {
public:
    static void setup(const std::string& filename);  // Call once at the beginning
    static Logger& getInstance();

    void log(const std::string& message);
    void log(const char* message);
    bool isOpen() const;

private:
    Logger() = default;
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void openFile(const std::string& filename);
    std::ofstream logFile;
};

/*
 *  example of usage
    int main() {
        Logger::setup("logfile.txt");
        Logger::getInstance().log("Started program.");

        return 0;
    }
 */

#endif //IOT_S2025_TEAM7_LOGGER_H
