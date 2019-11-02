/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-genetic-mutation
*/
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    int minMutation(string startGene, string endGene, vector<string>& bank){
        //hash表的查询效率最高
        unordered_set<string> wordDict(bank.begin(), bank.end());
        //标记基因是否已经访问过，访问过的不再访问
        unordered_set<string> visited;
        visited.insert(startGene);
        //初始化队列
        queue<string> q;
        q.push(startGene);
        int res = 0;
        while(!q.empty()){
            int nextSize = q.size();
            //每一步都要把队列中上一步添加的所有基因变化一遍
            //最短的变化肯定在这些基因当中， 所有这些词的变化只能算一次变化
            //因为都是上一步变化出来的
            while(nextSize--){
                string curWord = q.front();
                q.pop();
                //尝试变化当前基因的每一个位置
                for(int i = 0; i < curWord.size(); ++i){
                    string newWord = curWord;
                    //每一个位置用26个字母分别替换
                    for(char ch = 'A'; ch <= 'Z'; ++ch){
                        newWord[i] = ch;
                        //如果列表中没有此基因或者已经访问过（它的变化已经遍历过，无需再次遍历），则跳过
                        if(!wordDict.count(newWord) || visited.count(newWord)){
                            continue;
                        }
                        //变化成功，则在上一步变化的基础上+1
                        if(newWord == endGene){
                            return res + 1;
                        }
                        //还没有变化成功，则新的基因入队
                        visited.insert(newWord);
                        q.push(newWord);
                    }
                }
            }
            res++;
        }
        //变化不成功，返回-1
        return -1;
    }
};

int main(){
    string startGene = "AACCGGTT";
    string endGene = "AACCGGTA";
    vector<string> bank = {"AACCGGTA"};
    Solution S;
    cout << S.minMutation(startGene, endGene, bank) << endl;

    string startGene1 = "AACCGGTT";
    string endGene1 = "AAACGGTA";
    vector<string> bank1 = {"AACCGGTA", "AACCGCTA", "AAACGGTA"};
    cout << S.minMutation(startGene1, endGene1, bank1) << endl;

    string startGene2 = "AAAAACCC";
    string endGene2 = "AACCCCCC";
    vector<string> bank2 = {"AAAACCCC", "AAACCCCC", "AACCCCCC"};
    cout << S.minMutation(startGene2, endGene2, bank2) << endl;

    return 0;
}
