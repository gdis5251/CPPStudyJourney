class Date
{
public :
	//构造函数
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	//拷贝构造函数
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	//赋值重定义函数
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}

	Date& operator+=(int day)
	{
		_day += day;

		if (_day > getMonthDay(*this))
		{
			int count = 0;
			Date copy(*this);

			while (1)
			{
				_day -= getMonthDay(copy);
				count++;

				copy._month += 1;
				if (copy._month > 12)
				{
					copy._year += 1;
					copy._month -= 12;
				}

				if (_day <= getMonthDay(copy))
					break;
			}

			_month += count;
			if (_month > 12)
			{
				_year += (_month / 12);
				_month %= 12;
			}
		}

		return *this;
	}

	Date& operator-=(int day)
	{
		_day -= day;

		if (_day < 1)
		{
			int count = 0;
			Date copy(*this);

			while (1)
			{
				copy._month -= 1;
				if (copy._month < 1)
				{
					copy._year -= 1;
					copy._month = 12;
				}

				_day += getMonthDay(copy);
				count++;

				if (_day > 0)
					break;
			}

			_month -= count;
			if (_month < 1)
			{
				_year -= -((_month / 12) - 1);
				_month = _month % 12 + 12;
			}
		}

		return *this;
	}

	Date operator+(int day)
	{
		//因为+不改变自身的值，所以需要拷贝一个类进行加法，返回拷贝的类
		Date copy(*this);
		copy.operator+=(day);

		return copy;
	}

	Date operator-(int day)
	{
		Date copy(*this);
		copy.operator-=(day);

		return copy;
	}

	int operator-(const Date& d)
	{
		int count = 0;

		if (*this >= d)
		{
			Date copy(d);
			while (1)
			{
				if (*this == copy)
					break;

				copy++;
				count++;
			}
		}
		else
		{
			Date copy(*this);
			while (1)
			{
				if (d == copy)
					break;

				copy++;
				count++;
			}
		}
		
		return count;
	}

	//前置++
	Date& operator++()
	{
		this->operator+=(1);

		return *this;
	}

	//后置++
	Date operator++(int)
	{
		Date copy(*this);
		this->operator+=(1);

		return copy;
	}

	//前置--
	Date& operator--()
	{
		this->operator-=(1);
		return *this;
	}

	//后置--
	Date operator--(int)
	{
		Date copy(*this);
		this->operator-=(1);

		return copy;
	}

	bool operator>(const Date& d)const 
	{
		if (this->_year > d._year)
			return true;
		else if (this->_year == d._year &&
			this->_month > d._month)
			return true;
		else if (this->_year == d._year &&
			this->_month == d._month &&
			this->_day > d._day)
			return true;

		return false;
	}

	bool operator>=(const Date& d)const
	{
		if (this->_year > d._year)
			return true;
		else if (this->_year == d._year &&
			this->_month > d._month)
			return true;
		else if (this->_year == d._year &&
			this->_month == d._month &&
			this->_day >= d._day)
			return true;

		return false;
	}

	bool operator<(const Date& d)const
	{
		if (this->_year < d._year)
			return true;
		else if (this->_year == d._year &&
			this->_month < d._month)
			return true;
		else if (this->_year == d._year &&
			this->_month == d._month &&
			this->_day < d._day)
			return true;

		return false;
	}

	bool operator<=(const Date& d)const
	{
		if (this->_year < d._year)
			return true;
		else if (this->_year == d._year &&
			this->_month < d._month)
			return true;
		else if (this->_year == d._year &&
			this->_month == d._month &&
			this->_day <= d._day)
			return true;

		return false;
	}

	bool operator==(const Date& d)const
	{
		if (this->_year == d._year &&
			this->_month == d._month &&
			this->_day == d._day)
			return true;

		return false;
	}

	bool operator!=(const Date& d)const
	{
		if (this->_year != d._year &&
			this->_month != d._month &&
			this->_day != d._day)
			return true;

		return false;
	}

	



private:
	int _year;
	int _month;
	int _day;
	
	//是否是闰年
	bool isLeapYear(int year)
	{
		return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
	}

	//该月的天数
	int getMonthDay(const Date& d)
	{
		if (isLeapYear(d._year) && d._month == 2)
			return 29;

		switch (d._month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 2:
			return 28;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		}
	}
};