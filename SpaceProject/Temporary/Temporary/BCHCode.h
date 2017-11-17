//
//  Tmp1.hpp
//  Temporary
//
//  Created by Shuaibing_Zhao on 2017/11/17.
//  Copyright © 2017年 Shuaibing_Zhao. All rights reserved.
//

#ifndef BCHCode_h
#define BCHCode_h

#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

const int dataLen = 32;
const int parityLen = 12;
const int codeLen = 44;

void bin2Dec(vector<int> & input, long long int & output);                //将一串二进制数转换为十进制的一个长整数
void dec2Bin(long long int & input, vector<int> & output);                //将十进制的一个长整数转换为一串二进制数

class BCHCode {
public:
    void BCHEncode(vector<int> & input, vector<int> & output);
    void BCHDecode(vector<int> & input, vector<int> & output);
    void getParityXOR(vector<int> & input, vector<int> & output);
    void setTable();
};

#endif /* BCHCode_h */



