#include <string.h>
#include <iostream>
#pragma warning(disable:4996)

/*
C++�ṹ������Լ��뺯��
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



������ֶ��巽ʽ
1.�����Ͷ���ȫ����������
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

2.��������.h�ļ��У���Ķ������.cpp�ļ���
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
	Date()	//�޲ι��캯��
	{
		_year = 1997;
		_month = 9;
		_day = 21;
	}

	Date(int year, int month, int day)	//�вι��캯��
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
		_year = year;	//�ȼ���this->_year = year
		_month = month;
		_day = day;
	}
private:
	int _year; // ��
	int _month; // ��
	int _day; // ��
};
void Test(){	Date d;	//�����޲ι��캯��ʱ�����治��Ҫ������	Date g(1997, 9, 21); //�����вι��캯��ʱ����Ҫд��Ӧ�Ĳ���ֵ	Date d2();	//����ڴ�������ʱ���������ֲ�д�������ᱻ���ɺ�������}*/class Time{
public:
	Time()	{		std::cout << "Time" << std::endl;	}};class Date{public:	Date()	{		_a = 1;		_p = &_a;	}	~Date()	{		free(_p);		_p = nullptr;	}private:	int _a;	int *_p;};