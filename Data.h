//
// Created by papraczy on 05/11/2019.
//

#ifndef SERVER_DATA_H
#define SERVER_DATA_H
#include <string>

using namespace std;

class Data {
public:
    Data();
    ~Data();
    string dataPayload;
    string buffLen;
    int lenOfHex;
    int payloadLength;
    int dataIndex;
    string dataIndexHex;
    string to_string();
};


#endif //SERVER_DATA_H
