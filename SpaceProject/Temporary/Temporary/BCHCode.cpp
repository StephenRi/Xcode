//
//  Tmp1.cpp
//  Temporary
//
//  Created by Shuaibing_Zhao on 2017/11/17.
//  Copyright © 2017年 Shuaibing_Zhao. All rights reserved.
//

#include "BCHCode.h"

vector<int> enInput = {
    0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0, 0, 0
};
vector<int> enOutput(codeLen);
vector<int> deInput(codeLen);
vector<int> deOutput(codeLen);
vector<int> parityXOR(parityLen);

/**
 //效率低，删掉
 const int generateMatrix[12][32] = {
 {1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1,   0, 1, 0, 0, 0, 1, 1, 0, 0, 0,   1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0},       //p0
 {0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1,   1, 0, 1, 0, 0, 0, 1, 1, 0, 0,   0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0},       //p1
 {1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1,   1, 0, 0, 1, 0, 1, 1, 1, 1, 0,   1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1},       //p2
 {0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1,   1, 1, 0, 0, 1, 0, 1, 1, 1, 1,   0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1},       //p3
 {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,   1, 0, 1, 0, 0, 0, 1, 1, 1, 1,   0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0},       //p4
 {0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0,   0, 1, 0, 1, 0, 0, 0, 1, 1, 1,   1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0},       //p5
 {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,   0, 0, 1, 0, 1, 0, 0, 0, 1, 1,   1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1},       //p6
 {1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1,   0, 1, 0, 1, 0, 0, 1, 0, 0, 1,   0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1},       //p7
 {1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0,   1, 1, 1, 0, 1, 1, 1, 1, 0, 0,   0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},       //p8
 {0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0,   0, 0, 1, 1, 0, 0, 0, 1, 1, 0,   1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0},       //p9
 {0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1,   0, 0, 0, 1, 1, 0, 0, 0, 1, 0,   0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0},       //p10
 {0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0,   1, 0, 0, 0, 1, 1, 0, 0, 0, 1,   1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1}        //p11
 };
 */

//  BCH(44, 32)生成矩阵
const vector<vector<int>> generateMatrix = {
    {0, 3, 4, 5, 6, 9, 10, 12, 16, 17, 21, 22, 24, 25, 26, 27, 28, 29},                                     //p0
    {1, 4, 5, 6, 7, 10, 11, 13, 17, 18, 22, 23, 25, 26, 27, 28, 29, 30},                                    //p1
    {0, 2, 3, 4, 7, 8, 9, 10, 11, 14, 16, 17, 18, 19, 21, 22, 23, 25, 30, 31},                              //p2
    {1, 3, 4, 5, 8, 9, 10, 11, 12, 15, 17, 18, 19, 20, 22, 23, 24, 26, 31},                                 //p3
    {0, 2, 3, 11, 13, 17, 18, 19, 20, 22, 23, 26, 28, 29},                                                  //p4
    {1, 3, 4, 12, 14, 18, 19, 20, 21, 23, 24, 27, 29, 30},                                                  //p5
    {4, 5, 13, 15, 19, 20, 21, 22, 24, 25, 28, 30, 31},                                                     //p6
    {0, 4, 9, 10, 12, 14, 17, 20, 23, 24, 27, 28, 31},                                                      //p7
    {0, 1, 3, 4, 6, 9, 11, 12, 13, 15, 16, 17, 18, 22, 26, 27},                                             //p8
    {1, 2, 3, 6, 7, 9, 13, 14, 18, 19, 21, 22, 23, 24, 25, 26, 29},                                         //p9
    {1, 2, 3, 4, 7, 8, 10, 14, 15, 19, 22, 23, 24, 25, 26, 27, 30},                                         //p10
    {2, 3, 4, 5, 8, 9, 11, 15, 16, 20, 21, 23, 24, 25, 26, 27, 28, 31},                                     //p11
    {0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15},                   //data0 ~ 15
    {16}, {17}, {18}, {19}, {20}, {21}, {22}, {23}, {24}, {25}, {26}, {27}, {28}, {29}, {30}, {31}          //data16 ~ 31
};

