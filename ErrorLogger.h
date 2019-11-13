//
// Created by papraczy on 05/11/2019.
//

#ifndef SERVER_ERRORLOGGER_H
#define SERVER_ERRORLOGGER_H

#include <string>
#include <chrono>

using namespace std;

class ErrorLogger
{
public:
    ErrorLogger();
    ~ErrorLogger();
    void logError(string message);
    time_t* getTime();

private:
    int errorCounter;
};


#endif //SERVER_ERRORLOGGER_H
