/*
深度优先搜索（Depth First Search）------ 一条道走到黑

n个盒子放n张牌的方法总数
*/
#include <iostream>
#include <vector>

using namespace std;

void Dfs(int index, int n, vector<int> &boxs, vector<int> &book)
{
    if (index == n + 1){
        for (int i = 1; i <= n; ++i){
            cout << boxs[i] << " ";
        }
        cout << endl;
        return; //向上回退
    }
    for (int i = 1; i <= n; ++i){
        if (book[i] == 0){//第i号牌仍在手上
            boxs[index] = i;
            book[i] = 1;
            //现在第i号牌已经被用了
            //处理下一个盒子
            Dfs(index + 1, n, boxs, book);
            //从下一个盒子回退到当前盒子，取出当前盒子的牌，
            //尝试放入其它牌。
            book[i] = 0;
        }
    }
}
/*
总结：深度优先搜索模型
    Dfs(当前这一步的处理逻辑) {
        1. 判断边界，是否已经一条道走到黑了：向上回退
        2. 尝试当下的每一种可能
        3. 确定一种可能之后，继续下一步 Dfs(下一步) 
    }
*/

int main(){
    int n;
    cin >> n;
    vector<int> boxs(n + 1, 0);
    vector<int> books(n + 1, 0);
    Dfs(1, n, boxs, books);
    return 0;
}