//
//  BCHCode.cpp
//  BCH(50, 32)
//
//  Created by Shuaibing_Zhao on 2017/11/24.
//  Copyright © 2017年 Shuaibing_Zhao. All rights reserved.
//

#include "BCHCode.h"

bitset<dataLen> enInput("00000000000000000000000000000000");
bitset<codeLen> enOutput;
bitset<codeLen> deInput;
bitset<codeLen> deOutput;
bitset<parityLen> parityXOR;

unordered_map<bitset<parityLen>, bitset<codeLen>> errTable;

//  BCH(50, 32)生成矩阵
const vector<vector<int>> generateMatrix = {
    {0, 1, 4, 5, 6, 7, 9, 11, 14, 16, 17, 20, 21, 22, 23, 24, 27, 30, 31},                                  //p0
    {0, 2, 4, 8, 9, 10, 11, 12, 14, 15, 16, 18, 20, 25, 27, 28, 30},                                        //p1
    {0, 3, 4, 6, 7, 10, 12, 13, 14, 15, 19, 20, 22, 23, 24, 26, 27, 28, 29, 30},                            //p2
    {0, 6, 8, 9, 13, 15, 17, 22, 25, 28, 29},                                                               //p3
    {1, 7, 9, 10, 14, 16, 18, 23, 26, 29, 30},                                                              //p4
    {2, 8, 10, 11, 15, 17, 19, 24, 27, 30, 31},                                                             //p5
    {3, 9, 11, 12, 16, 18, 20, 25, 28, 31},                                                                 //p6
    {4, 10, 12, 13, 17, 19, 21, 26, 29},                                                                    //p7
    {5, 11, 13, 14, 18, 20, 22, 27, 30},                                                                    //p8
    {0, 1, 4, 5, 7, 9, 11, 12, 15, 16, 17, 19, 20, 22, 24, 27, 28, 30},                                     //p9
    {1, 2, 5, 6, 8, 10, 12, 13, 16, 17, 18, 20, 21, 23, 25, 28, 29, 31},                                    //p10
    {0, 1, 2, 3, 4, 5, 13, 16, 18, 19, 20, 23, 26, 27, 29, 31},                                             //p11
    {0, 2, 3, 7, 9, 11, 16, 19, 22, 23, 28, 31},                                                            //p12
    {1, 3, 4, 8, 10, 12, 17, 20, 23, 24, 29},                                                               //p13
    {2, 4, 5, 9, 11, 13, 18, 21, 24, 25, 30},                                                               //p14
    {0, 1, 3, 4, 7, 9, 10, 11, 12, 16, 17, 19, 20, 21, 23, 24, 25, 26, 27, 30},                             //p15
    {0, 2, 6, 7, 8, 9, 10, 12, 13, 14, 16, 18, 23, 25, 26, 28, 30},                                         //p16
    {0, 3, 4, 5, 6, 8, 10, 13, 15, 16, 19, 20, 21, 22, 23, 26, 29, 30},                                     //p17
    {0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15},                   //data0 ~ 15
    {16}, {17}, {18}, {19}, {20}, {21}, {22}, {23}, {24}, {25}, {26}, {27}, {28}, {29}, {30}, {31}          //data16 ~ 31
};

//  BCH(50, 32)伴随矩阵，其实就是新旧校验位的异或值
const vector<vector<int>> adjointMatrix = {
    {0, 18, 19, 22, 23, 24, 25, 27, 29, 32, 34, 35, 38, 39, 40, 41, 42, 45, 48, 49},                        //a0
    {1, 18, 20, 22, 26, 27, 28, 29, 30, 32, 33, 34, 36, 38, 43, 45, 46, 48},                                //a1
    {2, 18, 21, 22, 24, 25, 28, 30, 31, 32, 33, 37, 38, 40, 41, 42, 44, 45, 46, 47, 48},                    //a2
    {3, 18, 24, 26, 27, 31, 33, 35, 40, 43, 46, 47},                                                        //a3
    {4, 19, 25, 27, 28, 32, 34, 36, 41, 44, 47, 48},                                                        //a4
    {5, 20, 26, 28, 29, 33, 35, 37, 42, 45, 48, 49},                                                        //a5
    {6, 21, 27, 29, 30, 34, 36, 38, 43, 46, 49},                                                            //a6
    {7, 22, 28, 30, 31, 35, 37, 39, 44, 47},                                                                //a7
    {8, 23, 29, 31, 32, 36, 38, 40, 45, 48},                                                                //a8
    {9, 18, 19, 22, 23, 25, 27, 29, 30, 33, 34, 35, 37, 38, 40, 42, 45, 46, 48},                            //a9
    {10, 19, 20, 23, 24, 26, 28, 30, 31, 34, 35, 36, 38, 39, 41, 43, 46, 47, 49},                           //a10
    {11, 18, 19, 20, 21, 22, 23, 31, 34, 36, 37, 38, 41, 44, 45, 47, 49},                                   //a11
    {12, 18, 20, 21, 25, 27, 29, 34, 37, 40, 41, 46, 49},                                                   //a12
    {13, 19, 21, 22, 26, 28, 30, 35, 38, 41, 42, 47},                                                       //a13
    {14, 20, 22, 23, 27, 29, 31, 36, 39, 42, 43, 48},                                                       //a14
    {15, 18, 19, 21, 22, 25, 27, 28, 29, 30, 34, 35, 37, 38, 39, 41, 42, 43, 44, 45, 48},                   //a15
    {16, 18, 20, 24, 25, 26, 27, 28, 30, 31, 32, 34, 36, 41, 43, 44, 46, 48},                               //a16
    {17, 18, 21, 22, 23, 24, 26, 28, 31, 33, 34, 37, 38, 39, 40, 41, 44, 47, 48}                            //a17
};


