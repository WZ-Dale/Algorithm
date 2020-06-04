/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/combination-sum/
*/

/*
此题相加的元素可以重复，所以去下一个元素的位置可以从当前位置开始， DFS + 回溯
为了保证组合不重复(顺序不同，元素相同，也算重复)，不再从当前位置向前看
1. 从第一个元素开始相加
2. 让局部和继续累加候选的剩余值
3. 局部和等于目标值，保存组合，向上回退，寻找其它组合
*/
class Solution {
public:
    void backTrace(vector<int>& candidates, vector<vector<int>>& vv, vector<int>& v, int cursum, int prevPosition, int target){
        if(cursum >= target){
            if(cursum == target){
                vv.push_back(v);
            }
            return;
        }
        for(int i = prevPosition; i < candidates.size(); ++i){
            if(candidates[i] > target){
                continue;
            }
            v.push_back(candidates[i]);
            backTrace(candidates, vv, v, cursum + candidates[i], i, target);
            v.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> vv;
        vector<int> v;
        if(candidates.empty()){
            return vv;
        }
        int cursum = 0;
        backTrace(candidates, vv, v, cursum, 0, target);
        return vv;
    }
};
