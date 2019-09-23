/*
在古老的一维模式识别中,常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。
但是,如果向量中包含负数,是否应该包含某个负数,并期望旁边的正数会弥补它呢？
例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。
给一个数组，返回它的最大连续子序列的和(子向量的长度至少是1)。
*/
#include <iostream>
#include <vector>

using namespace std;

/*
方法：动态规划
    状态：
        子状态：长度为1，2，3，...,n的子数组和的最大值
        F(i):长度为i的子数组和的最大值，这种定义不能形成递推关系，舍弃
        F(i):以array[i]为末尾元素的子数组和的最大值
    状态递推：
        F(i) = max(F(i-1) + array[i]，array[i])
        F(i) = (F(i-1) > 0) ? (F(i-1) + array[i]) : array[i]
    初始值：
        F(0) = array[0]
    返回结果：
        maxsum：所有F(i)中的最大值
        maxsum = max(maxsum，F(i))
*/
class Solution
{
public:
    int MaxSubarraySum(vector<int> array){
        if(array.empty()){
            return 0;
        }
        // F(i)初始化
        int sum = array[0];
        // maxsum初始化
        int maxsum = array[0];
        for(int i = 1; i < array.size(); ++i){
            // F(i) = max(F(i-1) + array[i]，array[i])
            sum = (sum > 0) ? (sum + array[i]) : array[i];
            // maxsum = max(maxsum，F(i))
            maxsum = maxsum > sum ? maxsum : sum;
        }
        return maxsum;
    }
};

int main(){
    vector<int> array;
    array.push_back(6);
    array.push_back(-3);
    array.push_back(-2);
    array.push_back(7);
    array.push_back(-15);
    array.push_back(1);
    array.push_back(2);
    array.push_back(2);
    Solution S;
    cout << S.MaxSubarraySum(array) << endl;
    return 0;
}