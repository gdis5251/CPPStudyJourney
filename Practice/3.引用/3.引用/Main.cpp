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
//	//int& ra = a; ��Ϊa�ǳ���������������
//	const int& ra = a;
//
//	const int& rb = 10;//����ֱ�Ӹ�����
//
//	double c = 13.14;
//	const int& rc = c;//����ֱ�ӽ�c��ʽ����ת����������γ���
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
	
	// ��ָ����Ϊ��������
	size_t begin1 = clock();
	for (size_t i = 0; i < 10000; ++i)
		TestFunc1();
	size_t end1 = clock();
	// ��������Ϊ��������
	size_t begin2 = clock();
	for (size_t i = 0; i < 10000; ++i)
		TestFunc2();
	size_t end2 = clock();
	// �ֱ���������������н������ʱ��
	std::cout << "TestFunc1(int*)-time:" << end1 - begin1 << std::endl;
	std::cout << "TestFunc2(int&)-time:" << end2 - begin2 << std::endl;
}
// ���ж�Σ����ָ��������ڴ��η����Ч������
int main()
{
	for (int i = 0; i < 10; ++i)
	{
		TestRefAndValue();
	}

	return 0;
}