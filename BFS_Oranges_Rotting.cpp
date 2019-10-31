/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/rotting-oranges
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
/*
本题可以先找到所有的腐烂橘子，入队，用第一批带出新一批腐烂的橘子
每以匹橘子都会在一分钟之内腐烂,所以此题可以转化为求BFS执行的大循环的次数
这里的step的更新需要有一个标记，只有新的腐烂的橘子加入，step才能自加
最后BFS执行完之后，说明所有可以被腐烂的都完成了，再去遍历grid,如何还有
值为1的，说明没有办法完全腐烂，返回-1,如果没有，则返回step
*/
class Solution
{
public:
    int orangesRotting(vector<vector<int>>& grid){
        //用pair存放位置
        queue<pair<int, int>> q;
        int row = grid.size();
        int col = grid[0].size();
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                if(grid[i][j] == 2){
                    q.push(make_pair(i, j));
                }
            }
        }
        int step = 0;
        while(!q.empty()){
            int n = q.size();
            int flag = 0;
            //用当前这一批已经腐烂的橘子带出下一批要腐烂的橘子
            //故要遍历队列中的所有位置
            while(n--){
                auto rot = q.front();
                q.pop();
                //当前位置向四个方向蔓延
                for(int i = 0; i < 4; ++i){
                    int nx = rot.first + _nextPosition[i][0];
                    int ny = rot.second + _nextPosition[i][1];
                    //如果位置越界或者是空格，或者已经是腐烂的位置，则跳过
                    if(nx < 0 || nx >= row || ny < 0 || ny >= col || grid[nx][ny] != 1){
                        continue;
                    }
                    //标记有新的被腐烂
                    flag = 1;
                    grid[nx][ny] = 2;
                    q.push(make_pair(nx, ny));
                }
            }
            //如果有新的腐烂，才++
            if(flag){
                ++step;
            }
        }
        //判断是否还有无法腐烂的
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                if(grid[i][j] == 1){
                    return -1;
                }
            }
        }
        return step;
    }
private:
    //可以蔓延的方向
    int _nextPosition[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
};
void print_vv(vector<vector<int>>& vv){
    cout << endl;
    for(int i = 0; i < vv.size(); ++i){
        for(int j = 0; j < vv[0].size(); ++j){
            cout << vv[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    print_vv(grid);
    Solution S;
    cout << S.orangesRotting(grid) << endl;

    vector<vector<int>> grid1 = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
    print_vv(grid1);
    cout << S.orangesRotting(grid1) << endl;

    vector<vector<int>> grid2 = {{0, 2}};
    print_vv(grid2);
    cout << S.orangesRotting(grid2) << endl;

    return 0;
}