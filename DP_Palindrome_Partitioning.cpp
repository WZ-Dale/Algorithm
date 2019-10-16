/*
回文串：正读和反读都一样的字符串，比如noon，level，字符串左右对称
题目描述：
    给定一个字符串 s, 把 s 分割成一系列的子串，分割的每一个子串都为回文串
    返回最小的分割次数
    比如，给定 s = "aab",
    返回1，因为一次cut就可以产生回文分割["aa","b"]
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
/*
方法：动态规划
    状态：
        子状态：到第1,2,3,...,n个字符需要的最小分割数
        F(i): 到第i个字符需要的最小分割数
    状态递推：
        F(i) = min{F(i), 1 + F(j)}, where j<i && j+1到i是回文串
        上式表示如果从j+1到i判断为回文字符串，且已经知道从第1个字符到第j个字符的最小切割数
        那么只需要再切一次，就可以保证 1-->j, j+1-->i 都为回文串。
    初始化：
        F(i) = i - 1
        上式表示到第i个字符需要的最大分割数, 比如单个字符只需要切0次，因为单子符都为回文串
        2个字符最大需要1次，3个2次......
    返回结果：
        F(n)
    遗留问题：如何判断一段字符串为回文串
        循环判断首尾元素是否相同，如果全部相同，则是回文串
*/
class Solution
{
public:
    //判断是否回文串
    bool isPalindrome(const string &str){
        string str1(str);
        reverse(str1.begin(), str1.end());
        if (str1 == str){
            return true;
        }
        return false;
    }
    int minCut(const string &str){
        if (str.empty()){
            return 0;
        }
        int len = str.size();
        vector<int> F;
        // F(i)初始化
        // F(0）= -1，必要项，如果没有这一项，对于重叠字符串“aaaaa”会产生错误的结果
        for (int i = 0; i < len + 1; ++i){
            F.push_back(i - 1);
        }
        for (int i = 1; i < len + 1; ++i){
            for (int j = 0; j < i; ++j){
                // F(i) = min{F(i), 1 + F(j)}, where j<i && j+1到i是回文串
                // 从最长串判断，如果从第j+1到i为回文字符串
                // 则再加一次分割，从1到j，j+1到i的字符就全部分成了回文字符串
                if (isPalindrome(str.substr(j, i - j))){
                    F[i] = min(F[j] + 1, F[i]);
                }
            }
        }
        return F[len];
    }
};
/*
上述方法两次循环时间复杂度是O(n^2),
判断回文串时间复杂度是O(n),
所以总时间复杂度为O(n^3)
对于过长的字符串，在OJ的时候会出现TLE(Time Limit Exceeded)
判断回文串的方法可以继续优化，使总体时间复杂度降为O(n^2)
判断回文串，这是一个“是不是”的问题，所以也可以用动态规划来实现
判断回文串：动态规划
    状态：
        子状态：从第一个字符到第二个字符是不是回文串，第1-3，第2-5，...
        F(i,j): 字符区间 [i,j] 是否为回文串
    状态递推：
        F(i,j): true->{s[i]==s[j] && F(i+1,j-1)} OR false
        上式表示如果字符区间首尾字符相同且在去掉区间首尾字符后字符区间仍为回文串，
        则原字符区间为回文串
        从递推公式中可以看到第i处需要用到第i+1处的信息，所以i应该从字符串末尾遍历
    初始化：
        F(i,j) = false
    返回结果：
        矩阵F(n,n), 只更新一半值（i <= j），n^2 / 2
*/
class Solution1
{
public:
    //判断是否回文串
    vector<vector<bool>> getMat(string s){
        int len = s.size();
        vector<vector<bool>> mat = vector<vector<bool>> (len, vector<bool>(len, false));
        for (int i = len - 1; i >= 0; --i){
            for (int j = i; j < len; ++j){
                if (j == i){
                    // 单字符为回文字符串
                    mat[i][j] = true;
                }
                else if (j == i + 1){
                    // 相邻字符如果相同，则为回文字符串
                    mat[i][j] = (s[i] == s[j]);
                }
                else{
                    // F(i,j) = {s[i]==s[j] && F(i+1,j-1)
                    // j > i+1
                    mat[i][j] = ((s[i] == s[j]) && mat[i + 1][j - 1]);
                }
            }
        }
        return mat;
    }
    int minCut(const string &str){
        if (str.empty()){
            return 0;
        }
        int len = str.size();
        vector<int> F;
        // F(i)初始化
        // F(0）= -1，必要项，如果没有这一项，对于重叠字符串“aaaaa”会产生错误的结果
        for (int i = 0; i < len + 1; ++i){
            F.push_back(i - 1);
        }
        vector<vector<bool>> mat = getMat(str);
        for (int i = 1; i < len + 1; ++i){
            for (int j = 0; j < i; ++j){
                // F(i) = min{F(i), 1 + F(j)}, where j<i && j+1到i是回文串
                // 从最长串判断，如果从第j+1到i为回文字符串
                // 则再加一次分割，从1到j，j+1到i的字符就全部分成了回文字符串
                if (mat[j][i - 1]){
                    F[i] = min(F[j] + 1, F[i]);
                }
            }
        }
        return F[len];
    }
};
/*
上述方法判断回文串时间复杂度O(n^2)
主方法两次循环时间复杂度O(n^2)
总体时间复杂度O(n^2) ~ O(2 * n^2) = O(n^2) + O(n^2)
总结：
    简单的动态规划问题，状态，状态递推和状态初始化都比较直观
    对于复杂的动态规划问题，状态，状态递推和状态初始化都比较隐含，需要仔细推敲
    尤其是状态递推可能需要额外的辅助判断条件才能达成。
*/

int main()
{
    string str("aaaaaaa");
    Solution S;
    cout << S.minCut(str) << endl;
    Solution S1;
    cout << S1.minCut(str) << endl;
    return 0;
}
