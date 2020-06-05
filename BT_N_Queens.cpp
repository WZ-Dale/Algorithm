/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens/
*/

/*
N皇后问题：把N个皇后放值N*N的二维矩阵中，保证他们相互不能攻击： 即不在同一行，同一列，同一个斜线上(撇捺)
思想：DFS + 回溯
从第一行开始放置皇后，每确定一个位置，判断是否会冲突： 是否在同一列，撇，捺， 不可能在同一行，
同一列：纵坐标相同
“撇”，对应的位置，横坐标加上纵坐标的值是相同的。
“捺”，对应的位置，横坐标减去纵坐标的值也是相同的。
当前行位置确定之后， 继续确定下一行的位置
回退，尝试当前行的其它位置
*/
class Solution {
public:
	// solution: 一个解决方案，从第一行开始到当前行的上一行每一行已经放置皇后的点
    bool isValid(vector<pair<int, int>>& solution, int row, int col){
		// 判断当前行尝试的皇后位置是否和前面几行的皇后位置有冲突
		// i.second == col: 第i个皇后与当前这个点在同一列
		// i.first + i.second == row + col: 第i个皇后与当前点在撇上，横坐标+纵坐标值相同
		// i.first - i.second == row - col：第i个皇后与当前点在捺上, 横坐标-纵坐标值相同
        for(const auto& e : solution){
            if(e.second == col || e.first + e.second == row + col || e.first - e.second == row - col){
                return false;
            }
        }
        return true;
    }
    void nQueensBacktrack(vector<vector<pair<int, int>>>& solutions, vector<pair<int, int>>& solution, int curRow, int n){
        if(curRow == n){
            solutions.push_back(solution);
			return;
        }
		// 尝试当前行的每一个位置（列）是否可以放置一个皇后
        for(int col = 0; col < n; ++col){
            if(isValid(solution, curRow, col)){
				// 如果可以，在保存当前位置，继续确定下一行皇后的位置
				// 直接调用构造函数，内部构造pair, 或者调用make_pair
                solution.emplace_back(curRow, col);
                nQueensBacktrack(solutions, solution, curRow + 1, n);
				// 回溯，删除当前位置，尝试当前行的其它位置
                solution.pop_back();
            }
        }
    }
    vector<vector<string>> transResult(vector<vector<pair<int, int>>>& solutions, int n){
        vector<vector<string>> vvs;
		// 把每一种解决方案都转换为string形式，最终结果
        for(const auto& solution : solutions){
            // 存放n个string的数组，每个string初始化n大小，每个位置初始化为 '.'
            vector<string> vs(n, string(n, '.'));
			// n*n char: 每行有n个元素，把皇后的位置修改为Q
            for(const auto& e : solution){
                vs[e.first][e.second] = 'Q';
            }
            vvs.push_back(vs);
        }
        return vvs;
    }
    vector<vector<string>> solveNQueens(int n) {
		// 按坐标位置存放所有解决方案
        vector<vector<pair<int, int>>> solutions;
		// 存放一种解决方案中的所有皇后的位置
        vector<pair<int, int>> solution;
		// 解决方案，回溯
        nQueensBacktrack(solutions, solution, 0, n);
		// 把坐标位置转成string
        return transResult(solutions, n);
    }
};