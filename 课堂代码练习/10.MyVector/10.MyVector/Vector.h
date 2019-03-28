#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <assert.h>

namespace Gerald
{
	template<class T>
	class Vector
	{
	public:
		//Member Function/////////////////////////////////////////
		Vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}

		//构造的时候放进去n个val
		//这里存在一个问题
		//如果在调用这个函数的时候，传两个int类型的，会自动调用下面的构造函数，发生解引用错误
		explicit Vector(size_t n, const T& val = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			reserve(n);

			while (n--)
			{
				push_back(val);
			}

		}

		template<class InputIterator>
		Vector(InputIterator first, InputIterator last)
		{
			reserve(last - first);

			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}


		~Vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _endofstorage = nullptr;
			}
		}



		Vector(const Vector<T>& v)
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{
			reserve(v.capacity());

			iterator it = begin();
			const_iterator vit = v.begin();

			while (vit != v.end())
			{
				*it++ = *vit++;
			}

			_finish = _start + v.size();
		}


		Vector<T> operator=(const Vector<T> v)
		{
			swap(v);
			return *this;
		}
		////////////////////////////////////////////////////////

		//iterator/////////////////////////////////////////////
		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
		{
			return _finish;
		}
		///////////////////////////////////////////////////////

		//Modify//////////////////////////////////////////////
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				T* tmp = new T[n];

				if (_start)
					memcpy(tmp, _start, sizeof(T) * sz);

				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}


		void resize(size_t n, const T& val = T())
		{
			if (n < size())
			{
				_finish = _start + n;
				return;
			}
			
			if (n > capacity())
			{
				reserve(n);
			}

			iterator it = _finish;
			iterator finish = _start + n;

			while (it != finish)
			{
				*it = val;
				++it;
			}
		}


		void push_back(const T& x)
		{
			insert(_finish, x);
		}


		void pop_back()
		{
			erase(_finish - 1);
		}


		//因为插入有可能会导致迭代器失效
		//所以要返回pos
		iterator insert(iterator pos, const T& x)
		{
			assert(pos <= _finish);

			if (_finish == _endofstorage)
			{
				size_t new_pos = pos - _start;
				size_t new_capacity = capacity() == 0 ? 1 : capacity() * 2;
				reserve(new_capacity);

				pos = _start + new_pos;
			}

			iterator begin = _finish;
			while (begin != pos)
			{
				*begin = *(begin - 1);
				begin--;
			}

			*pos = x;
			_finish++;
			return pos;
		}


		iterator erase(iterator pos)
		{
			size_t new_pos = pos - _start;

			iterator begin = pos;
			while (begin != _finish)
			{
				*begin = *(begin + 1);
				begin++;
			}

			_finish--;
			pos = _start + new_pos;

			return pos;
		}


		size_t size() const
		{
			return (_finish - _start);
		}

		size_t capacity() const
		{
			return (_endofstorage - _start);
		}

		T& operator[](size_t pos)
		{
			assert(pos < size());
			return _start[pos];
		}

		T& operator[](size_t pos) const
		{
			assert(pos < size());
			return _start[pos];
		}
		/////////////////////////////////////////////////////////////

		//swap//////////////////////////////////////////////////////
		void swap(const T& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}

		//////////////////////////////////////////////////////////////
	private:
		/*T* _start;
		T* _finish;
		T* _endofstorage;*/
		
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};
}