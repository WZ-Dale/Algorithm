/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/island-perimeter

给定一个包含 0 和 1 的二维网格地图，其中 1 表示陆地 0 表示水域。
网格中的格子水平和垂直方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。
岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。

示例 :
    输入:[[0, 1, 0, 0],
          [1, 1, 1, 0],
          [0, 1, 0, 0],
          [1, 1, 0, 0]]
    输出: 16
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int Dfs(vector<vector<int>>& island, int row, int col, vector<vector<int>>& book, int sr, int sc){
        book[sr][sc] = 1;
        int sum = 0;
        for(int i = 0; i < 4; ++i){
            int newSr = sr + _nextPosition[i][0];
            int newSc = sc + _nextPosition[i][1];
            // 判断新位置是否越界
            if(newSr < 0 || newSr >= row || newSc < 0 || newSc >= col || island[newSr][newSc] == 0){
                ++sum;
                continue;
            }
            // 如果新位置为1，且未标记过则进入
            if(island[newSr][newSc] == 1 && book[newSr][newSc] == 0){
                sum += Dfs(island, row, col, book, newSr, newSc);
            }
        }
        return sum;
    }    
    int islandPerimeter(vector<vector<int>>& island, int row, int col, int sr, int sc){
        if(island.empty()){
            return 0;
        }
        // 建立标记
        vector<vector<int>> book(row, vector<int>(col, 0));
        return Dfs(island, row, col, book, sr, sc);
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
    vector<vector<int>> island = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}};
    print_island(island);
    int row = island.size();
    int col = island[0].size();
    int sr = -1, sc = -1;
    // 找出第一个 1
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            if(island[i][j] == 1){
                sr = i;
                sc = j;
                break;
            }
        }
        if(sr != -1){
            break;
        }
    }
    if(sr == -1){
        cout << "inexistence island !!" << endl;
    }
    else{
        Solution S;
        cout << S.islandPerimeter(island, row, col, sr, sc) << endl;  
    }
    return 0;
}