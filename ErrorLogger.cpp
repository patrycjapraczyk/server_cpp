//
// Created by papraczy on 05/11/2019.
//

#include "ErrorLogger.h"
#include <fstream>
#include <iostream>

using namespace std;

ErrorLogger::ErrorLogger()
{
    ofstream ofile;
    ofile.open("errors.txt");
    this->errorCounter = 1;
}


ErrorLogger::~ErrorLogger()
{
}

void ErrorLogger::logError(string message)
{
    ofstream ofile;
    ofile.open("errors.txt", std::ios_base::app);
    if (ofile.is_open())
    {
        ofile << errorCounter << ". " << message << " time: " << ctime(this->getTime());
        ofile.close();
    }
    else
    {
        cout << "Couldn't open the file" << endl;
    }
    errorCounter++;
}

time_t* ErrorLogger::getTime()
{
    auto time = chrono::system_clock::now();
    time_t normal_format  = chrono::system_clock::to_time_t(time);
    return &normal_format;
}

