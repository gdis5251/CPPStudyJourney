//#include <iostream>


//int add(int a, int b)
//{
//	return a + b;
//}
//
//double add(double a, double b)
//{
//	return a + b;
//}
//
//long add(long a, long b)
//{
//	return a + b;
//}
//
//int main(void)
//{
//	add(1, 2);
//	add(1.2, 5.3);
//	add(10L, 20L);
//
//	return 0;
//}


int add(int a, int b);
int add(double a, double b);

int main(void)
{
	int a = add(1, 2);
	int b = add(3.0, 4.0);
	return 0;
}