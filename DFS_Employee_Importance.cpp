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
#include <unordered_map>

using namespace std;

struct Employee
{
    int id;
    int importance;
    vector<int> subid;
};

/*
边界: 下属为空
    每次先加第一个下属的重要性
    按照相同的操作再去加下属的第一个下属的重要性
*/
class Solution
{
public:
    void Dfs(vector<Employee*> &employees, int &sum, int id){
        // 这里无需判断边界，for循环就是一个边界，下属为空，直接结束
        // 当前员工的重要性
        sum += employees[id-1]->importance;
        // 遍历其下属
        for(const auto& subid : employees[id-1]->subid){
            Dfs(employees, sum, subid);
        }
    }
    int getImportance(vector<Employee*> &employees, int id) {
        if(employees.empty()){
            return 0;
        }
        int sum = 0;
        Dfs(employees, sum, id);
        return sum;
    }
};

// 使用map进行简化，就不需要进行id-1了（因为有时候员工id不一定和下标id-1匹配）
class Solution1
{
public:
    void Dfs(unordered_map<int, Employee*> &info, int &sum, int id){
        // 这里无需判断边界，for循环就是一个边界，下属为空，直接结束
        // 当前员工的重要性
        sum += info[id]->importance;
        // 遍历其下属
        for(const auto& id : info[id]->subid){
            Dfs(info, sum, id);
        }
    }
    int getImportance(vector<Employee*> &employees, int id) {
        if(employees.empty()){
            return 0;
        }
        //把员工信息用map存储，方便后面的使用
        unordered_map<int, Employee*> info;
        for(auto& e : employees){
            info[e->id] = e;    // 键值对：键存id，值存员工结构体指针
        }
        int sum = 0;
        Dfs(info, sum, id);
        return sum;
    }
};

// 继续简化代码，使Dfs直接返回求和的值
class Solution2
{
public:
    int Dfs(unordered_map<int, Employee*> &info, int id){
        int sum = info[id]->importance;
        for(const auto& id : info[id]->subid){
            sum += Dfs(info, id);
        }
        return sum;
    }
    int getImportance(vector<Employee*> &employees, int id) {
        if(employees.empty()){
            return 0;
        }
        unordered_map<int, Employee*> info;
        for(auto& e : employees){
            info[e->id] = e;
        }
        return Dfs(info, id);
    }
};

int main(){
    vector<Employee*> employees(3);
    employees[0] = new Employee, employees[0]->id = 1, employees[0]->importance = 5, employees[0]->subid = {2, 3};
    employees[1] = new Employee, employees[1]->id = 2, employees[1]->importance = 3, employees[1]->subid = {};
    employees[2] = new Employee, employees[2]->id = 3, employees[2]->importance = 3, employees[2]->subid = {};
    Solution S;
    cout << S.getImportance(employees, 1) << endl;
    Solution S1;
    cout << S1.getImportance(employees, 1) << endl;
    Solution S2;
    cout << S2.getImportance(employees, 1) << endl;
    return 0;
}