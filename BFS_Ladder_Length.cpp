/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-ladder
*/
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;
/*
1.通过BFS, 首先用beginWord带出转换一个字母之后所有可能的结果
2.每一步都要把队列中上一步添加的所有单词转换一遍，最短的转换肯定在这些单词当中， 所有这些词的转换只能算一
次转换，因为都是上一步转换出来的，这里对于每个单词的每个位置都可以用26个字母进行转换，所以一个单词一次转换
的可能有：单词的长度 * 26
3.把转换成功的新词入队，进行下一步的转换
4.最后整个转换的长度就和BFS执行的次数相同
*/
class Solution
{
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList){
        //hash表的查询效率最高
        unordered_set<string> wordDict(wordList.begin(), wordList.end());
        //标记单词是否已经访问过，访问过的不再访问
        unordered_set<string> visited;
        visited.insert(beginWord);
        //初始化队列
        queue<string> q;
        q.push(beginWord);
        int res = 1;
        while(!q.empty()){
            int nextSize = q.size();
            //每一步都要把队列中上一步添加的所有单词转换一遍
            //最短的转换肯定在这些单词当中， 所有这些词的转换只能算一次转换
            //因为都是上一步转换出来的
            while(nextSize--){
                string curWord = q.front();
                q.pop();
                //尝试转换当前单词的每一个位置
                for(int i = 0; i < curWord.size(); ++i){
                    string newWord = curWord;
                    //每一个位置用26个字母分别替换
                    for(char ch = 'a'; ch <= 'z'; ++ch){
                        newWord[i] = ch;
                        //如果列表中没有此单词或者已经访问过（它的转换已经遍历过，无需再次遍历），则跳过
                        if(!wordDict.count(newWord) || visited.count(newWord)){
                            continue;
                        }
                        //转换成功，则在上一步转换的基础上+1
                        if(newWord == endWord){
                            return res + 1;
                        }
                        //还没有转换成功，则新的单词入队
                        visited.insert(newWord);
                        q.push(newWord);
                    }
                }
            }
            res++;
        }
        //转换不成功，返回0
        return 0;
    }
};

int main(){
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    Solution S;
    cout << S.ladderLength(beginWord, endWord, wordList) << endl;

    string beginWord1 = "hit";
    string endWord1 = "cog";
    vector<string> wordList1 = {"hot", "dot", "dog", "lot", "log"};
    cout << S.ladderLength(beginWord1, endWord1, wordList1) << endl;

    return 0;
}
