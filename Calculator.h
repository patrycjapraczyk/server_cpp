//
// Created by papraczy on 06/11/2019.
//

#ifndef SERVER_CALCULATOR_H
#define SERVER_CALCULATOR_H

#include <string>
#include <vector>

using namespace std;

class Calculator {
public:
    static int getInt(string num_str);
    static vector<int> getNumberSequence(int numSeqLen);

};


#endif //SERVER_CALCULATOR_H
