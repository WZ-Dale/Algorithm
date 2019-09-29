/*
题目描述：
    给定一个m*n的网格，网格用非负数填充，找到一条从左上角到右下角的最短路径。
    注：每次只能向下或者向右移动。
*/
#include <iostream>
#include <vector>

using namespace std;
/*
方法：动态规划
    状态：
        子状态：从(0,0)到达(1,0),(1,1),(2,1),...(m-1,n-1)的最短路径
        F(i,j): 从(0,0)到达F(i,j)的最短路径
    状态递推：
        F(i,j) = min{F(i-1,j) , F(i,j-1)} + (i,j)
    初始化：
        F(0,0) = (0,0)
        特殊情况：第0行和第0列
        F(0,i) = F(0,i-1) + (0,i)
        F(i,0) = F(i-1,0) + (i,0)
    返回结果：
        F(m-1,n-1)
*/
class Solution
{
public:
    int minimumPathSum(const vector<vector<int>> &arr){
        // 如果为空或者只有一行，返回0
        if(arr.empty() || arr[0].empty()){
            return 0;
        }
        // 获取行和列大小，并申请F(i,j)空间
        const int m = arr.size();
        const int n = arr[0].size();
        vector<vector<int>> F(m, vector<int>(n, 0));
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(i == 0 && j == 0){
                    F[0][0] = arr[0][0]; 
                }
                else if(i == 0){
                    F[0][j] = F[0][j - 1] + arr[0][j];// 因为是求和，所以不要忘记加上当前位置的值
                }
                else if(j == 0){
                    F[i][0] = F[i - 1][0] + arr[i][0];// 因为是求和，所以不要忘记加上当前位置的值
                }
                else{
                    F[i][j] = min(F[i][j - 1], F[i - 1][j]) + arr[i][j];// 因为是求和，所以不要忘记加上当前位置的值
                }
            }
        }
        return F[m - 1][n - 1];
    }
};
// 以上解法简洁，但容易出错
// 在解决复杂问题是，同时考虑多种情况，逻辑容易混乱。
// 因此，分解思考每一种情况，逻辑简明，不易出错。
class Solution1
{
public:
    int minimumPathSum(const vector<vector<int>> &arr){
        // 如果为空或者只有一行，返回0
        if(arr.empty() || arr[0].empty()){
            return 0;
        }
        // 获取行和列大小，并申请F(i,j)空间
        const int m = arr.size();
        const int n = arr[0].size();
        vector<vector<int>> F(m, vector<int>(n, 0));
        // F(0,0)初始化
        F[0][0] = arr[0][0];
        // 初始化第一列
        for(int i = 1; i < m; ++i){
            F[i][0] = F[i - 1][0] + arr[i][0];
        }
        // 初始化第一行
        for(int j = 1; j < n; ++j){
            F[0][j] = F[0][j - 1] + arr[0][j];
        }
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                // F(i,j) = min{F(i-1,j) , F(i,j-1)} + (i,j)
                F[i][j] = min(F[i][j - 1], F[i - 1][j]) + arr[i][j];
            }
        }
        return F[m - 1][n - 1];
    }
};
int main(){
    vector<vector<int>> arr = {{2, 1, 9}, {5, 3, 6}, {7, 8, 4}};
    Solution S;
    cout << S.minimumPathSum(arr) << endl;
    Solution1 S1;
    cout << S1.minimumPathSum(arr) << endl;
    return 0;
}