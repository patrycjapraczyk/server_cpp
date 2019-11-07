//
// Created by papraczy on 05/11/2019.
//

#include "ErrorLogger.h"
#include <fstream>
#include <iostream>

using namespace std;

ErrorLogger::ErrorLogger()
{
}


ErrorLogger::~ErrorLogger()
{
}

void ErrorLogger::logError(string message)
{
    ofstream ofile;
    ofile.open("errors.txt", ios::ate);
    if (ofile.is_open())
    {
        ofile << errorCounter << ". " << message << " " << this->getTime() << endl;
        ofile.close();
    }
    else
    {
        cout << "Couldn't open the file" << endl;
    }
}

time_t ErrorLogger::getTime()
{
    return time(0);
}

