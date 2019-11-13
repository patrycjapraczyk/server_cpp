#include "DataAnalyser.h"
#include "Calculator.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

DataAnalyser::DataAnalyser(SafeQueue *data_queue) {
    this->dataStorage = new DataStorage();
    this->q = data_queue;
    this->currDataStr = "";
    this->stopped = false;
    this->logger = new ErrorLogger();
}


DataAnalyser::~DataAnalyser() {
    //delete &(this->dataStorage);
    // delete &(this->logger);
}

/*
	checks if data packets are in agreement with data headers
	and checks its internal integrity.
	Elements in data header:
	-- PACKET_LEN - data packet length- header + payload
	-- DATA_CNT - data counter
*/
void DataAnalyser::operator()(void) {
    //look for start code initially
    int startIndex = this->currDataStr.find(START_CODE);
    //take another data packet off the queue if it was not found
    //and continue the search for the start code
    while (startIndex < 0) {
        this->currDataStr = (this->q)->pop();
        startIndex = this->currDataStr.find(START_CODE);
    }
    // ignore all data preceding the start code
    this->currDataStr = (this->currDataStr).substr(startIndex);
    while (!this->stopped) {
        /* If there is data to be analysed from the previous data str,
        do not take the new data of the queue */
        if (this->currDataStr.length() < AVERAGE_DATA_LENGTH) {
            this->currDataStr += (this->q)->pop();
        }

        // try to find end code if there is data that has not been finished
        Data *currDataItem = this->dataStorage->currData;

        if (!currDataItem->dataPayload.empty()) {
            this->findEndIndex();
            continue;
        }

        // NEW DATA PIECE
        string expectedStartEndCode = this->currDataStr.substr(0, START_END_CODE_LENGTH);
        // if start index was not found
        if (expectedStartEndCode != START_CODE) {
            this->logger->logError("MISSING START CODE data_str: " + this->currDataStr);
        }

        if (this->currDataStr.length() < DATA_PAYLOAD_START_INDEX) {
            continue;
        }

        // extract buffer length
        string s = this->currDataStr.substr(PACKET_LEN_START_INDEX, PACKET_LEN_LENGTH);
        currDataItem->buffLen = s;
        int intLen = Calculator::getInt(currDataItem->buffLen);

        //number of hex digits
        currDataItem->lenOfHex = intLen * 2;

        //extract data counter
        string dataIndex = this->currDataStr.substr(DATA_COUNTER_START_INDEX, DATA_COUNTER_LENGTH);

        currDataItem->dataIndex = Calculator::getInt(dataIndex);
        currDataItem->dataIndexHex = dataIndex;

        // remove all all data that has been analysed and saved already
        this->currDataStr = this->currDataStr.substr(DATA_PAYLOAD_START_INDEX);

        this->findEndIndex();

    }
}

bool DataAnalyser::findEndIndex() {
    Data *currDataItem = this->dataStorage->currData;
    int dataLength = this->currDataStr.length();
    int payloadLength = currDataItem->dataPayload.length();

    //expected end code index
    int endCodeIndex = currDataItem->lenOfHex - DATA_PAYLOAD_START_INDEX - START_END_CODE_LENGTH - payloadLength;

    // if data_str is shorter than expected end code
    if (dataLength < endCodeIndex) {
        //add current data string to data payload
        currDataItem->dataPayload += currDataStr.substr(0, dataLength);

        //remove the analysed data from curr_data_str
        this->currDataStr = this->currDataStr.substr(dataLength);
        return false;
    } else {
        string expectedEndCode = "";
        // check if end code is placed in agreement with buffer length
        if (endCodeIndex + START_END_CODE_LENGTH < this->currDataStr.length()) {
            expectedEndCode = this->currDataStr.substr(endCodeIndex, START_END_CODE_LENGTH);
        }
        if (expectedEndCode == END_CODE) {

            currDataItem->dataPayload += this->currDataStr.substr(0, endCodeIndex);

            // remove the analysed data from curr_data_str
            this->currDataStr = this->currDataStr.substr(endCodeIndex + START_END_CODE_LENGTH);

            this->analyseDataPayload();
            this->checkDataIndex();
            this->dataStorage->saveCurrentData();
        } else {
            //can't find the end code within data
            this->logger->logError("MISSING END_CODE, expected_end_code: " + expectedEndCode + " end_code index: " +
                                   to_string(endCodeIndex) + " data_str: " + this->currDataStr);
        }
    }
    return true;
}

void DataAnalyser::analyseDataPayload() {
    Data *currDataItem = this->dataStorage->currData;
    string dataPayload = currDataItem->dataPayload;
    std::vector<string> indexList;

    //split the data string into chunks of length 4
    for (int i = 0; i < dataPayload.length() - DATA_BLOCK_LEN_HEX; i = i + DATA_BLOCK_LEN_HEX) {
        string dataChunk = dataPayload.substr(i, DATA_BLOCK_LEN_HEX);
        indexList.push_back(dataChunk);
    }


    indexList = this->removeEveryOther(indexList);

    vector<int> indexListInts;
    for (int i = 0; i < indexList.size(); i++) {
        string curr = indexList.at(i);
        indexListInts.push_back(Calculator::getInt(curr));
    }

    // generate a sequence of numbers according to data buffer length
    // (number of data chunks)
    int buffLen = Calculator::getInt(currDataItem->buffLen);
    static int BYTES_PER_DATA_CHUNK = 2;
    int dataPayloadLen = buffLen - DATA_PARAMS_LEN / 2;
    int numSeqLen = dataPayloadLen / BYTES_PER_DATA_CHUNK;

    // divide by 2 because of taking into account every other num
    if (numSeqLen % 2 == 0)
        numSeqLen /= 2;
    else
        numSeqLen = numSeqLen / 2 + 1;

    vector<int> numSeq;
    Calculator::getNumberSequence(numSeqLen, &numSeq);

    if (!Calculator::checkVectorEquality(&indexListInts, &numSeq)) {
        this->logger->logError("Indices in the list were not sorted! ");
    }
}

bool DataAnalyser::checkDataIndex() {
    // check if curr_data.data_index == prev_data.data_index + 1
    Data *currDataItem = this->dataStorage->currData;
    vector<Data> allData = this->dataStorage->dataArr;
    if (allData.size() == 0) {
        return true;
    }
    Data prevDataItem = allData.at(allData.size() - 1);
    int currIndex = currDataItem->dataIndex;
    int prevIndex = prevDataItem.dataIndex;
    if (prevIndex != MAX_DATA_INDEX) {
        if (currIndex != prevIndex + 1) {
            this->logger->logError(
                    "Unexpected data index! Prev index: " + to_string(prevIndex) + " " + prevDataItem.dataIndexHex +
                    " curr data: " +
                    to_string(currDataItem->dataIndex) + " " + currDataItem->dataIndexHex);
        }
    } else {
        if (currIndex == 0) {
            this->logger->logError(
                    "Unexpected data index! Prev index: " + to_string(prevIndex) + " " + prevDataItem.dataIndexHex +
                    " curr data: " +
                    to_string(currDataItem->dataIndex) + " " + currDataItem->dataIndexHex);
        }
    }
    return true;
}

template<class T>
vector<T> DataAnalyser::removeEveryOther(vector<T> old_arr) {
    std::vector<string> new_arr;
    for (int i = 0; i < old_arr.size(); i++) {
        if (i % 2 == 0) {
            new_arr.push_back(old_arr.at(i));
        }
    }
    return new_arr;
}
