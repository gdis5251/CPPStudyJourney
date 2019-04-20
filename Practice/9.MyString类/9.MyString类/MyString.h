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

		friend std::ostream& operator<<(std::ostream& cout, const String& str);


		//iterator//////////////////
		//作用
		//1. 实现类似于指针的解引用操作哦
		//2. 实现类似于指针的位置移动操作 ++ --
		//3. begin（）返回元素的第一个位置
		//4. end（）返回最后一个元素下一个位置
		//5. 迭代器要具有 == !=  的操作逻辑，但是不能比较大小（因为不一定所有数据是按一定物理次序而存的）
		
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

		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}
		//////////////////////////

		//Member functions//////////////////////////
		String(const char *str = "")
		{
			_size = strlen(str);
			_capacity = _size > 15 ? _size : 15;
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
		/////////////////////////////////////////////

		//Modify////////////////////////////////////
		void push_back(char ch);
		void append(const char *str);
		String& operator+= (char ch);
		String& operator+= (const char *str);
		size_t find(char ch, size_t pos = 0);
		size_t find(const char *str, size_t pos = 0);
		void Insert(size_t pos, const char ch);
		void Insert(size_t pos, const char *str);
		void Erase(size_t pos, size_t len = npos);
		String substr(size_t pos, size_t len = npos);

		
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

		Gerald::String operator+(const Gerald::String& s2);
		String operator+(const char* s2);
		String operator+(const String& s2);


		////////////////////////////

	private:
		char *_str;
		size_t _size;
		size_t _capacity;

	public:
		static const size_t npos;

	};
}
#endif //_STRING_H_