/*
给定一个字符串和一个词典dict，确定s是否可以根据词典中的词分成一个或多个单词。
比如，给定 s = "leetcode", dict = ["leet", "code"]
返回true，因为"leetcode"可以被分成"leet code"
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

/*
方法：动态规划
    状态：
        子状态：前1，2，3，...,n个字符能否根据词典中的词被成功分词
        F(i): 前i个字符能否根据词典中的词被成功分词
    状态递推：
        F(i): true{j<i && F(j) && substr[j+1,i]能在词典中找到} OR false
        在j小于i中，只要能找到一个F(j)为true，并且从j+1到i之间的字符能在词典中找到，则F(i)为true
    初始值：
        对于初始值无法确定的，可以引入一个不代表实际意义的空状态，作为状态的起始
        空状态的值需要保证状态递推可以正确且顺利的进行，到底取什么值可以通过简单的例子进行验证
        F(0) = true
    返回结果：F(n)
*/
class Solution
{
public:
    bool WordBreak(string str, unordered_set<string> &dict){
        if(str.empty() || dict.empty()){
            return false;
        }
        // 获取词典中的单词的最大长度
        int max_length = 0;
        for(auto it = dict.begin(); it != dict.end(); ++it){
            max_length = max_length > (*it).size() ? max_length : (*it).size();
        }
        // F(i): 前i个字符能否根据词典中的词被成功分词
        vector<bool> F(str.size() + 1, false);
        // 初始化F(0) = true
        F[0] = true;
        for(int i = 1; i <= str.size(); ++i){
            for(int j = i - 1; j >= 0; --j ){
                // 如果最小子串长度大于max_length，则跳过
                if((i - j) > max_length){
                    break;
                }
                // F(i): true{j <i && F(j) && substr[j+1,i]能在词典中找到} OR false
                // 第j+1个字符的索引为j
                if(F[j] && dict.find(str.substr(j, i - j)) != dict.end()){
                    F[i] = true;
                    break;
                }
            }
        }
        return F[str.size()];
    }
};

int main()
{
    string str("iamachinesepeople");
    unordered_set<string> dict= {"men", "i", "am", "women", "a", "china", "chinese", "man", "people"};
    Solution s;
    cout << s.WordBreak(str, dict) << endl;
    return 0;
}