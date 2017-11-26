//
//  BCHCode.hpp
//  BCH(50, 32)
//
//  Created by Shuaibing_Zhao on 2017/11/24.
//  Copyright © 2017年 Shuaibing_Zhao. All rights reserved.
//

#ifndef BCHCode_h
#define BCHCode_h

#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <math.h>
#include <bitset>
#include <unordered_map>

using namespace std;

const int dataLen = 32;
const int parityLen = 18;
const int codeLen = 50;

class BCHCode {
public:
    void BCHEncode(bitset<dataLen> & input, bitset<codeLen> & output);
    void BCHDecode(bitset<codeLen> & input, bitset<codeLen> & output);
    void getParityXOR(bitset<codeLen> & input, bitset<parityLen> & output);
    void setTable();
    void getTable();
    void testBCH();
    void errTest3();
    void errTest4();
};

#endif /* BCHCode_h */



