//
//  main.cpp
//  Permutations
//
//  Created by Shuaibing_Zhao on 2017/11/5.
//  Copyright © 2017年 Shuaibing_Zhao. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> answer;
    vector<int> subAnswer;
    
    return answer;
}

void dfs(vector<int> & nums, vector<vector<int>> & answer, vector<int> subAnswer, int level)
{
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> input;
    cout << "该程序给出一个整数数组的全排列" << endl;
    cout << "请输入您的数组（以#结束）： ";
    int tmp;
    while(cin >> tmp)
    {
        input.push_back(tmp);
    }
    vector<vector<int>> output = permute(input);
    
    return 0;
}
