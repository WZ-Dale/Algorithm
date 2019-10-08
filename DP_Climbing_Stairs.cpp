/*
一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
*/
#include <iostream>

using namespace std;

/*
方法一：动态规划
    状态：
        子状态：跳上1级，2级，3级，...，n级台阶的跳法数
        f(n)：还剩n个台阶的跳法数
    状态递推：
        n级台阶，第一步有n种跳法：跳1级、跳2级、到跳n级 
            跳1级，剩下n-1级，则剩下跳法是f(n-1)
            跳2级，剩下n-2级，则剩下跳法是f(n-2)
        f(n) = f(n-1)+f(n-2)+...+f(n-n)
            = f(n-1)+f(n-2)+...+f(0)
        f(n-1) = f(n-2)+...+f(0)
        则：f(n) = 2*f(n-1)
    初始值：
        f(1) = 1
        f(2) = 2*f(1) = 2
        f(3) = 2*f(2) = 4
        f(4) = 2*f(3) = 8
        所以它是一个等比数列
        f(n) = 2^(n-1)
    返回结果：f(n)
方法二：排列
    每个台阶看成一个位置，除过最后一个位置，其它位置都有两种可能性（要么跳，要么不跳）
    所以总的排列数为2^(n-1)*1 = 2^(n-1)
*/
class Solution
{
public:
    int JumpStair(int n){
        if(n  <= 0){
            return 0;
        }
        int total = 1;
        for(int i = 1; i < n; ++i){
            total *= 2;             // 2^(n-1)
        }
        return total;
    }
};
/*
扩展：降低时间复杂度
     上述实现的时间复杂度:O(N)
     O(1)的实现：使用移位操作
*/
class Solution1
{
public:
	int JumpStair(int n){
        if(n  <= 0){
            return 0;
        }
        return 1 << n - 1;      // 使用移位操作
    }
};
/*
总结：
    此题看似复杂，通过抽象和归纳，可以找出问题的内在规律
    定义问题的状态，以及状态间的递推关系，找到问题的答案
    
扩展1：
    上述问题为变态青蛙跳台阶，太疯狂，这只青蛙像是吃了大力丸
    身上充满了无穷的力量。现在让它变成一个正常的青蛙，限制它
    一次只能跳1阶或者2阶，现在该如何解答
    
扩展2：
    牛客网上另一个题目：矩形覆盖
    我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。
    请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？
*/
// 上述两个题目都可以用斐波那契数列求解：
class Solution2
{
public:
	int JumpStair(int n){
        // 初始值
        if(n <= 0){
            return 0;
        }
        else if(n == 1){
            return 1;
        }
        else if(n == 2){
            return 2;
        }
        else{
            int a = 1;
            int b = 2;
            int result = 0;
            for(int i = 3; i <= n; ++i){
                // F(n)=F(n-1)+F(n-2)
                result = a + b;
                // 更新值
                a = b;
                b = result;
            }
            return result;
        }
    }
};

int main()
{
	int n = 4;
    Solution F;
    cout << F.JumpStair(n) << endl;
    Solution1 F1;
    cout << F1.JumpStair(n) << endl;
    Solution2 F2;
    cout << F2.JumpStair(n) << endl;
	return 0;
}
