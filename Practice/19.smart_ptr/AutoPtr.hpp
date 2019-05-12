#pragma once
#include <iostream>

template <class T>
class AutoPtr
{
public:
    typedef T _data;
    typedef T* _pointer;
    typedef const T* _const_pointer;
    typedef T& _reference;
    typedef const T& _const_reference;

    //Member Function
    AutoPtr(const _pointer ptr = nullptr)
        :_ptr(ptr)
    {}

    AutoPtr(AutoPtr& ap)
        :_ptr(ap._ptr)
    {
        ap._ptr = nullptr;
    }

    AutoPtr& operator=(AutoPtr& ap)
    {
        if (this != ap)
        {
            delete _ptr;
            _ptr = ap._ptr;
            ap._ptr = nullptr;
        }
    }

    ~AutoPtr()
    {
        if (_ptr)
        {
            delete _ptr;
            _ptr = nullptr;
        }
    }
    //End of Member Function
    
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
    _pointer _ptr;
};
