//
// Created by papraczy on 05/11/2019.
//

#ifndef SERVER_DATAANALYSER_H
#define SERVER_DATAANALYSER_H

#include <string>
#include "ErrorLogger.h"
#include "DataStorage.h"
#include "SafeQueue.h"

#define AVERAGE_DATA_LENGTH 3000
#define PACKET_LEN_START_INDEX 2
#define PACKET_LEN_LENGTH 4
#define DATA_COUNTER_START_INDEX 6
#define DATA_COUNTER_LENGTH 4
#define DATA_BLOCK_LEN_HEX 4
#define DATA_PARAMS_LEN 14
#define DATA_PAYLOAD_START_INDEX 14
#define END_CODE "81"
#define START_CODE "aa"
#define START_END_CODE_LENGTH 2
#define DATA_INDEX_LENGTH 8
#define HEX_BASE 16
#define MAX_DATA_INDEX (HEX_BASE ^ (DATA_INDEX_LENGTH)-1)

using namespace std;

class DataAnalyser {

private:
    bool stopped;
    string currDataStr;
    ErrorLogger *logger;
    DataStorage *dataStorage;
    SafeQueue *q;
    bool findEndIndex();
    template <class T>
    vector<T> removeEveryOther(vector<T> old_arr);

public:
    DataAnalyser(SafeQueue *data_queue);
    ~DataAnalyser();
    void analyseDataPayload();
    bool checkDataIndex();
    void operator() (void);
};



#endif //SERVER_DATAANALYSER_H
