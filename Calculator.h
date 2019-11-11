//
// Created by papraczy on 06/11/2019.
//

#ifndef SERVER_CALCULATOR_H
#define SERVER_CALCULATOR_H

#include <string>
#include <vector>

#define HEX_BASE 16

using namespace std;

class Calculator {
public:
    static int getInt(string num_str);
    static vector<int> getNumberSequence(int numSeqLen);
    static string getBinary(int num);
    static string getHex(int num);
};


#endif //SERVER_CALCULATOR_H
