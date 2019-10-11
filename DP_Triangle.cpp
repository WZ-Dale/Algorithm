/*
题目描述：
    给定一个三角矩阵，找出自顶向下的最短路径和，每一步可以移动到下一行的相邻数字。
    比如给定下面一个三角矩阵，自顶向下的最短路径和为11。2 + 3 + 5 + 1 = 11
    [
        [2],
       [3,4],
      [6,5,7],
     [4,1,8,3]
    ]
*/
#include <iostream>
#include <vector>

using namespace std;

/*
方法一：动态规划
    状态：
        子状态：从(0,0)到(1,0),(1,1),(2,0),...(n,n)的最短路径和
        F(i,j): 从(0,0)到(i,j)的最短路径和
    状态递推：
        F(i,j) = min( F(i-1, j-1), F(i-1, j)) + triangle[i][j]
    初始值：
        F(0,0) = triangle[0][0]
    返回结果：
        min(F(n-1, i))
*/
class Solution
{
public:
    int minimumTotal(const vector<vector<int>> &triangle){
        if(triangle.empty()){
            return 0;
        }
        // F[i][j], F[0][0]初始化
        int N = triangle.size();
        vector<vector<int>> F(triangle);// 拷贝构造
        for(int i = 1; i < N; ++i){
            for(int j = 0; j <= i; ++j){
                // 处理左边界和右边界
                if(j == 0){
                    F[i][j] = F[i - 1][j] + F[i][j];
                    continue;
                }
                else if(j == i){
                    F[i][j] = F[i - 1][j - 1] + F[i][j];
                    break;
                }
                // F(i,j) = min( F(i-1, j-1), F(i-1, j)) + triangle[i][j]
                F[i][j] = min(F[i - 1][j - 1], F[i - 1][j]) + F[i][j];
            }
        }
        int result = F[N - 1][0];
        // min(F(n-1, i))
        for(int i = 1; i < N; ++i){
            result = min(result, F[N - 1][i]);
        }
        return result;
    } 
};
/*
方法二：动态规划（反向思维）
    状态：
        子状态：从(n,n),(n,n-1),...(1,0),(1,1),(0,0)到最后一行的最短路径和
        F(i,j): 从(i,j)到最后一行的最短路径和
    状态递推：
        F(i,j) = min( F(i+1, j), F(i+1, j+1)) + triangle[i][j]
    初始值：
        F(n-1,0) = triangle[n-1][0], F(n-1,1) = triangle[n-1][1],..., F(n-1,n-1) = triangle[n-1][n-1]
    返回结果：
        F(0, 0) 
这种逆向思维不需要考虑边界，也不需要最后寻找最小值，直接返回F(0,0)即可
*/
class Solution1
{
public:
    int minimumTotal(const vector<vector<int>> &triangle){
        if(triangle.empty()){
            return 0;
        }
        // F[n-1][n-1],...F[n-1][0]初始化
        int N = triangle.size();
        vector<vector<int>> F(triangle);// 拷贝构造
        // 从倒数第二行开始
        for(int i = N - 2; i >= 0; --i){
            for(int j = 0; j <= i; ++j){
                // F(i,j) = min( F(i+1, j), F(i+1, j+1)) + triangle[i][j]
                F[i][j] = min(F[i + 1][j], F[i + 1][j + 1]) + F [i][j];
            }
        }
        return F[0][0];
    } 
};
/*
注：
    易错点：只保留每一步的最小值，忽略其他路径，造成最终结果错误
            局部最小不等于全局最小
            
    总结：
        遇到关于矩阵、网格、字符串间的比较、匹配的问题，
        单序列(一维)动规解决不了的情况下，就需要考虑双序列(二维)动规。
*/

int main(){
    int N = 4;
    vector<vector<int>> triangle(N);
    triangle[0].push_back(2);
    triangle[1].push_back(3), triangle[1].push_back(4);
    triangle[2].push_back(6), triangle[2].push_back(5), triangle[2].push_back(7);
    triangle[3].push_back(4), triangle[3].push_back(1), triangle[3].push_back(8), triangle[3].push_back(3);
    Solution S;
    cout << S.minimumTotal(triangle) << endl;
    Solution S1;
    cout << S1.minimumTotal(triangle) << endl; 
    return 0;
}
