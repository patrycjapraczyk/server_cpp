//
// Created by papraczy on 05/11/2019.
//

#include "DataStorage.h"
using namespace std;


DataStorage::DataStorage()
{
    this->currData = new Data();
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
    this->currData = new Data();
    int curr_size = this->dataArr.size();
    //this->dataArr.resize(curr_size + 1);
}
