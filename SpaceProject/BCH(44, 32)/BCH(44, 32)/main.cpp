//
//  main.cpp
//  BCH(44, 32)
//
//  Created by Shuaibing_Zhao on 2017/11/8.
//  Copyright © 2017年 Shuaibing_Zhao. All rights reserved.
//

#include <iostream>
#include "BCHCode.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    BCHCode * bch = new BCHCode();
    bch->setTable();
    
    
    return 0;
}
