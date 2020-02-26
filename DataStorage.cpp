//
// Created by papraczy on 05/11/2019.
//

#include "DataStorage.h"
using namespace std;


DataStorage::DataStorage()
{
    this->currData = new Data();
    this->data_counter = 0;
}

DataStorage::~DataStorage()
{
}

void DataStorage::saveCurrentData()
{
    if(this->dataArr.size() > MAX_SIZE)
        this->dataArr.erase(this->dataArr.begin(), this->dataArr.begin() + 1);

    (this->currData)->payloadLength = (this->currData)->dataPayload.length();
    this->dataArr.push_back(*this->currData);
    cout << this->currData->to_string() << endl;

    this->data_counter++;
    //clear current data
    this->currData = new Data();
}

long DataStorage::getDataCounter() const {
    return data_counter;
}
