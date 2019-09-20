/*
要求输入一个整数n，请输出斐波那契数列的第n项（从0开始，第0项为0）。
*/
#include <iostream>
#include <ctime>

using namespace std;


/* 
方法一：递归
    斐波那契数列定义：F(n)=F(n-1)+F(n-2)（n>=2，n∈N*），其中F(1)=1，F(2)=1
*/
class Solution
{
public:
	int Fibonacci(int n){
        // 初始值
		if (n <= 0){
			return 0;
		}
		else if (n == 1 || n == 2){
			return 1;
		}
		else{
            // F(n)=F(n-1)+F(n-2)
			return Fibonacci(n - 1) + Fibonacci(n - 2);
		}
	}
};
/*
递归的方法时间复杂度为O(2^n)，随着n的增大呈现指数增长，效率低下
当输入比较大时，可能导致栈溢出
在递归过程中有大量的重复计算
*/

/* 
方法二：动态规划
	状态：F(n)
    状态递推：F(n)=F(n-1)+F(n-2)
    初始值：F(1)=F(2)=1
    返回结果：F(N)
*/
class Solution1
{
public:
	int Fibonacci(int n){
		//vector<int> record(n + 1, 0);
        //int* record = new int[n + 1];
        int record[n + 1] = {0};// 申请一个数组，保存子问题的解，题目要求从第0项开始
		record[1] = record[2] = 1;// 初始状态
        for(int i = 3; i <= n; ++i){
            record[i] = record[i - 1] + record[i - 2];// 状态转移 F(n)=F(n-1)+F(n-2)
        }
        return record[n];// 返回值
    }
};
/*
上述解法的空间复杂度为O(n)
其实F(n)只与它相邻的前两项有关，所以没有必要保存所有子问题的解
只需要保存两个子问题的解就可以
下面方法的空间复杂度将为O(1)
*/
class Solution2
{
public:
	int Fibonacci(int n){
        // 初始值
        if(n <= 0){
            return 0;
        }
        else if(n == 1 || n == 2){
            return 1;
        }
        else{
            int a = 1;
            int b = 1;
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
	int n = 40;
	clock_t startTime0, endTime0, startTime1, endTime1, startTime2, endTime2;

    int Fn = 0;
    Solution F;
	startTime0 = clock();//计时开始
    Fn = F.Fibonacci(n);
	endTime0 = clock();//计时结束
	cout << "recursion:\n" << Fn << endl;
	cout << "The run time is:" << (double)(endTime0 - startTime0) / CLOCKS_PER_SEC << "s" << endl;
    
    int Fn1 = 0;
    Solution1 F1;
    startTime1 = clock();//计时开始
    Fn1 = F1.Fibonacci(n);
	endTime1 = clock();//计时结束
	cout << "dynamic programming:\n" << Fn1 << endl;
	cout << "The run time is:" << (double)(endTime1 - startTime1) / CLOCKS_PER_SEC << "s" << endl;

    int Fn2 = 0;
    Solution2 F2;
    startTime2 = clock();//计时开始
    Fn2 = F2.Fibonacci(n);
	endTime2 = clock();//计时结束
	cout << "dynamic programming:\n" << Fn2 << endl;
	cout << "The run time is:" << (double)(endTime2 - startTime2) / CLOCKS_PER_SEC << "s" << endl;


	cout << "All run time is:" << (double)clock() / CLOCKS_PER_SEC << "s" << endl;

	return 0;
}