/**
 //  BCH(44, 32)伴随矩阵，论文里的这种方法貌似有问题，暂时不用了
 const vector<vector<int>> adjointMatrix = {
 {0, 12, 15, 16, 17, 18, 21, 22, 24, 28, 29, 33, 34, 36, 37, 38, 39, 40, 41},                            //a0
 {1, 13, 16, 17, 18, 19, 22, 23, 25, 29, 30, 34, 35, 37, 38, 39, 40, 41, 42},                            //a1
 {2, 12, 14, 15, 16, 19, 20, 21, 22, 23, 26, 28, 29, 30, 31, 33, 34, 35, 37, 43},                        //a2
 {3, 13, 15, 16, 17, 20, 21, 22, 23, 24, 27, 29, 30, 31, 32, 34, 35, 36, 38, 43},                        //a3
 {4, 12, 14, 15, 23, 25, 21, 29, 30, 31, 32, 34, 35, 38, 40, 41},                                        //a4
 {5, 13, 15, 16, 24, 26, 30, 31, 32, 33, 35, 36, 39, 41, 42},                                            //a5
 {6, 14, 16, 17, 25, 27, 31, 32, 33, 34, 36, 37, 40, 42, 43},                                            //a6
 {7, 12, 16, 21, 22, 24, 26, 29, 32, 35, 36, 39, 40, 43},                                                //a7
 {8, 12, 13, 15, 16, 18, 21, 23, 24, 25, 27, 28, 29, 30, 34, 38, 39},                                    //a8
 {9, 12, 13, 14, 15, 18, 19, 21, 25, 26, 30, 31, 33, 34, 35, 36, 37, 38, 41},                            //a9
 {10, 13, 14, 15, 16, 19, 20, 22, 26, 27, 31, 32, 34, 35, 36, 37, 38, 39, 42},                           //a10
 {11, 14, 15, 16, 17, 20, 21, 23, 27, 28, 32, 33, 35, 36, 37, 38, 39, 40, 43}                            //a11
 };
 **/

//  BCH(44, 32)伴随矩阵
const vector<vector<int>> adjointMatrix = {
    {0, 12, 15, 16, 17, 18, 21, 22, 24, 28, 29, 33, 34, 36, 37, 38, 39, 40, 41},                            //a0
    {1, 13, 16, 17, 18, 19, 22, 23, 25, 29, 30, 34, 35, 37, 38, 39, 40, 41, 42},                            //a1
    {2, 12, 14, 15, 16, 19, 20, 21, 22, 23, 26, 28, 29, 30, 31, 33, 34, 35, 37, 42, 43},                    //a2
    {3, 13, 15, 16, 17, 20, 21, 22, 23, 24, 27, 29, 30, 31, 32, 34, 35, 36, 38, 43},                        //a3
    {4, 12, 14, 15, 23, 25, 29, 30, 31, 32, 34, 35, 38, 40, 41},                                            //a4
    {5, 13, 15, 16, 24, 26, 30, 31, 32, 33, 35, 36, 39, 41, 42},                                            //a5
    {6, 16, 17, 25, 27, 31, 32, 33, 34, 36, 37, 40, 42, 43},                                                //a6
    {7, 12, 16, 21, 22, 24, 26, 29, 32, 35, 36, 39, 40, 43},                                                //a7
    {8, 12, 13, 15, 16, 18, 21, 23, 24, 25, 27, 28, 29, 30, 34, 38, 39},                                    //a8
    {9, 13, 14, 15, 18, 19, 21, 25, 26, 30, 31, 33, 34, 35, 36, 37, 38, 41},                                //a9
    {10, 13, 14, 15, 16, 19, 20, 22, 26, 27, 31, 34, 35, 36, 37, 38, 39, 42},                               //a10
    {11, 14, 15, 16, 17, 20, 21, 23, 27, 28, 32, 33, 35, 36, 37, 38, 39, 40, 43}                            //a11
};


