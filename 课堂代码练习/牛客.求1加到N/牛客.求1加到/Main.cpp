#include <iostream>

class Solution {
public:
	class Sum
	{
	public:
		Sum()
		{
			sum += num;
			++num;
		}
	};
	int Sum_Solution(int n) {
		sum = 0;
		num = 1;
		Sum arr[n];//因为牛客网的编译器是clang,所以支持可变数组
		return sum;
	}
private:
	static int sum;
	static int num;
};

int Solution::sum = 0;
int Solution::num = 1;

