//
// Created by papraczy on 06/11/2019.
//

#include <ios>
#include <sstream>
#include "Calculator.h"

int Calculator::getInt(string num_str) {
    return stoi(num_str, 0, HEX_BASE);
}

vector<int> Calculator::getNumberSequence(int numSeqLen) {
    vector<int> numSeq;
    for(int i = 0; i < numSeqLen; i++){
        numSeq.push_back(i);
    }
    return numSeq;
}

string Calculator::getBinary(int num) {
    string new_num;
    while (num > 0)
    {
        int digit = num % 2;
        new_num = to_string(digit) + new_num;
        num /= 2;
    }
    return new_num;
}

string Calculator::getHex(int num) {
    stringstream stream;
    stream << hex << num;
    string result = stream.str();
    if(result.length() < 2)
        result = "0" + result;
    return result;
}
