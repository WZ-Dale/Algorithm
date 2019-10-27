/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/surrounded-regions

给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。
找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。

示例:
    X X X X
    X O O X
    X X O X
    X O X X
运行你的函数后，矩阵变为：
    X X X X
    X X X X
    X X X X
    X O X X
解释: 
    被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。 
    任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。
    如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。
*/
#include <iostream>
#include <vector>

using namespace std;
/*
本题的意思被包围的区间不会存在于边界上，所以边界上的o以及与o联通的都不算做包围，只要把边界上的o以及与之联
通的o进行特殊处理，剩下的o替换成x即可。故问题转化为，如何寻找和边界联通的o，我们需要考虑如下情况。
X X X X
X O O X
X X O X
X O O X
从每一个边缘的o开始，只要和边缘的o联通，则它就没有被包围。
1.首先寻找边上的每一个o，如果没有，表示所有的o都被包围
2.对于边上的每一个o进行dfs进行扩散，先把边上的每一个o用特殊符号标记，比如*，#等，
3.把和它相邻的o都替换为特殊符号，每一个新的位置都做相同的dfs操作
4.所有扩散结束之后，把特殊符号的位置（和边界连通）还原为o,原来为o的位置（和边界不连通）替换为x即可。
这里一定要注意这里是大'O'和大'X'
*/
class Solution
{
public:
    void Dfs(vector<vector<char>>& area, int row, int col,int sr, int sc ){
        // 当前位置设为'#'
        area[sr][sc] = '#';
        for(int i = 0; i < 4; ++i){
            // 向四个方向扩散
            int newSr = sr + _nextPosition[i][0];
            int newSc = sc + _nextPosition[i][1];
            // 判断新位置是否越界
            if(newSr < 0 || newSr >= row || newSc < 0 || newSc >= col){
                continue;
            }
            // 是'O'说明和边联通，继续搜索是否还有联通的
            if(area[newSr][newSc] == 'O'){
                Dfs(area, row, col, newSr, newSc);
            }
        }
    }
    void surroundingArea(vector<vector<char>>& area){
        if(area.empty()){
            return;
        }
        int row = area.size();
        int col = area[0].size();
        // 寻找边上的每一个o，如果没有，表示所有的o都被包围
        // 寻找第一行和最后一行
        for(int i = 0; i < col; ++i){
            if(area[0][i] == 'O'){
                Dfs(area, row, col, 0, i);
            }
            if(area[row - 1][i] == 'O'){
                Dfs(area, row, col, row - 1, i);
            }
        }
        // 寻找第一列和最后一列
        for(int i = 0; i < row; ++i){
            if(area[i][0] == 'O'){
                Dfs(area, row, col, i, 0);
            }
            if(area[i][col - 1] == 'O'){
                Dfs(area, row, col, i, col - 1);
            }
        }
        // 将被包围的O替换成X
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                if(area[i][j] == 'O'){
                    area[i][j] = 'X';
                }
                else if(area[i][j] == '#'){
                    area[i][j] = 'O';
                }
            }
        }
    }
private:
    // 四个方向的位置更新：顺时针更新
    int _nextPosition[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
};
void print_area(vector<vector<char>>& area){
    for(int i = 0; i < area.size(); ++i){
        for(int j = 0; j < area[0].size(); ++j){
            cout << area[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    vector<vector<char>> area = {{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X'}};
    print_area(area);
    Solution S;
    S.surroundingArea(area);
    print_area(area);
    return 0;
}