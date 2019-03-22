#ifndef _STRING_H_
#define _STRING_H_

#include <assert.h>
#include <string>

#pragma warning(disable:4996)

namespace Gerald
{
	class String
	{
	public:

		//iterator//////////////////
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
		//////////////////////////

		//Member functions
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
				_str = nullptr;
				_size = 0;
				_capacity = 0;
			}
		}


		String(const String& s)
			:_str(nullptr),
			_size(0),
			_capacity(0)
		{
			String tmp(s._str);
			Swap(tmp);
		}


		String& operator=(String s)
		{
			Swap(s);
			return *this;
		}
		/////////////////

		//Modify
		void push_back(char ch);
		void append(const char *str);
		String& operator+= (char ch);
		String& operator+= (const char *str);
		size_t find(char ch, size_t pos = 0);
		size_t find(const char *str, size_t pos = 0);
		void Insert(size_t pos, char ch);
		void Insert(size_t pos, const char *str);
		void Erase(size_t pos, size_t len = -1);
		String substr(size_t pos, size_t len = -1);
		
		void clear()
		{
			_size = 0;
			_str[0] = '\0';
		}
		
		int empty() const
		{
			if (_size == 0)
				return 1;

			return 0;
		}
		
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

	public:
		static const size_t npos;

	};
	const size_t Gerald::String::npos = -1;
}

#endif //_STRING_H_