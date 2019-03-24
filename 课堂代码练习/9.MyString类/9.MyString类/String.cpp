#include "MyString.h"

const size_t Gerald::String::npos = -1;


void Gerald::String::reserve(size_t n)
{
	if (n > _capacity)
	{
		char *new_str = new char[n + 1];
		strcpy(new_str, _str);
		delete[] _str;

		_str = new_str;
		_capacity = n;
	}
}

void Gerald::String::resize(size_t n, char ch)
{
	if (n < _size)
	{
		_size = n;
		_str[_size] = '\0';
	}
	else if (n > _size)
	{
		if (n > _capacity)
		{
			reserve(n);
		}
		/*while (_size < n)
		{
			push_back(ch);
			_size++;
		}*/
			
		memset(_str + _size, ch, n - _size);
		_size = n;
		_str[_size] = '\0';
	}

	
}

void Gerald::String::push_back(char ch)
{
	if (_size == _capacity)
	{
		reserve(_capacity * 2);
	}

	_str[_size] = ch;
	_size++;

	//这一步比较重要，若忘记加了，则会出现读取字符串停不下来
	_str[_size] = '\0';
}


void Gerald::String::append(const char *str)
{
	int len = strlen(str);
	if (_size + len > _capacity)
	{
		reserve(_size + len);
	}

	strcpy(_str + _size, str);
	_size += len;
}


Gerald::String& Gerald::String::operator+= (char ch)
{
	push_back(ch);
	return *this;
}


Gerald::String& Gerald::String::operator+= (const char *str)
{
	append(str);
	return *this;
}


size_t Gerald::String::find(char ch, size_t pos)
{
	assert(pos < _size);

	for (pos; pos < _size; pos++)
	{
		if (_str[pos] == ch)
			return pos;
	}

	return npos;
}
size_t Gerald::String::find(const char *str, size_t pos)
{
	assert(pos < _size);

	char *pstr = strstr(_str, str);
	if (pstr)
	{
		return pstr - str;
	}

	return npos;
}


void Gerald::String::Insert(size_t pos, const char ch)
{

	if (_size == _capacity)//_size位置放的是'\0'要统一
	{
		size_t new_size = _capacity == 0 ? 15 : 2 * _capacity;
		reserve(new_size);
	}

	size_t i = _size + 1; //这里+1可以在第一步直接将'\0'挪到最后面，所以在最后就不需要赋值'\0'了
	for (i; i > pos; i--)
	{
		_str[i] = _str[i - 1];
	}
	_str[pos] = ch;

	_size++;
}

void Gerald::String::Insert(size_t pos, const char *str)
{
	size_t len = strlen(str);
	if (_size + len > _capacity)
	{
		reserve(_size + len);
	}

	size_t i = _size + len;
	for (i; i > pos + len - 1; i--)  //i > pos + len - 1   极端位置 i = pos + len  可以把pos位置的数据挪过来
	{								//就算在字符串尾部插入，循环还是会把'\0'挪到最后面，不用担心最后没有加'\0'的问题
		_str[i] = _str[i - len];
	}

	strncpy(_str + pos, str, len);
	_size += len;
	
}


void Gerald::String::Erase(size_t pos, size_t len)
{
	if (pos + len > _size)//直接将后面的字符串屏蔽
	{
		_str[pos] = '\0';
		_size = pos;
		return;
	}

	for (size_t i = pos; i < _size - len + 1; i++)//i < _size - len + 1可以直接将'\0'挪到缩减后的最后一个位置
	{
		_str[i] = _str[i + len];
	}

	_size -= len;
}


Gerald::String Gerald::String::substr(size_t pos, size_t len)
{
	if (_size - pos < len)
		len = _size - pos;

	String sub;
	sub.reserve(len);

	for (size_t i = pos; i < pos + len; i++)
	{
		sub += _str[i];
	}

	return sub;
}



std::ostream& Gerald::operator<<(std::ostream& _cout, const Gerald::String& str)
{
	for (auto& c : str)
	{
		_cout << c;
	}

	return _cout;
}