#include <iostream>

/*
template <typename T1>
void swap(T1& x, T1& y)
{
	T1 temp = x;
	x = y;
	y = temp;
}
*/


int add(const int& left, const int&right)
{
	return left + right;
}

template <typename T1>
T1 add(const T1& left, const T1& right)
{
	return left + right;
}

void test(void)
{
	int a = 3, b = 2;
	double c = 5.0, d = 1.0;

	add(a, b);
	add(c, d);

	add<int>(a, d);
}