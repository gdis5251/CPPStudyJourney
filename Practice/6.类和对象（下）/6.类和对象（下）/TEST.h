#include <iostream>

//class Date
//{
//public:
//	/*Date(int year, int month, int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}*/
//	Date(int year, int month, int day)
//		:_year(year),
//		_month(month),
//		_day(day)
//	{}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//
//class A
//{
//public:
//	A(int a)
//		:_a(a)
//	{}
//private:
//	int _a;
//};
//
//class B
//{
//public:
//	B(int c, int a)
//		:_c(c),
//		_b(10),
//		_a(a)
//	{}
//private:
//	int& _c;
//	const int _b;
//	A _a;
//};


class Time
{
public:
	Time(int hour = 0)
		:_hour(hour)
	{
	}

	int _hour;
};
class Date
{
public:
	void Display()
	{
		std::cout << _day << std::endl;
		std::cout << _t._hour << std::endl;
		std::cout << *_p << std::endl;
		std::cout << _st << std::endl;

	}

private:
	int _day = 10;
	int *_p = new int(2);
	Time _t = 5;
	static int _st;
};

int Date::_st = 6;

