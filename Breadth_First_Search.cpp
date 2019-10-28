/*
广度优先搜索（Breadth First Search) ------ 一石激起千层浪

迷宫问题
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct node
{
    int x;
    int y;
};

//queue实现
bool Bfs(vector<vector<int>>& graph, int startx, int starty, int endx, int endy)
{
    //迷宫的大小
    int m = graph.size();
    int n = graph[0].size();
    //标记迷宫中的位置是否被走过
    vector<vector<int>> book(m, vector<int>(n, 0));
    //存储迷宫中的位置
    queue<node> q;
    node xy = {startx, starty};
    q.push(xy);
    //标记已经走过
    book[startx][starty] = 1;
    //四个行走的方向，右下左上
    int _nextPosition[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    //标记是否可以出去
    bool flag = false;
    while(!q.empty()){
        //当前位置带出所有新的位置，右下左上
        for (size_t i = 0; i < 4; ++i){
            //计算新的位置
            int newx = q.front().x + _nextPosition[i][0];
            int newy = q.front().y + _nextPosition[i][1];
            //如果新的位置越界，继续下一个
            if(newx < 0 || newx >= m || newy < 0 || newy >= n){
                continue;
            }
            //如果新的位置无障碍并且之前也没走过，保存新的位置
            if(graph[newx][newy] == 0 && book[newx][newy] == 0){
                node newxy = {newx, newy};
                q.push(newxy);
                //标记已被走过
                book[newx][newy] = 1;
            }
            //如果新的位置为目标位置,则结束查找
            if(newx == endx && newy == endy){
                flag = true;
                break;
            }
        }
        if(flag){
            break;
        }
        //否则，用新的位置继续向后走
        q.pop();
    }
    return flag;
}

//vector实现
bool Bfs1(vector<vector<int>>& graph, int startx, int starty, int endx, int endy)
{
    //迷宫的大小
    int m = graph.size();
    int n = graph[0].size();
    //标记迷宫中的位置是否被走过
    vector<vector<int>> book(m, vector<int>(n, 0));
    //存储迷宫中的位置
    vector<node> arr(m * n);

    int head = 0, tail = 1;
    arr[head].x = startx;
    arr[head].y = starty;

    //标记已经走过
    book[startx][starty] = 1;
    //四个行走的方向，右下左上
    int _nextPosition[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    //标记是否可以出去
    bool flag = false;
    while(head < tail){
        //当前位置带出所有新的位置，右下左上
        for (size_t i = 0; i < 4; ++i){
            //计算新的位置
            int newx = arr[head].x + _nextPosition[i][0];
            int newy = arr[head].y + _nextPosition[i][1];
            //如果新的位置越界，继续下一个
            if(newx < 0 || newx >= m || newy < 0 || newy >= n){
                continue;
            }
            //如果新的位置无障碍并且之前也没走过，保存新的位置
            if(graph[newx][newy] == 0 && book[newx][newy] == 0){
                arr[tail].x = newx;
                arr[tail].y = newy;
                //标记已被走过
                book[newx][newy] = 1;
                ++tail;
            }
            //如果新的位置为目标位置,则结束查找
            if(newx == endx && newy == endy){
                flag = true;
                break;
            }
        }
        if(flag){
            break;
        }
        //否则，用新的位置继续向后走
        ++head;
    }
    return flag;
}
/*
总结：广度优先搜索模型
    Bfs()
    {
       1. 建立起始步骤，队列初始化
       2. 遍历队列中的每一种可能，whlie(队列不为空)
      {
           通过队头元素带出下一步的所有可能，并且依次入队
          {
               判断当前情况是否达成目标：按照目标要求处理逻辑
          }
           继续遍历队列中的剩余情况
           
      }
    }
*/

int main(){
    int sx = 0, sy = 0;
    int ex = 7, ey = 9;
    vector<vector<int>> graph ={{0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
                                {0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
                                {0, 1, 1, 0, 1, 1, 0, 0, 1, 0},
                                {0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
                                {0, 1, 0, 0, 0, 1, 1, 1, 0, 1},
                                {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
                                {0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
                                {0, 1, 0, 0, 1, 1, 0, 1, 0, 0},
                                {1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
                                {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},};
    cout << "是否可以走出迷宫： " << Bfs(graph, sx, sy, ex, ey) << endl;
    cout << "是否可以走出迷宫： " << Bfs1(graph, sx, sy, ex, ey) << endl;
    return 0; 
}