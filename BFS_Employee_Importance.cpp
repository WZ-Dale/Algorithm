/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/employee-importance

给定一个保存员工信息的数据结构，它包含了员工唯一的id，重要度 和 直系下属的id。
比如，员工1是员工2的领导，员工2是员工3的领导。他们相应的重要度为15, 10, 5。那么：
员工1的数据结构是[1, 15, [2]]，员工2的数据结构是[2, 10, [3]]，员工3的数据结构是[3, 5, []]。
注意虽然员工3也是员工1的一个下属，但是由于并不是直系下属，因此没有体现在员工1的数据结构中。
现在输入一个公司的所有员工信息，以及单个员工id，返回这个员工和他所有下属的重要度之和。

示例:
    输入: [[1, 5, [2, 3]], [2, 3, []], [3, 3, []]], 1
    输出: 11
    解释: 员工1自身的重要度是5，他有两个直系下属2和3，而且2和3的重要度均为3。因此员工1的总重要度是 5 + 3 + 3 = 11。
注意：一个员工最多有一个直系领导，但是可以有多个直系下属员工数量不超过2000。
*/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

struct Employee
{
    int id;
    int importance;
    vector<int> subid;
};

class Solution
{
public:
    int getImportance(vector<Employee*>& employees, int id) {
        int res = 0;
        queue<int> q;
        //初始化队列
        q.push(id);
        //把员工信息保存在map中，方便查询
        unordered_map<int, Employee*> m;
        for (auto& e : employees){
            m[e->id] = e;
        }
        //遍历队列
        while(!q.empty()){
            int t = q.front();
            q.pop();
            res += m[t]->importance;
            for(auto& num : m[t]->subid){
                q.push(num);
            }
        }
        return res;
    }
};

int main(){
    vector<Employee*> employees(3);
    employees[0] = new Employee, employees[0]->id = 1, employees[0]->importance = 5, employees[0]->subid = {2, 3};
    employees[1] = new Employee, employees[1]->id = 2, employees[1]->importance = 3, employees[1]->subid = {};
    employees[2] = new Employee, employees[2]->id = 3, employees[2]->importance = 3, employees[2]->subid = {};
    Solution S;
    cout << S.getImportance(employees, 1) << endl;
    return 0;
}