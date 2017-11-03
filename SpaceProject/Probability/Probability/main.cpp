//
//  main.cpp
//  Probability
//
//  Created by Shuaibing_Zhao on 2017/9/14.
//  Copyright © 2017年 Shuaibing_Zhao. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

/**
 从n个数中取出m个的组合种数
 n      数据总数
 m      选取数目
 **/
int combination(int n, int m)
{
    if(m >= n / 2)
    {
        m = n - m;
    }
    if(m == 0)
    {
        return 1;
    }
    int dividend = 1;
    int divisor = 1;
    int answer = 0;
    for(int i = 1; i <= m; i++)
    {
        dividend *= (n - i + 1);
        divisor *= i;
    }
    answer = dividend / divisor;
    return answer;
}

/**
 根据单位的翻转概率求一个条纹可以正常无故障的概率
 dataBits               数据位数
 parityBits             校验位数
 edacCapability         纠错能力
 reversalProbability    位翻转率
 **/
double getUndamagedProbability(int dataBits, int parityBits, int edacCapability, double reversalProbability)
{
    double answer = 0;
    int codeLength = dataBits + parityBits;             //码长
    for(int i = 0; i <= edacCapability; i++)
    {
        answer += combination(codeLength, i) * pow(reversalProbability, i) * pow(1 - reversalProbability, codeLength - i);
    }
    return answer;
}

int main(int argc, const char * argv[])
{
    // insert code here...
    int dataBits = 512;
    int parityBits = 15;
    int edacCapability = 6;
    double reversalProbability = 0.000108;
    cout << setprecision(30);
    cout << "一个校验组不出无法修复的错误的概率为: " << getUndamagedProbability(dataBits, parityBits, edacCapability, reversalProbability) << endl;
    cout << "erased probability is: " << 1- pow(getUndamagedProbability(dataBits, parityBits, edacCapability, reversalProbability), 4096) << endl;
    system("pause");
    return 0;
}

