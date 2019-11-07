//
// Created by papraczy on 06/11/2019.
//

#include "Calculator.h"

int Calculator::getInt(string num_str) {
    return stoi(num_str, 0, 2);
}

vector<int> Calculator::getNumberSequence(int numSeqLen) {
    vector<int> numSeq;
    for(int i = 0; i < numSeqLen; i++){
        numSeq.push_back(i);
    }
    return numSeq;
}