/**
 BCH编码
 
 @param input 输入32位信息位
 @param output 输出44位编码后的BCH码
 */
void BCHCode::BCHEncode(vector<int> & input, vector<int> & output) {
    //printf("BCHEncode start...\n");
    for (int i = 0; i < generateMatrix.size(); i++) {
        output[i] = 0;
        for (int j = 0; j < generateMatrix[i].size(); j++) {
            output[i] ^= input[generateMatrix[i][j]];
        }
    }
    //printf("BCHEncode end...\n");
}

void BCHCode::BCHDecode(vector<int> & input, vector<int> & output) {
    
}

void BCHCode::getParityXOR(vector<int> & input, vector<int> & output) {
    //printf("getParityXOR start...\n");
    for (int i = 0; i < adjointMatrix.size(); i++) {
        output[i] = 0;
        for (int j = 0; j < adjointMatrix[i].size(); j++) {
            output[i] ^= input[adjointMatrix[i][j]];
        }
    }
    //printf("getParityXOR end...\n");
}


/**
 制表，保存所有的1位或2位错误导致的新旧校验位异或值
 */
void BCHCode::setTable() {
    //生成文件流
    string fileName = "errTable.txt";
    ofstream fout(fileName, ios::binary);
    fout << "Loc\t" << "XOR\t" << "\n";
    
    //编码
    BCHEncode(enInput, enOutput);
    for(int i = 0; i < codeLen; i ++) {
        printf("%-2d", enOutput[i]);
    }
    printf("\n");
    
    //出现1位错误，错误位置位errLoc
    for(int errLoc = 0; errLoc < codeLen; errLoc ++) {
        //memcpy(deInput, enOutput, codeLen * sizeof(int));
        deInput.assign(enOutput.begin(), enOutput.end());
        deInput[errLoc] = (deInput[errLoc] == 1) ? 0 : 1;             //翻转第errLoc位
        
        printf("第%d位发生翻转\n", errLoc);
        for(int i = 0; i < codeLen; i ++) {
            printf("%-2d", deInput[i]);
        }
        printf("\n");
        
        getParityXOR(deInput, parityXOR);
        
        for(int i = 0; i < parityLen; i ++) {
            printf("%-2d", parityXOR[i]);
        }
        printf("\n");
    }
    
    //出现2位错误，错误位置为errLoc1和errLoc2
    for (int errLoc1 = 0; errLoc1 < codeLen - 1; errLoc1 ++) {
        for (int errLoc2 = errLoc1 + 1; errLoc2 < codeLen; errLoc2 ++) {
            //memcpy(deInput, enOutput, codeLen * sizeof(int));
            deInput.assign(enOutput.begin(), enOutput.end());
            deInput[errLoc1] = (deInput[errLoc1] == 1) ? 0 : 1;             //翻转第errLoc1位
            deInput[errLoc2] = (deInput[errLoc2] == 1) ? 0 : 1;             //翻转第errLoc2位
            
            printf("第%d位和第%d发生翻转\n", errLoc1, errLoc2);
            for(int i = 0; i < codeLen; i ++) {
                printf("%-2d", deInput[i]);
            }
            printf("\n");
            
            getParityXOR(deInput, parityXOR);
            
            for(int i = 0; i < parityLen; i ++) {
                printf("%-2d", parityXOR[i]);
            }
            printf("\n");
        }
    }
}


void bin2Dec(vector<int> & input, long long int & output) {
    int inputLen = input.size();
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == 1) {
            output += pow(2, i);
        }
    }
}

void dec2Bin(long long int & input, vector<int>  & output) {
    
}


