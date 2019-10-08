/*
题目描述：
    给定两个单词word1和word2，找到最小的修改步数，把word1转换成word2
    每一个操作记为一步
    允许在一个word上进行如下3种操作：
    a) 插入一个字符
    b) 删除一个字符
    c) 替换一个字符
编辑距离（Edit Distance）：是指两个字串之间，由一个转成另一个所需的最少编辑操作次数。
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;
/* 
方法：动态规划
    状态：
        子状态：word1的前1，2，3，...m个字符转换成word2的前1，2，3，...n个字符需要的编辑距离
        F(i,j):word1的前i个字符于word2的前j个字符的编辑距离
    状态递推：
        F(i,j) = min { F(i-1,j）+1, F(i,j-1) +1, F(i-1,j-1) +(w1[i]==w2[j]?0:1) } 
        上式表示从删除，增加和替换操作中选择一个最小操作数
        F(i-1,j): w1[1,...,i-1]于w2[1,...,j]的编辑距离，删除w1[i]的字符--->F(i,j)
        F(i,j-1): w1[1,...,i]于w2[1,...,j-1]的编辑距离，增加一个字符--->F(i,j)
        F(i-1,j-1): w1[1,...,i-1]于w2[1,...,j-1]的编辑距离，如果w1[i]与w2[j]相同，
        不做任何操作，编辑距离不变，如果w1[i]与w2[j]不同，替换w1[i]的字符为w2[j]--->F(i,j)
    初始化：
        初始化一定要是确定的值，如果这里不加入空串，初始值无法确定
        F(i,0) = i :word与空串的编辑距离，删除操作
        F(0,i) = i :空串与word的编辑距离，增加操作
    返回结果：F(m,n)
注：字符串类的动态规划，可引入空串进行初始化
*/
class Solution
{
public:
    int editDistance(string s, string s1){
        if(s.empty() && s1.empty()){
            return 0;
        }
        else if(s.empty()){
            return s1.size();
        }
        else if(s1.empty()){
            return s.size();
        }
        const int m = s.size() + 1;
        const int n = s1.size() + 1;
        vector<vector<int>> F(m, vector<int>(n, 0));
        for(int i = 0; i < m; ++i){
            F[i][0] = i;
        }
        for(int j = 0; j < n; ++j){
            F[0][j] = j;
        }
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                // F(i,j) = min { F(i-1,j）+1, F(i,j-1) +1, F(i-1,j-1) +(w1[i]==w2[j]?0:1) } 
                // 判断word1的第i个字符是否与word2的第j个字符相等
                if (s[i - 1] == s1[j - 1]) {
                    F[i][j] = 1 + min(F[i][j - 1], F[i - 1][j]);
                    // 字符相等，F(i-1,j-1)编辑距离不变
                    F[i][j] = min(F[i][j], F[i - 1][j - 1]);
                }
                else {
                    F[i][j] = 1 + min(F[i][j - 1], F[i - 1][j]);
                    // 字符不相等，F(i-1,j-1)编辑距离 + 1
                    F[i][j] = min(F[i][j], 1 + F[i - 1][j - 1]);
                }
            }
        }
        return F[m - 1][n - 1];
    }
};
// 简化版：
class Solution1
{
public:
    int editDistance(string s, string s1){
        if(s.empty() || s1.empty()){
            return max(s.size(), s1.size());
        }
        const int m = s.size() + 1;
        const int n = s1.size() + 1;
        vector<vector<int>> F(m, vector<int>(n, 0));
        for(int i = 0; i < m; ++i){
            F[i][0] = i;
        }
        for(int j = 0; j < n; ++j){
            F[0][j] = j;
        }
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                // F(i,j) = min { F(i-1,j）+1, F(i,j-1) +1, F(i-1,j-1) +(w1[i]==w2[j]?0:1) } 
                F[i][j] = min(min(F[i - 1][j] + 1, F[i][j - 1] + 1), F[i - 1][j - 1] + (s[i - 1] == s1[j - 1] ? 0 : 1));
            }
        }
        return F[m - 1][n - 1];
    }
};

int main(){
    Solution S;
    cout << S.editDistance("edit", "distance") << endl;
    Solution S1;
    cout << S1.editDistance("edit", "distance") << endl;
    return 0;
}