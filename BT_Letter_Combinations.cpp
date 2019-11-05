/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;
/*
此题DFS + 回溯
*/
class Solution
{
public:
    void backTrace(string& digits, vector<string>& ret, string curStr, int curDepth){
        //边界，找到一种组合，放入数组中，结束此路径，向上回溯
        if(curDepth == digits.size()){
            if(!curStr.empty()){
                ret.push_back(curStr);
            }
            return;
        }
        //找到当前字符在string映射表中的位置
        int curMapIndex = digits[curDepth] - '0';
        string curMap = mapString[curMapIndex];
        //遍历每一种可能的组合
        for(auto& ch : curMap){
            backTrace(digits, ret, curStr + ch, curDepth + 1);
        }
    }
    vector<string> letterCombinations(string& digits){
        vector<string> ret;
        backTrace(digits, ret, "", 0);
        return ret;
    }
private:
    string mapString[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
};
void print_v(vector<string>& v){
    for(auto& e : v){
        cout << e << ", ";
    }
    cout << endl;

    //以下是不打印最后一个逗号的两种写法

    // int n = v.size();
    // for(int i = 0; i < n; ++i){
    //     if(i == n - 1){
    //         cout << v[i];
    //         break;
    //     }
    //     cout << v[i] << ", ";
    // }
    // cout << endl;

    // for(int i = 0; i < n - 1; ++i){
    //     cout << v[i] << ", ";
    // }
    // cout << v[n - 1] << endl;
}

int main(){
    string digits = "23";
    Solution S;
    vector<string> v = S.letterCombinations(digits);
    print_v(v);
    return 0;
}