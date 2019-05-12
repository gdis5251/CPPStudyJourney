#pragma once
#include <iostream>

template <class T>
class UniquePtr
{
public:
    typedef T _data;
    typedef T* _pointer;
    typedef const T* _const_pointer;
    typedef T& _reference;
    typedef const T& _const_reference;

    //Member Function
    UniquePtr(const _pointer ptr = nullptr)
        :_ptr(ptr)
    {}

    ~UniquePtr()
    {
        if (_ptr)
        {
            delete _ptr;
            _ptr = nullptr;
        }
    }
    //end of member function
    
    //Like Pointer
    _reference operator*()
    {
        return *(_ptr);
    }

    _pointer operator->()
    {
        return _ptr;
    }
private:
    UniquePtr(UniquePtr& up) = delete;
    UniquePtr(const UniquePtr& up) = delete;
    UniquePtr& operator=(UniquePtr& up) = delete;
    UniquePtr& operator=(const UniquePtr& up) = delete;


private:
    _pointer _ptr;

};
