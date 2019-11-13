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
    static void getNumberSequence(int numSeqLen, vector<int> *numSeq);
    static string getBinary(int num);
    static string getHex(int num);
    static bool checkVectorEquality(vector<int> *v1, vector<int> *v2);
};


#endif //SERVER_CALCULATOR_H
