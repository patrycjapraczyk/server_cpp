//
// Created by papraczy on 05/11/2019.
//

#include "ErrorLogger.h"
#include <fstream>
#include <iostream>

using namespace std;

ErrorLogger::ErrorLogger() {
    //clear the file
    ofstream ofile;
    ofile.open("errors.txt");
    this->errorCounter = 0;
    this->printTime("Started at: ");
}


ErrorLogger::~ErrorLogger()
{
    this->printTime("Ended at: ");
}


void ErrorLogger::logError(string message, long packets_received)
{
    string msg = "";
    msg += "\n" + to_string(errorCounter + 1) + ". " + message + "\n";
    msg += "time :" + this->getTimeStr(this->getTime()) + " error percentage: " + to_string(this->getErrorPercentage(packets_received)) + "*10^4 %\n";
    float errorPercent = this->getErrorPercentage(packets_received);
    msg += "Error frequency: " + to_string(getErrorFrequency()) + "mHz\n";
    this->logToFile(msg);
    errorCounter++;
}


time_t* ErrorLogger::getTime()
{
    auto time = chrono::system_clock::now();
    time_t normal_format  = chrono::system_clock::to_time_t(time);
    return &normal_format;
}

float ErrorLogger::getErrorPercentage(long packets_received) {
    const int MULTIPLY_FACTOR = 1000000;
    float percent = (MULTIPLY_FACTOR * this->errorCounter)/packets_received;
    return percent;
}

void ErrorLogger::printTime(string message) {
    time_t* currTime = this->getTime();
    this->logToFile(message + this->getTimeStr(currTime));
    errorCounter++;
}

void ErrorLogger::logToFile(string message) {
    ofstream ofile;
    ofile.open("errors.txt", std::ios_base::app);
    if (ofile.is_open())
    {
        ofile <<  message;
        ofile.close();
    }
    else
    {
        cout << "Couldn't open the file" << endl;
    }
}

string ErrorLogger::getTimeStr(time_t *currTime) {
    time (currTime);
    struct tm * timeinfo;
    char buffer[80];
    timeinfo = localtime(currTime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    string str(buffer);
    return buffer;
}

void ErrorLogger::printEndMessage() {
    this->logToFile("Ended at: " + this->getTimeStr(this->getTime()) + "\n");
}

float ErrorLogger::getErrorFrequency() {
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(end-start).count();
    return errorCounter/elapsed_time_ms;
}


