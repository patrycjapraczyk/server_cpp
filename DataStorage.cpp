//
// Created by papraczy on 05/11/2019.
//

#include "DataStorage.h"
using namespace std;


DataStorage::DataStorage()
{
    this->currData = Data();
}

DataStorage::~DataStorage()
{
}

void DataStorage::saveCurrentData()
{
    (this->currData).payloadLength = (this->currData).dataPayload.length();
    this->dataArr->push_back(this->currData);
    cout << this->currData.to_string() << endl;
    this->currData = Data();
}
