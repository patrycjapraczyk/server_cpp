//
// Created by papraczy on 05/11/2019.
//

#ifndef SERVER_ERRORLOGGER_H
#define SERVER_ERRORLOGGER_H

#include <string>
#include <chrono>

using namespace std;
#include <iostream>
#include <chrono>

class ErrorLogger {
public:
    ~ErrorLogger();

    ErrorLogger();

    void logError(string message, long packets_received);

    time_t *getTime();

    void printEndMessage();

private:
    int errorCounter;

    float getErrorPercentage(long packets_received);

    void printTime(string message);

    void logToFile(string message);

    string getTimeStr(time_t *currTime);

    float getErrorFrequency();

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
};

#endif //SERVER_ERRORLOGGER_H
