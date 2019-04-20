#pragma once

#include <iostream>
#include <string>

//基类
class Person
{
public:
	Person()
	{
		std::cout << "Person()" << std::endl;
	}

	Person(const Person& x)
	{
		std::cout << "Person(const Person& x)" << std::endl;
	}

	Person& operator=(const Person& x)
	{
		std::cout << "Student operator=" << std::endl;

		return *this;
	}

	~Person()
	{
		std::cout << "~Person()" << std::endl;
	}

	void print()
	{
		std::cout << "name: " << _name.c_str() << std::endl;
		std::cout << "age: " << _age << std::endl;
		std::cout << "sex: " << _sex.c_str() << std::endl;
	}

protected:
	std::string _name = "Gerald";
	size_t _age = 21;
	std::string _sex = "male";
};


//派生类
class Student : public Person
{
public:
	Student()
	{
		std::cout << "Student()" << std::endl;
	}
	
	Student(const Student& x)
	{
		std::cout << "Student(const Student& x)" << std::endl;
	}

	Student& operator=(const Student& x)
	{
		std::cout << "Student operator=" << std::endl;

		return *this;
	}

	~Student()
	{
		std::cout << "~Student()" << std::endl;
	}
	void print()
	{
		std::cout << "name: " << _name.c_str() << std::endl;
		std::cout << "age: " << _age << std::endl;
		std::cout << "sex: " << _sex.c_str() << std::endl;
		std::cout << "sno: " << _sno << std::endl;
	}

protected:
	size_t _sno = 110;
	size_t _age = 18;
};



//class A
//{
//public:
//		
//	
//};
//
//class B : public A
//{
//public:
//};
//
//class C : public B
//{
//public:
//};

class G
{
public:
	int _g;
};

class A : virtual public G
{
public:
	int _a;
};

class B : virtual public G
{
public:
	int _b;
};

class C : public A, public B
{
public:
	int _c;
};

void test(void)
{
	C c;
	c.A::_g = 1;
	c.B::_g = 2;
	c._a = 3;
	c._b = 4;
	c._c = 5;
}
