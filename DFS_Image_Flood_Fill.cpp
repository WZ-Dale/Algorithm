/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/flood-fill

有一幅以二维整数数组表示的图画，每一个整数表示该图画的像素值大小，数值在 0 到 65535 之间。
给你一个坐标 (sr, sc) 表示图像渲染开始的像素值（行 ，列）和一个新的颜色值 newColor，让你重新上色这幅图像。
为了完成上色工作，从初始坐标开始，记录初始坐标的上下左右四个方向上像素值与初始坐标相同的相连像素点。
接着再记录这四个方向上符合条件的像素点与他们对应四个方向上像素值与初始坐标相同的相连像素点，……，重复该过程。
将所有有记录的像素点的颜色值改为新的颜色值。
最后返回经过上色渲染后的图像。

示例:
    输入: 
        image = [[1,1,1],[1,1,0],[1,0,1]]
        sr = 1, sc = 1, newColor = 2
    输出: 
        [[2,2,2],[2,2,0],[2,0,1]]
    解析: 
        在图像的正中间，(坐标(sr,sc)=(1,1)),
        在路径上所有符合条件的像素点的颜色都被更改成2。
        注意，右下角的像素没有更改为2，
        因为它不是在上下左右四个方向上与初始点相连的像素点。
注意:
    image 和 image[0] 的长度在范围 [1, 50] 内。
    给出的初始点将满足 0 <= sr < image.length 和 0 <= sc < image[0].length。
    image[i][j] 和 newColor 表示的颜色值在范围 [0, 65535]内。
*/
#include <iostream>
#include <vector>

using namespace std;
/*
把和初始坐标开始，颜色值相同的点的颜色全部改为新的颜色，并且只要某个点颜色被更改，则继续以此点向周围渲染
比如题目的意思: 以位置（1，1）开始，向外渲染，只要渲染点的颜色值和（1，1）位置的颜色值相同，则继续向外渲染
    1 1 1
    1 1 0
    1 0 1

    2 2 2
    2 2 0
    2 0 1
这里每一个符合要求的点都要向四个方向渲染
边界：位置是否越界
这里需要用的标记，避免重复修改，使时间复杂度不超过O(row * col)
*/
class Solution
{
public:
    void Dfs(vector<vector<int>>& image, int row, int col, vector<vector<int>>& book, int sr, int sc, int oldColor, int newColor){
        // 处理当前逻辑，修改颜色，并且标记已经修改过了
        image[sr][sc] = newColor;
        book[sr][sc] = 1;
        // 遍历每一种可能，四个方向
        for(int i = 0; i < 4; ++i){
            int newSr = sr + _nextPosition[i][0];
            int newSc = sc + _nextPosition[i][1];
            // 判断新位置是否越界
            if(newSr < 0 || newSr >= row || newSc < 0 || newSc >= col){
                continue;
            }
            // 如果颜色符合要求，并且之前也没有渲染过，则继续渲染
            if(image[newSr][newSc] == oldColor && book[newSr][newSc] == 0){
                Dfs(image, row, col, book, newSr, newSc, oldColor, newColor);
            }
        }
    }    
    void floodFill(vector<vector<int>>& image, int sr, int sc, int newColor){
        if(image.empty()){
            return;
        }
        int row = image.size();
        int col = image[0].size();
        // 建立标记
        vector<vector<int>> book(row, vector<int>(col, 0));
        // 获取旧的颜色
        int oldColor = image[sr][sc];
        Dfs(image, row, col, book, sr, sc, oldColor, newColor);
    }
private:
    // 四个方向的位置更新：顺时针更新
    int _nextPosition[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
};
void print_image(vector<vector<int>>& image){
    for(int i = 0; i < image.size(); ++i){
        for(int j = 0; j < image[0].size(); ++j){
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    vector<vector<int>> image = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    print_image(image);
    Solution S;
    S.floodFill(image, 1, 1, 2);
    print_image(image);    
    return 0;
}