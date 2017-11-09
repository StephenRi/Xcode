//
//  main.cpp
//  529. Minesweeper
//
//  Created by Shuaibing_Zhao on 2017/11/9.
//  Copyright © 2017年 Shuaibing_Zhao. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> updateBoard(vector<vector<char>> & board, vector<int> & click);
void dfs(vector<vector<char>> & board, int curX, int curY);
bool inBoard(vector<vector<char>> & board, int x, int y);

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<vector<char>> input = {
        {'E', 'E', 'E', 'E', 'E'},
        {'E', 'E', 'M', 'E', 'E'},
        {'E', 'E', 'E', 'E', 'E'},
        {'E', 'E', 'E', 'E', 'E'}
    };
    vector<int> clickPos = {3, 0};
    
    vector<vector<char>> answer = updateBoard(input, clickPos);
    
    for (int i = 0; i < answer.size(); i++) {
        for (int j = 0; j < answer[0].size(); j++) {
            printf("%4c", answer[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
    //1. 如果当前按的位置是一个雷，直接标X返回
    if(board[click[0]][click[1]] == 'M') {
        board[click[0]][click[1]] = 'X';
        return board;
    }
    dfs(board, click[0], click[1]);
    return board;
}

void dfs(vector<vector<char>> & board, int curX, int curY) {
    int mineCount = 0;      //周围雷数
    //adjacent表示当前位置周围的8个方向
    int adjacent[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    //统计一下当前按的位置周围的雷数
    for (int i = 0; i < 8; i++) {
        if(inBoard(board, curX + adjacent[i][0], curY + adjacent[i][1])) {
            if (board[curX + adjacent[i][0]][curY + adjacent[i][1]] == 'M') {
                mineCount ++;
            }
        }
    }
    
    //2. 如果当前按的位置周围有雷，把该格子设置为雷数
    if (mineCount > 0) {
        board[curX][curY] = '0' + mineCount;
        return;
    }
    
    //3. 如果当前按的位置周围没有雷，将该位置置为B，递归查看周围8个未翻的格子
    board[curX][curY] = 'B';
    for (int i = 0; i < 8; i++) {
        if (inBoard(board, curX + adjacent[i][0], curY + adjacent[i][1]) && board[curX + adjacent[i][0]][curY + adjacent[i][1]] == 'E') {
            dfs(board, curX + adjacent[i][0], curY + adjacent[i][1]);
        }
    }
    
    
}

/**
 判断该位置是否在给定的面板内

 @param board 游戏面板
 @param x x坐标
 @param y y坐标
 @return 是否在面板内
 */
bool inBoard(vector<vector<char>> & board, int x, int y) {
    if(x < 0 || x > board.size() - 1 || y < 0 || y > board[0].size() - 1) {
        return false;
    } else {
        return true;
    }
}
