#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <assert.h>



//type  traits////////////////////////////////////////////////////
// 代表内置类型
struct __true_type {};
// 代表自定义类型
struct __false_type {};
template <class type>
struct __type_traits
{
	typedef __false_type is_POD_type;
};
// 对所有内置类型进行特化
template<>
struct __type_traits<char>
{
	typedef __true_type is_POD_type;
};
template<>
struct __type_traits<signed char>
{
	typedef __true_type is_POD_type;
};
template<>
struct __type_traits<unsigned char>
{
	typedef __true_type is_POD_type;
};
template<>
struct __type_traits<int>
{
	typedef __true_type is_POD_type;
};
template<>
struct __type_traits<float>
{
	typedef __true_type is_POD_type;
};
template<>
struct __type_traits<double>
{
	typedef __true_type is_POD_type;
};
// 注意：在重载内置类型时，所有的内置类型都必须重载出来，包括有符号和无符号，比如：对于int类型，必
//须特化三个，int-- signed int -- unsigned int
// 在需要区分内置类型与自定义类型的位置，标准库通常都是通过__true_type与__false_type给出一对重载
//的
// 函数，然后用一个通用函数对其进行封装
// 注意：第三个参数可以不提供名字，该参数最主要的作用就是让两个_copy函数形成重载
template<class T>
void _copy(T* dst, T* src, size_t n, __true_type)
{
	memcpy(dst, src, n * sizeof(T));
}
template<class T>
void _copy(T* dst, T* src, size_t n, __false_type)
{
	for (size_t i = 0; i < n; ++i)
		dst[i] = src[i];
}
template<class T>
void Copy(T* dst, T* src, size_t n)
{
	_copy(dst, src, n, __type_traits<T>::is_POD_type());
}
//end of type traits//////////////////////////////////////////////////


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
		explicit Vector(int n, const T& val = T())
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


			Copy(_start, v._start, v.size());
			//iterator it = begin();
			//const_iterator vit = v.begin();

			//
			////深拷贝
			//while (vit != v.end())
			//{
			//	*it++ = *vit++;
			//}

			_finish = _start + v.size();
		}


		Vector<T>& operator=(const Vector<T> v)
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
				{
					//memcpy(tmp, _start, sizeof(T) * sz);//浅拷贝
					//深拷贝 调用T类型的赋值运算符重载
					
					/*for (int i = 0; i < size(); i++)
						tmp[i] = _start[i];*/
					//这里拷贝可以用类型萃取来选择到底使用哪种拷贝方式 
					
					//类型萃取
					//然后在决定是深拷贝还是浅拷贝
					Copy(tmp, _start, size());
				
					delete[] _start;	
					/*
						对于string对象
						memcpy是按字节拷贝
						拷贝了string对象的指针
						等于说第一次释放的时候已经将当前string已有的内容释放了
						第三次插入，再次释放空间的时候
						会存在二次释放
						所以会报错
					*/
				}
				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}


		void resize(size_t n, const T& val = T())
		{
			if (n <= size())
			{
				_finish = _start + n;
				return;
			}
			
			if (n > capacity())
			{
				reserve(n);
			}

		
			while (_finish != _start + n)
			{
				*_finish = val;
				++_finish;
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
		void insert(iterator pos, const T& x)
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
		}


		//erase导致迭代器失效
		//获取erase的返回值，更新迭代器
		iterator erase(iterator pos)
		{
			iterator begin = pos;
			while (begin < _finish - 1)
			{
				*begin = *(begin + 1);
				begin++;
			}

			_finish--;

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
		void swap(Vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}

		//////////////////////////////////////////////////////////////

		//print///////////////////////////////////////////////////
		void printfVector()
		{
			Vector<T>::const_iterator it = begin();
			while (it != end())
			{
				std::cout << *it << " ";
				it++;
			}
			std::cout << std::endl;
		}
		///////////////////////////////////////////////////////////


	private:
		/*T* _start;
		T* _finish;
		T* _endofstorage;*/
		
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};
}