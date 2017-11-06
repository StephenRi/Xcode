//
//  main.cpp
//  46. Permutations
//
//  Created by Shuaibing_Zhao on 2017/11/5.
//  Copyright © 2017年 Shuaibing_Zhao. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;


/**
 深度优先搜索给出所有序列
 
 @param nums 输入数列
 @param answer 最终结果
 @param subAnswer 最终答案的子答案
 @param usedPos 已经使用过的数字
 @param level 深度优先搜索树的深度
 */
void dfs(vector<int> & nums, vector<vector<int>> & answer, vector<int> & subAnswer, vector<int> usedPos, int level)
{
    if (level >= nums.size())
    {
        answer.push_back(subAnswer);
        return;
    }
    for(int i = 0; i < nums.size(); i++)
    {
        if(usedPos[i] == 0)
        {
            usedPos[i] = 1;
            subAnswer.push_back(nums[i]);
            dfs(nums, answer, subAnswer, usedPos, level + 1);
            usedPos[i] = 0;
            subAnswer.pop_back();
        }
    }
}

vector<vector<int>> permute(vector<int> & nums) {
    vector<vector<int>> answer;
    if(nums.size() == 0)
    {
        return answer;
    }
    vector<int> subAnswer;
    vector<int> usedPos(nums.size(), 0);
    dfs(nums, answer, subAnswer, usedPos, 0);
    return answer;
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
    cout << "输入数组的全排列如下所示： " << endl;
    for(int i = 0; i < output.size(); i++)
    {
        for(int j = 0; j < output[0].size(); j++)
        {
            cout << output[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
