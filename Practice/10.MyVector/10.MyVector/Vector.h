#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <assert.h>



//type  traits////////////////////////////////////////////////////
// ������������
struct __true_type {};
// �����Զ�������
struct __false_type {};
template <class type>
struct __type_traits
{
	typedef __false_type is_POD_type;
};
// �������������ͽ����ػ�
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
// ע�⣺��������������ʱ�����е��������Ͷ��������س����������з��ź��޷��ţ����磺����int���ͣ���
//���ػ�������int-- signed int -- unsigned int
// ����Ҫ���������������Զ������͵�λ�ã���׼��ͨ������ͨ��__true_type��__false_type����һ������
//��
// ������Ȼ����һ��ͨ�ú���������з�װ
// ע�⣺�������������Բ��ṩ���֣��ò�������Ҫ�����þ���������_copy�����γ�����
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

		//�����ʱ��Ž�ȥn��val
		//�������һ������
		//����ڵ������������ʱ�򣬴�����int���͵ģ����Զ���������Ĺ��캯�������������ô���
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
			////���
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
					//memcpy(tmp, _start, sizeof(T) * sz);//ǳ����
					//��� ����T���͵ĸ�ֵ���������
					
					/*for (int i = 0; i < size(); i++)
						tmp[i] = _start[i];*/
					//������������������ȡ��ѡ�񵽵�ʹ�����ֿ�����ʽ 
					
					//������ȡ
					//Ȼ���ھ������������ǳ����
					Copy(tmp, _start, size());
				
					delete[] _start;	
					/*
						����string����
						memcpy�ǰ��ֽڿ���
						������string�����ָ��
						����˵��һ���ͷŵ�ʱ���Ѿ�����ǰstring���е������ͷ���
						�����β��룬�ٴ��ͷſռ��ʱ��
						����ڶ����ͷ�
						���Իᱨ��
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


		//��Ϊ�����п��ܻᵼ�µ�����ʧЧ
		//����Ҫ����pos
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


		//erase���µ�����ʧЧ
		//��ȡerase�ķ���ֵ�����µ�����
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