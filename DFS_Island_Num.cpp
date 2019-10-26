/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/number-of-islands

给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。
一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

示例 1:
    输入:
        1 1 1 1 0
        1 1 0 1 0
        1 1 0 0 0
        0 0 0 0 0
    输出: 1
示例 2:
    输入:
        1 1 0 0 0
        1 1 0 0 0
        0 0 1 0 0
        0 0 0 1 1
    输出: 3
*/
#include <iostream>
#include <vector>

using namespace std;
/*
本题的意思是连在一起的陆地都算做一个岛屿，本题可以采用类似渲染的做法，尝试以每个点作为渲染的起点，可以渲染
的陆地都算做一个岛屿，最后看渲染了多少次，即深度优先算法执行了多少次
*/
class Solution
{
public:
    void Dfs(vector<vector<char>>& island, int row, int col, vector<vector<int>>& book, int sr, int sc){
        //处理当前逻辑
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
            if(island[newSr][newSc] == '1' && book[newSr][newSc] == 0){
                Dfs(island, row, col, book, newSr, newSc);
            }
        }
    }
    int islandNum(vector<vector<char>>& island){
        if(island.empty()){
            return 0;
        }
        int num = 0;
        int row = island.size();
        int col = island[0].size();
        vector<vector<int>> book(row, vector<int>(col, 0));
        //以每一个网格点为起点开始
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                if(island[i][j] == '1' && book[i][j] == 0){
                    ++num;
                    Dfs(island, row, col, book, i, j);
                }
            }
        }
        return num;
    }
private:
    // 四个方向的位置更新：顺时针更新
    int _nextPosition[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
};
void print_island(vector<vector<char>>& island){
    for(int i = 0; i < island.size(); ++i){
        for(int j = 0; j < island[0].size(); ++j){
            cout << island[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    vector<vector<char>> island = {{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}};
    print_island(island);
    Solution S;
    cout << S.islandNum(island) << endl;

    vector<vector<char>> island1 = {{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}};
    print_island(island1);
    cout << S.islandNum(island1) << endl;
    return 0;
}