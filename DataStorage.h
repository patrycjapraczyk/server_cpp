//
// Created by papraczy on 05/11/2019.
//

#ifndef SERVER_DATASTORAGE_H
#define SERVER_DATASTORAGE_H

#define MAX_SIZE 20

#include "Data.h"
#include <vector>
#include <iostream>
using namespace std;

class DataStorage
{
public:
    DataStorage();
    ~DataStorage();
    Data *currData;
    void saveCurrentData();
    vector<Data> dataArr;
};


#endif //SERVER_DATASTORAGE_H
