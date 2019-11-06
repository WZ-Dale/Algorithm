/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-watch
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    void backTrace(int num, vector<string>& ret, string h, string m, int curDepth){
        //边界，找到一种组合，判定是否合法，放入数组中，结束此路径，向上回溯
        if(curDepth == num){
            if(h.empty()){
                h = "0";
            }
            if(m.empty()){
                m = "00";
            }
            if(atoi(h.c_str()) > 11 || atoi(m.c_str()) > 59){
                return;
            }
            ret.push_back(h+":"+m);
            return;
        }       
        //遍历每一种可能的组合
        
    }
    vector<string> readBinaryWatch(int num){
        vector<string> ret;
        backTrace(num, ret, "", "", 0);
        return ret;
    }
private:
    vector<vector<int>> watch = {{1, 2, 4, 8}, {1, 2, 4, 8, 16, 32}};
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
    int num = 1;
    Solution S;
    vector<string> v = S.readBinaryWatch(num);
    print_v(v);
    return 0;
}