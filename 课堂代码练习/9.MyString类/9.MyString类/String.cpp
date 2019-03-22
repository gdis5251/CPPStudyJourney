#include "MyString.h"


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
		while (_size < n)
		{
			push_back(ch);
		}

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

	return -1;
}
size_t Gerald::String::find(const char *str, size_t pos)
{
	assert(pos < _size);

	char *pstr = strstr(_str, str);
	if (pstr)
	{
		return pstr - str;
	}

	return -1;
}


void Gerald::String::Insert(size_t pos, char ch)
{

	if (_size == _capacity)
		reserve(2 * _capacity);

	if (pos == _size)
	{
		push_back(ch);
	}
	else if (pos < _size)
	{
		size_t i = _size;
		for (i; i > pos; i--)
		{
			_str[i] = _str[i - 1];
		}
		_str[pos] = ch;

		_size++;
		_str[_size] = '\0';
	}

}


void Gerald::String::Insert(size_t pos, const char *str)
{
	size_t len = strlen(str);
	if (_size + len > _capacity)
	{
		reserve(_size + len);
	}

	if (pos == _size)
	{
		*this += str;
	}
	else if (pos < _size)
	{
		size_t i = _size + len;
		for (i; i > pos + len - 1; i--)
		{
			_str[i] = _str[i - len];
		}
		strncpy(_str + pos, str, len);
		_size += len;
	}
}


void Gerald::String::Erase(size_t pos, size_t len)
{
	for (size_t i = pos; i < _size - len; i++)
	{
		_str[i] = _str[i + len];
	}

	_size -= len;
	_str[_size] = '\0';
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