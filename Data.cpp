//
// Created by papraczy on 05/11/2019.
//

#include "Data.h"

using namespace std;


Data::Data()
{
    this->dataPayload = "";
    this->payloadLength = 0;
    this->buffLen = "";
    this->lenOfHex = 0;
    this->dataIndex = 0;
    this->dataIndexHex = "";
}


Data::~Data()
{
}

string Data::to_string()
{
    return "index " + std::to_string(this->dataIndex) +
           ", payloadLen: " + std::to_string(this->payloadLength) +
           ", buffLen: " + this->buffLen +
           ", lenOfHex: " + std::to_string(this->lenOfHex) +
           ", dataPayload: " + this->dataPayload;
}