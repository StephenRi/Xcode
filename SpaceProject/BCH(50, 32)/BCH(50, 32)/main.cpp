//
//  main.cpp
//  BCH(50, 32)
//
//  Created by Shuaibing_Zhao on 2017/11/24.
//  Copyright © 2017年 Shuaibing_Zhao. All rights reserved.
//

#include <iostream>
#include "BCHCode.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    BCHCode * bch = new BCHCode();
    bch->testBCH();
    bch->errTest3();
    bch->errTest4();
    
    return 0;
}

