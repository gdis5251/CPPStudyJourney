#include <iostream>

//class a
//{
//public:
//	virtual void fun()
//	{
//
//	}
//protected:
//	int a;
//};
//
//void Test()
//{
//	a a;
//	std::cout << sizeof(a) << std::endl;
//}

//class base
//{
//public:
//	virtual void fun1()
//	{
//		std::cout << "base::fun1()" << std::endl;
//	}
//	virtual void fun2()
//	{
//		std::cout << "base::fun2()" << std::endl;
//	}
//	void fun3()
//	{
//		std::cout << "base::fun3() non-virtual" << std::endl;
//	}
//
//protected:
//	int _b;
//};
//
//class derive : public base
//{
//public:
//	virtual void fun1()
//	{
//		std::cout << "derive::fun1()" << std::endl;
//	}
//
//	//void fun5()
//	//{
//	//	std::cout << "ss" << std::endl;
//	//}
//
//protected:
//	int _d;
//};
//
//int _globe = 0;
//
//void Test(void)
//{
//	//base b;
//	derive d;
//	int a = 0;
//	int *p = new int;
//
//	std::cout << "栈：" << &a << std::endl;
//	std::cout << "堆：" << p << std::endl;
//	std::cout << "数据段：" << &_globe << std::endl;
//	printf("代码段：%p\n", &base::fun3);
//	printf("虚函数：%p\n", *((int*)*(int*)&d));
//	printf("虚表：%p\n", *(int*)&d);
//}


//class OrdinaryUser
//{
//public:
//	virtual void WatchFiles()
//	{
//		std::cout << "Ordinary User can't see files" << std::endl;
//	}
//};
//
//class VIPUser : public OrdinaryUser
//{
//public:
//	virtual void WatchFiles() override
//	{
//		std::cout << "VIP User can see files" << std::endl;
//	}
//};
//
//void Func(OrdinaryUser& user)
//{
//	user.WatchFiles();
//}
//
//void Test()
//{
//	OrdinaryUser o_user;
//	VIPUser vip_user;
//
//	Func(o_user);
//	Func(vip_user);
//}

//class Base
//{
//public:
//	virtual void Fun1() 
//	{
//		std::cout << "Base::Fun1()" << std::endl;
//	};
//	virtual void Fun2()
//	{
//		std::cout << "Base::Fun2()" << std::endl;
//	};
//};
//
//class Derive : public Base
//{
//public:
//	virtual void Fun2() override
//	{
//		std::cout << "Derive::Fun2()" << std::endl;
//	}
//	virtual void Fun3()
//	{
//		std::cout << "Derive::Fun3()" << std::endl;
//	}
//	virtual void Fun4()
//	{
//		std::cout << "Derive::Fun4()" << std::endl;
//	}
//};
//class Derive2 : public Derive
//{
//public:
//	virtual void Fun2() override
//	{
//		std::cout << "Derive::Fun2()" << std::endl;
//	}
//	virtual void Fun3()
//	{
//		std::cout << "Derive::Fun3()" << std::endl;
//	}
//	virtual void Fun4()
//	{
//		std::cout << "Derive::Fun4()" << std::endl;
//	}
//};

class Base1
{
public:
	virtual void Fun1()
	{
		std::cout << "Base1::Fun1()" << std::endl;
	}
	virtual void Fun2()
	{
		std::cout << "Base1::Fun2()" << std::endl;
	}
};

class Base2
{
public:
	virtual void Fun1()
	{
		std::cout << "Base2::Fun1()" << std::endl;
	}
	virtual void Fun2()
	{
		std::cout << "Base2::Fun2()" << std::endl;
	}
};

class Derive : public Base1, public Base2
{
	virtual void Fun1() override
	{
		std::cout << "Derive::Fun1()" << std::endl;
	}
	virtual void Fun3()
	{
		std::cout << "Derive::Fun3()" << std::endl;
	}
};

typedef void(*VFTPtr)();

void Print(VFTPtr table[])
{
	std::cout << table << std::endl;
	for (int i = 0; table[i] != nullptr; i++)
	{
		std::cout << table[i] << ":  ";
		VFTPtr v = table[i];
		v();
	}
}

void Test(void)
{
	Base1 b1;
	Base2 b2;
	Derive d;
	//Derive2 d2;

	std::cout << "Base1的虚表:  ";
	Print((VFTPtr*)(*(int*)&b1));

	std::cout << "Base2的虚表:  ";
	Print((VFTPtr*)(*(int*)&b2));

	std::cout << "Derive的虚表:  " << std::endl;
	std::cout << "继承Base1的虚表:  ";
	Print((VFTPtr*)(*(int*)&d)); //继承Base1 的虚表
	std::cout << "继承Base2的虚表:  ";
	Print((VFTPtr*)(*(int*)((char*)&d + sizeof(Base1)))); //继承Base2的虚表
}

//using namespace std;
//
//class Base {
//public:
//	virtual void func1() { cout << "Base::func1" << endl; }
//	virtual void func2() { cout << "Base::func2" << endl; }
//private:
//	int a;
//};
//class Derive :public Base {
//public:
//	virtual void func1() { cout << "Derive::func1" << endl; }
//	virtual void func3() { cout << "Derive::func3" << endl; }
//	virtual void func4() { cout << "Derive::func4" << endl; }
//private:
//	int b;
//};
////定义一个函数指针， 表示一类返回值为void,参数个数为0的函数
//typedef void(*VFPTR)();
//
//void PrintVF(VFPTR vfpt[])
//{
//	printf("虚表： %p\n", vfpt);
//	//虚表以nullptr
//	while (*vfpt != nullptr)
//	{
//		VFPTR vf = *vfpt;
//		printf("0x%p-->", vf);
//		vf();
//		//cout << endl;
//		++vfpt;
//	}
//}
//
//void Test()
//{
//	Base b;
//	Derive d;
//
//	PrintVF((VFPTR*)*(int*)&b);
//	PrintVF((VFPTR*)*(int*)&d);
//}