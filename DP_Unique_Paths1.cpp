/*
题目描述：
    在一个m*n的网格的左上角有一个机器人，机器人在任何时候只能向下或者向右移动，
    机器人试图到达网格的右下角，有多少可能的路径。
    机器人还是要从网格左上角到达右下角，但是网格中添加了障碍物，障碍物用1表示
*/
#include <iostream>
#include <vector>

using namespace std;
/*
方法：动态规划
    状态：
        子状态：从(0,0)到达(1,0),(1,1),(2,1),...(m-1,n-1)的路径数
        F(i,j): 从(0,0)到达F(i,j)的路径数
    状态递推：
        F(i,j) = {F(i-1,j) + F(i,j-1)} OR {0, if obstacleGrid(i,j) = 1} 
    初始化：
        特殊情况：第0行和第0列
        F(0,i) = {1} OR {0, if obstacleGrid(0,j) = 1, j <= i}
        F(i,0) = {1} OR {0, if obstacleGrid(j,0) = 1, j <= i}
    返回结果：
        F(m-1,n-1)
*/
class Solution
{
public:
    int uniquePaths1(const vector<vector<int>> &arr){
        if(arr.empty() || arr[0].empty()){
            return 0;
        }
        const int m = arr.size();
        const int n = arr[0].size();
        // 申请F(i,j)空间，初始值为0
        vector<vector<int>> F(m, vector<int>(n, 0));
        for(int i = 0; i < m; ++i){
            if(arr[i][0] == 1){// 第0列中只要前面有障碍，下面都无法到达
                break;
            }
            F[i][0] = 1;
        }
        for(int j = 0; j < n; ++j){
            if(arr[0][j] == 1){// 第0行中只要前面有障碍，后面都无法到达
                break;
            }
            F[0][j] = 1;
        }
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                if(arr[i][j] == 1){// 如果有障碍物，则将该位置的方法数填为0
                    F[i][j] = 0;
                }
                else{
                    // F(i, j) = F(i, j - 1) + F(i - 1, j)
                    F[i][j] = F[i][j - 1] + F[i - 1][j];
                }
            }
        }
        return F[m - 1][n - 1];
    }
};

int main(){
    vector<vector<int>> arr(3, vector<int>(3, 0));
    arr[1][1] = 1;
    Solution S;
    cout << S.uniquePaths1(arr) << endl;
    return 0;
}
