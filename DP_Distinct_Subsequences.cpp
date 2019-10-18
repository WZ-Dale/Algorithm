/*
题目描述：
    给定两个字符串S和T，求S有多少个不同的子串与T相同。
    S的子串定义为在S中任意去掉0个或者多个字符形成的串。
    子串可以不连续，但是相对位置不能变。
    比如“ACE”是“ABCDE”的子串，但是“AEC”不是。
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;
/*
问题翻译：S有多少个不同的子串与T相同
    S[1:m]中的子串与T[1:n]相同的个数
    由S的前m个字符组成的子串与T的前n个字符相同的个数
方法：动态规划
    状态：
        子状态：由S的前1,2,...,m个字符组成的子串与T的前1,2,...,n个字符相同的个数
        F(i,j): S[1:i]中的子串与T[1:j]相同的个数
    状态递推：
        在F(i,j)处需要考虑S[i] = T[j] 和 S[i] != T[j]两种情况
            当S[i] = T[j]:
                1>: 让S[i]匹配T[j]，则
                    F(i,j) = F(i-1,j-1)
                2>: 让S[i]不匹配T[j],则问题就变为S[1:i-1]中的子串与T[1:j]相同的个数，则
                    F(i,j) = F(i-1,j)
                故，S[i] = T[j]时，F(i,j) = F(i-1,j-1) + F(i-1,j)
            当S[i] != T[j]:
                问题退化为S[1:i-1]中的子串与T[1:j]相同的个数
                故，S[i] != T[j]时，F(i,j) = F(i-1,j)
    初始化：引入空串进行初始化
        F(i,0) = 1 ---> S的子串与空串相同的个数，只有空串与空串相同
    返回结果：F(m,n)
*/
class Solution
{
public:
    int distinctSubsequences(string s, string t){
        if(s.size() < t.size()){    // S的长度小于T长度，不可能含有与T相同的子串
            return 0;
        }
        else if(t.empty()){         // T为空串，只有空串与空串相同，S至少有一个子串，它为空串
            return 1;
        }
        const int m = s.size() + 1;
        const int n = t.size() + 1;
        vector<vector<int>> F(m, vector<int>(n, 0));
        // F(i,0)初始化
        for(int i = 0; i < m; ++i){
            F[i][0] = 1;
        }
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                if(s[i -1] == t[j - 1]){    // S的第i个字符与T的第j个字符相同
                    F[i][j] = F[i - 1][j - 1] + F[i- 1][j];
                }
                else{
                    // S的第i个字符与T的第j个字符不相同
                    // 从S的前i-1个字符中找子串，使子串与T的前j个字符相同
                    F[i][j] = F[i - 1][j];
                }
            }
        }
        return F[m - 1][n - 1];
    }
};

int main(){
    Solution S;
    cout << S.distinctSubsequences("ababcac", "abc") << endl;
    return 0;
}