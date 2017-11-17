//
//  main.cpp
//  Temporary
//
//  Created by Shuaibing_Zhao on 2017/11/17.
//  Copyright © 2017年 Shuaibing_Zhao. All rights reserved.
//

#include <iostream>
#include "BCHCode.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    BCHCode * bch = new BCHCode();
    bch->setTable();
    
    long long a = 0x0000000000000008;
    cout << a << endl;
    a >>= 2;
    cout << a << endl;
    return 0;
}
