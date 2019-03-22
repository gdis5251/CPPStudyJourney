#ifndef _STRING_H_
#define _STRING_H_

#include <iostream>
#include <assert.h>

#pragma warning(disable:4996)

namespace Gerald
{
	class String
	{
	public:

		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		String(const char *str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}


		~String()
		{
			if (_str)
			{
				delete[] _str;
			}
		}


		String(const char& str)
			:_str(nullptr),
			_size(0),
			_capacity(0)
		{
			String tmp(str);
			Swap(tmp);
		}


		String& operator=(String s)
		{
			Swap(s);
			return *this;
		}

		void push_back(char ch);
		void append(const char *str);
		String& operator+= (char ch);
		String& operator+= (const char *str);
		size_t find(char ch, size_t pos = 0);
		size_t find(const char *str, size_t pos = 0);
		void Insert(size_t pos, char ch);
		void Insert(size_t pos, const char *str);
		void Erase(size_t pos, size_t len = npos);
		void Swap(String& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		char *c_str()
		{
			return _str;
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}


		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}


		size_t size() const
		{
			return _size;
		}


		size_t capacity() const
		{
			return _capacity;
		}


		void reserve(size_t n);
		void resize(size_t n, char ch = '\0');


	private:
		char *_str;
		size_t _size;
		size_t _capacity;
		static const size_t npos;
	};

	//const size_t String::npos = -1;
}

#endif //_STRING_H_