/**
 BCH编码
 
 @param input 输入32位信息位
 @param output 输出50位编码后的BCH码
 */
void BCHCode::BCHEncode(bitset<dataLen> & input, bitset<codeLen> & output) {
//    //根据生成矩阵print the adjoinMatrix
//    for (int i = 0; i < generateMatrix.size(); i++) {
//        cout << i << ", ";
//        for (int j = 0; j < generateMatrix[i].size(); j++) {
//            cout << generateMatrix[i][j] + parityLen << ", ";
//        }
//        cout << endl;
//    }
    
    //printf("BCHEncode start...\n");
    for (int i = 0; i < generateMatrix.size(); i++) {
        output[i] = 0;
        for (int j = 0; j < generateMatrix[i].size(); j++) {
            //output[i] ^= input[generateMatrix[i][j]];
            if (input.test(generateMatrix[i][j])) {
                output.flip(i);
            }
        }
    }
    //printf("BCHEncode end...\n");
}


void BCHCode::BCHDecode(bitset<codeLen> & input, bitset<codeLen> & output) {
    getParityXOR(input, parityXOR);
    //如果没有错误
    if (!parityXOR.any()) {
        output = input;
        return;
    }
    //如果errTable中有该错误模式，则修复
    auto existTable = errTable.find(parityXOR);
    if (existTable != errTable.end()) {
        output = input ^ errTable[parityXOR];
    } else {
        output = input;
        cout << "\t错误过多，无法修复" << endl;
    }
}


/**
 求错误伴随式
 
 @param input 接收到的数据
 @param output 错误伴随式
 */
void BCHCode::getParityXOR(bitset<codeLen> & input, bitset<parityLen> & output) {
    //printf("getParityXOR start...\n");
    for (int i = 0; i < adjointMatrix.size(); i++) {
        output[i] = 0;
        for (int j = 0; j < adjointMatrix[i].size(); j++) {
            //output[i] ^= input[adjointMatrix[i][j]];
            if (input.test(adjointMatrix[i][j])) {
                output.flip(i);
            }
        }
    }
    //printf("getParityXOR end...\n");
}


/**
 制表，保存所有的1位或2位错误导致的新旧校验位异或值
 */
void BCHCode::setTable() {
    //生成文件流
    string fileName = "errTableBCH_50_32.txt";
    ofstream fout(fileName, ios::binary);
    fout << "Loc\t" << "XOR\t" << "\n";
    
    //编码
    //cout << enInput << endl;
    BCHEncode(enInput, enOutput);
    //cout << enOutput << endl;
    
    //出现1位错误，错误位置位errLoc
    for(int errLoc = 0; errLoc < codeLen; errLoc ++) {
        //memcpy(deInput, enOutput, codeLen * sizeof(int));
        deInput = enOutput;
        deInput.flip(errLoc);             //翻转第errLoc位
        
        getParityXOR(deInput, parityXOR);
        
        bitset<codeLen> tmp;
        tmp.flip(errLoc);
        fout << tmp << "\t" << parityXOR << "\t" << "\n";
        //fout << parityXOR << "\n";
    }
    
    //出现2位错误，错误位置为errLoc1和errLoc2
    for (int errLoc1 = 0; errLoc1 < codeLen - 1; errLoc1 ++) {
        for (int errLoc2 = errLoc1 + 1; errLoc2 < codeLen; errLoc2 ++) {
            //memcpy(deInput, enOutput, codeLen * sizeof(int));
            deInput = enOutput;
            deInput.flip(errLoc1);            //翻转第errLoc1位
            deInput.flip(errLoc2);            //翻转第errLoc2位
            
            getParityXOR(deInput, parityXOR);
            
            bitset<codeLen> tmp;
            tmp.flip(errLoc1);
            tmp.flip(errLoc2);
            fout << tmp << "\t" << parityXOR << "\t" << "\n";
            //fout << parityXOR << "\n";
        }
    }
}


/**
 读表，并倒排保存到errTable中，下标为伴随式，值为错误位置
 */
void BCHCode::getTable() {
    //生成文件流
    string fileName = "errTableBCH_50_32.txt";
    ifstream fin(fileName, ios::binary);
    string tmpStr;
    bitset<codeLen> tmp1;
    bitset<parityLen> tmp2;
    fin >> tmpStr >> tmpStr;            //去表头
    while (!fin.eof()) {
        fin >> tmp1 >> tmp2;
        errTable[tmp2] = tmp1;
    }
}


