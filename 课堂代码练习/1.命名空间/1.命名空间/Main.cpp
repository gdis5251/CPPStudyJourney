#include <iostream>
//1.普通的命名空间
namespace N1	//N1为命名空间的名称
{
	//命名空间内可以定义变量也可以定义函数
	int a;

	int add(int left, int right)
	{
		return left + right;
	}
}

//2.命名空间可以嵌套
namespace N2
{
	int a;
	int b;
	int add(int left, int right)
	{
		return left + right;
	}

	namespace N3
	{
		int c;
		int d;
		int sub(int left, int right)
		{
			return left - right;
		}
	}
}



//3. 同一工程中允许出现名字相同的命名空间
//	 在编译过程中，编译器会自动合并名字相同的命名空间
namespace N1
{
	int mul(int left, int right)
	{
		return left * right;
	}
}

using namespace N2;
int main(void)
{
	std::cout << N2::a;
	std::cout << b;

	int sum = add(1, 5);
	return 0;
}