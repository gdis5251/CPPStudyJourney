#include <iostream>
//1.��ͨ�������ռ�
namespace N1	//N1Ϊ�����ռ������
{
	//�����ռ��ڿ��Զ������Ҳ���Զ��庯��
	int a;

	int add(int left, int right)
	{
		return left + right;
	}
}

//2.�����ռ����Ƕ��
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



//3. ͬһ�������������������ͬ�������ռ�
//	 �ڱ�������У����������Զ��ϲ�������ͬ�������ռ�
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