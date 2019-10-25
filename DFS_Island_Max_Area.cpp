/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/max-area-of-island

给定一个包含了一些 0 和 1 的非空二维数组 grid , 一个 岛屿 是由四个方向 (水平或垂直) 的 1 (代表土地) 构成的组合。你可以假设二维矩阵的四个边缘都被水包围着。
找到给定的二维数组中最大的岛屿面积。(如果没有岛屿，则返回面积为0。)
示例 1:
        {0,0,1,0,0,0,0,1,0,0,0,0,0},
         {0,0,0,0,0,0,0,1,1,1,0,0,0},
         {0,1,1,0,1,0,0,0,0,0,0,0,0},
         {0,1,0,0,1,1,0,0,1,0,1,0,0},
         {0,1,0,0,1,1,0,0,1,1,1,0,0},
         {0,0,0,0,0,0,0,0,0,0,1,0,0},
         {0,0,0,0,0,0,0,1,1,1,0,0,0},
         {0,0,0,0,0,0,0,1,1,0,0,0,0}}
    对于上面这个给定矩阵应返回 6。注意答案不应该是11，因为岛屿只能包含水平或垂直的四个方向的‘1’。
示例 2:
        {{0,0,0,0,0,0,0,0}}
    对于上面这个给定的矩阵, 返回 0。
注意: 给定的矩阵grid 的长度和宽度都不超过 50。
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int Dfs(vector<vector<int>>& island, int row, int col, vector<vector<int>>& book, int sr, int sc){
        //处理当前逻辑
        int area = 1;
        book[sr][sc] = 1;
        //遍历每一种可能，四个方向
        for(int i = 0; i < 4; ++i){
            int newSr = sr + _nextPosition[i][0];
            int newSc = sc + _nextPosition[i][1];
            //判断新位置是否越界
            if(newSr < 0 || newSr >= row || newSc < 0 || newSc >= col){
                continue;
            }
            //如果符合要求，并且之前也没有标记过，则继续
            if(island[newSr][newSc] == 1 && book[newSr][newSc] == 0){
                area += Dfs(island, row, col, book, newSr, newSc);
            }
        }
        return area;
    }
    int maxAreaOfIsland(vector<vector<int>>& island){
        if(island.empty()){
            return 0;
        }
        int maxArea = 0;
        int row = island.size();
        int col = island[0].size();
        vector<vector<int>> book(row, vector<int>(col, 0));
        //以每一个网格点为起点开始
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                if(island[i][j] == 1 && book[i][j] == 0){
                    maxArea = max(maxArea, Dfs(island, row, col, book, i, j));
                }
            }
        }
        return maxArea;
    }
private:
    // 四个方向的位置更新：顺时针更新
    int _nextPosition[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
};
void print_island(vector<vector<int>>& island){
    for(int i = 0; i < island.size(); ++i){
        for(int j = 0; j < island[0].size(); ++j){
            cout << island[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    vector<vector<int>> island = {{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                  {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
                                  {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};
    print_island(island);
    Solution S;
    cout << S.maxAreaOfIsland(island) << endl;
    return 0;
}