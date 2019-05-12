#pragma once
#include <iostream>
#include <mutex>

template <class T>
class SharedPtr
{
public:
    typedef T _data;
    typedef T* _pointer;
    typedef const T* _const_pointer;
    typedef T& _reference;
    typedef const T& _const_reference;

    //Member Function
    SharedPtr(const _pointer ptr = nullptr)
        :_ptr(ptr),
        _reference_count(new int(1)),
        _mutex(new std::mutex)
    {}

    SharedPtr(const SharedPtr& sp)
    {
        if (sp._ptr != nullptr)
        {
            _ptr = sp._ptr;
            _mutex = sp._mutex;
            _reference_count = sp._reference_count;
            AddReferenceCount();
        }
    }

    SharedPtr& operator=(const SharedPtr& sp)
    {
        if (_ptr != sp._ptr)
        {
            //先把当前指针指向的对象引用计数减1
            //如果减完为0，就释放对象
            if (SubReferenceCount() == 0)
            {
                delete _ptr;
                delete _reference_count;
                delete _mutex;
            }

            _ptr = sp._ptr;
            _reference_count = sp._reference_count;
            _mutex = sp._mutex;
            AddReferenceCount();
        }
    }

    ~SharedPtr()
    {
        if (SubReferenceCount() == 0)
        {
            delete _ptr;
            _ptr = nullptr;

            delete _reference_count;
            _reference_count = nullptr;

            delete _mutex;
            _mutex = nullptr;
        }
    }
    //end of member function//////////////////////////////////
    
    
    //Like Pointer//////////////////////////////////////////
    _reference operator*()
    {
        return *(_ptr);
    }

    _pointer operator->()
    {
        return _ptr;
    }

    int UseCount()
    {
        return *_reference_count;
    }


private:
    int AddReferenceCount()
    {
        _mutex->lock();
        (*_reference_count)++;
        _mutex->unlock();

        return *_reference_count;
    }

    int SubReferenceCount()
    {
        _mutex->lock();
        (*_reference_count)--;
        _mutex->unlock();

        return *_reference_count;
    }

private:
    _pointer _ptr;
    int* _reference_count;
    std::mutex* _mutex;
};
