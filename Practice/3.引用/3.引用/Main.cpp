#include <iostream>
//
//void Swap(int& a, int& b)
//{
//	int temp = a;
//	a = b;
//	b = temp;
//}
//
//int& AddItself(int a)
//{
//	return a += 10;
//}
//
//void TestRef(void)
//{
//	const int a = 10;
//	//int& ra = a; 因为a是常量所以这样不行
//	const int& ra = a;
//
//	const int& rb = 10;//可以直接赋常量
//
//	double c = 13.14;
//	const int& rc = c;//可以直接将c隐式类型转换，变成整形常量
//
//	std::cout << rc << std::endl; //13
//}
//
//int main(void)
//{
//	/*int a = 0;
//	int& ra = a;
//
//	std::cout << a << std::endl;
//	std::cout << ra << std::endl;
//*/
//	//TestRef();
//	int a = AddItself(10);
//	std::cout << a << std::endl;
//	system("pause");
//	return 0;
//}

#include <time.h>
struct A
{
	int a[10000];
};
A a;
A* TestFunc1()
{
	return &a;
}
A& TestFunc2()
{
	return a;
}
void TestRefAndValue()
{
	
	// 以指针作为函数参数
	size_t begin1 = clock();
	for (size_t i = 0; i < 10000; ++i)
		TestFunc1();
	size_t end1 = clock();
	// 以引用作为函数参数
	size_t begin2 = clock();
	for (size_t i = 0; i < 10000; ++i)
		TestFunc2();
	size_t end2 = clock();
	// 分别计算两个函数运行结束后的时间
	std::cout << "TestFunc1(int*)-time:" << end1 - begin1 << std::endl;
	std::cout << "TestFunc2(int&)-time:" << end2 - begin2 << std::endl;
}
// 运行多次，检测指针和引用在传参方面的效率区别
int main()
{
	for (int i = 0; i < 10; ++i)
	{
		TestRefAndValue();
	}

	return 0;
}