#include <string.h>
#include <iostream>
#pragma warning(disable:4996)

/*
C++结构体里可以加入函数
typedef struct Student
{
	void setStudentInfo(const char *name, const char *sex, int age)
	{
		strncpy(_name, name, strlen(name) + 1);
		strncpy(_sex, sex, strlen(sex) + 1);
		_age = age;
	}

	void printStudentInfo()
	{
		std::cout << "name:" << _name << "  sex:" << _sex << "  age:" << _age << std::endl;
	}




private:
	char _name[20];
	char _sex[6];
	short _age;
} Student;



类的两种定义方式
1.声明和定义全部在类体中
class Student
{
public:
	void showInfo()
	{
		std::cout << _name << " " << _sex << " " << age << std::endl;
	}

private:
	char _name[20];
	char _sex[6];
	int _age;
};

2.声明放在.h文件中，类的定义放在.cpp文件中
person.h
class Person
{
public:
	void showInfo();
private:
	char _name[20];
	char _sex[6];
	int _age;
};




//person.cpp
#include "person.h"

void Person::showInfo()
{
	std::cout << _name << _sex << _age << std::endl;
}


class Date
{
public:
	Date()	//无参构造函数
	{
		_year = 1997;
		_month = 9;
		_day = 21;
	}

	Date(int year, int month, int day)	//有参构造函数
	{
		_year = year;
		_month = month;
		_day = day;
	}
	void Display()
	{
		std::cout << _year << "-" << _month << "-" << _day << std::endl;
	}

	void SetDate(int year, int month, int day)
	{
		_year = year;	//等价于this->_year = year
		_month = month;
		_day = day;
	}
private:
	int _year; // 年
	int _month; // 月
	int _day; // 日
};
void Test(){	Date d;	//调用无参构造函数时，后面不需要加括号	Date g(1997, 9, 21); //调用有参构造函数时，需要写相应的参数值	Date d2();	//如果在创建对象时，加括号又不写参数，会被当成函数声明}*/class Time{
public:
	Time()	{		std::cout << "Time" << std::endl;	}};class Date{public:	Date()	{		_a = 1;		_p = &_a;	}	~Date()	{		free(_p);		_p = nullptr;	}private:	int _a;	int *_p;};