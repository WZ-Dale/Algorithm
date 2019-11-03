/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/open-the-lock
*/
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;
/*
深度优先不适合解此题，递归深度太大，会导致栈溢出
本题的密码为4位密码，每位密码可以通过拨动一次进行改变，注意这里的数的回环以及拨动的方向
拨动方向：向前，向后
回环：如果当前是9，0时，向前，向后拨动需要变成最小最大，而不是简单的自加自减
*/
class Solution
{
public:
    int openLock(vector<string>& deadends, string target){
        //hash表的查询效率最高
        unordered_set<string> deadendsSet(deadends.begin(), deadends.end());
        //如果"0000"在死亡字符串中，则永远到达不了
        if(deadendsSet.count("0000")){
            return -1;
        }
        //加标记，已经搜索过的字符串不需要再次搜索
        unordered_set<string> book;
        book.insert("0000");
        //初始化队列
        queue<string> q;
        q.push("0000");
        int step = 0;
        while(!q.empty()){
            int n = q.size();
            //从上一步转换之后的字符串都需要进行验证和转换
            //并且只算做一次转换，类似于层序遍历，转换的步数和层相同
            //同一层的元素都是经过一步转换得到的
            for(int i = 0; i < n; ++i){
                string curStr = q.front();
                q.pop();
                if (curStr == target){
                    return step;
                }
                //四位密码锁，每个位置每次都可以转一次
                for(int j = 0; j < 4; ++j){
                    string newStr1 = curStr, newStr2 = curStr;
                    //当前位置可以向前或者向后拨一位
                    newStr1[j] = newStr1[j] == '9' ? '0' : newStr1[j] + 1;
                    newStr2[j] = newStr2[j] == '0' ? '9' : newStr2[j] - 1;
                    //count看在不在集合内，find查找位置，此处用两者均可
                    //if(deadendsSet.find(newStr1) == deadendsSet.end() && book.find(newStr1) == book.end()){
                    if(deadendsSet.count(newStr1) == 0 && book.count(newStr1) == 0){
                        q.push(newStr1);
                        book.insert(newStr1);
                    }
                    if(deadendsSet.find(newStr2) == deadendsSet.end() && book.find(newStr2) == book.end()){
                        q.push(newStr2);
                        book.insert(newStr2);
                    }
                }
            }
            ++step;
        }
        return -1;
    }
};

int main(){
    vector<string> deadends = {"0201", "0101", "0102", "1212", "2002"};
    string target = "0202";
    Solution S;
    cout << S.openLock(deadends, target) << endl;

    vector<string> deadends1 = {"8888"};
    string target1 = "0009";
    cout << S.openLock(deadends1, target1) << endl;

    vector<string> deadends2 = {"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"};
    string target2 = "8888";
    cout << S.openLock(deadends2, target2) << endl;

    vector<string> deadends3 = {"0000"};
    string target3 = "8888";
    cout << S.openLock(deadends3, target3) << endl;

    return 0;
}