/**
 BCH编码测试程序
 */
void BCHCode::testBCH() {
    cout << "$1:\tsetTable(制作错误位置表，保存到errTableBCH_50_32.txt)" << endl;
    setTable();
    cout << "$2:\tgetTable(从errTable.txt读去错误模式，并倒排保存到errTable数组中，下标为伴随式，值为错误位置)" << endl;
    getTable();
    
    cout << "$3:\t生成随机输入序列：\t";
    srand((unsigned int)time(NULL));
    int tmp = 0;
    enInput.reset();
    for (int i = 0; i < dataLen; i ++) {
        tmp = rand() % 2;
        if (tmp) {
            enInput.set(i);
        }
    }
    cout << enInput << endl;
    BCHEncode(enInput, enOutput);
    cout << "\tBCH编码后的码字：\t";
    cout << enOutput << endl;
    
    bool notEnd = 1;
    while (notEnd) {
        cout << "$4:\t输入1个或2个错误位置：\t";
        vector<int> errLoc;
        int tmpLoc = 0;
        while(cin >> tmpLoc) {
            errLoc.push_back(tmpLoc);
            if(cin.get() == '\n')
                break;
        }
        deInput = enOutput;
        for (int i = 0; i < errLoc.size(); i ++) {
            deInput.flip(errLoc[i]);
        }
        cout << "\t注入错误后的接收信息序列：\t" << deInput << endl;
        BCHDecode(deInput, deOutput);
        cout << "\t修复错误后的接收信息序列：\t" << deOutput << endl;
        if (deOutput == enOutput) {
            cout << "\t修复成功" << endl;
        } else {
            cout << "\t修复失败" << endl;
        }
    }
}



/**
 测试出现3个位错误时，会不会有冲突。枚举3个位错误的情况，然后查errTable表，如果能查到，说明有冲突。
 如果有，这种编码方案就不适合做字内编码
 */
void BCHCode::errTest3() {
    cout << "$1:\tsetTable(制作错误位置表，保存到errTableBCH_50_32.txt)" << endl;
    setTable();
    cout << "$2:\tgetTable(从errTable.txt读取错误模式，并倒排保存到errTable数组中，下标为伴随式，值为错误位置)" << endl;
    getTable();
    
    cout << "$3:\terrTest(遍历3个错误的情况，得到新旧校验异或，并查询errTable，如果存在，则有冲突)" << endl;
    for (int errLoc1 = 0; errLoc1 < codeLen - 2; errLoc1 ++) {
        for (int errLoc2 = errLoc1 + 1; errLoc2 < codeLen - 1; errLoc2 ++) {
            for (int errLoc3 = errLoc2 + 1; errLoc3 < codeLen; errLoc3 ++) {
                deInput.reset();                //deInput置零
                deInput.flip(errLoc1);
                deInput.flip(errLoc2);
                deInput.flip(errLoc3);
                getParityXOR(deInput, parityXOR);
                //输出冲突项
                auto findConflict = errTable.find(parityXOR);
                if (findConflict != errTable.end()) {
                    cout << "\tfind conflict at: \t" << findConflict->first << "\tfor err: \t" << deInput << endl;
                }
            }
        }
    }
}


/**
 测试出现4个位错误时，会不会有冲突。枚举4个位错误的情况，然后查errTable表，如果能查到，说明有冲突。
 如果有，这种编码方案就不适合做字内编码
 */
void BCHCode::errTest4() {
    cout << "$1:\tsetTable(制作错误位置表，保存到errTableBCH_50_32.txt)" << endl;
    setTable();
    cout << "$2:\tgetTable(从errTable.txt读取错误模式，并倒排保存到errTable数组中，下标为伴随式，值为错误位置)" << endl;
    getTable();
    
    cout << "$3:\terrTest(遍历4个错误的情况，得到新旧校验异或，并查询errTable，如果存在，则有冲突)" << endl;
    for (int errLoc1 = 0; errLoc1 < codeLen - 3; errLoc1 ++) {
        for (int errLoc2 = errLoc1 + 1; errLoc2 < codeLen - 2; errLoc2 ++) {
            for (int errLoc3 = errLoc2 + 1; errLoc3 < codeLen - 1; errLoc3 ++) {
                for (int errLoc4 = errLoc3 + 1; errLoc4 < codeLen; errLoc4 ++) {
                    deInput.reset();                //deInput置零
                    deInput.flip(errLoc1);
                    deInput.flip(errLoc2);
                    deInput.flip(errLoc3);
                    deInput.flip(errLoc4);
                    getParityXOR(deInput, parityXOR);
                    //输出冲突项
                    auto findConflict = errTable.find(parityXOR);
                    if (findConflict != errTable.end()) {
                        cout << "\tfind conflict at: \t" << findConflict->first << "\tfor err: \t" << deInput << endl;
                    }
                }
            }
        }
    }
}
