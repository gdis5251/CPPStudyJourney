#pragma once
#include <iostream>

template <class T>
class AutoPtr
{
public:
    AutoPtr(T* ptr = nullptr)
        :ptr_(ptr)
    {}

    ~AutoPtr()
    {
        if (ptr_ != nullptr)
        {
            delete ptr_;
        }
    }

    // 使用权转移
    AutoPtr (AutoPtr& auto_ptr)
        :ptr_(auto_ptr.ptr_)
    {
        auto_ptr.ptr_ = nullptr;
    }

    AutoPtr& operator=(AutoPtr& auto_ptr)
    {
        // 判断是否是自己给自己赋值
        if (this != auto_ptr)
        {
            if (ptr_ != nullptr)
            {
                delete ptr_;
            }

            ptr_ = auto_ptr.ptr_;
            auto_ptr.ptr_ = nullptr;
        }
        return *this;
    }

    // 像指针一样
    T& operator*()
    {
        return *ptr_;
    }

    T* operator->()
    {
        return ptr_;
    }

    T* operator++()
    {
        return ++ptr_;
    }

    bool operator==(const T* ptr)
    {
        return ptr_ == ptr;
    }
private:
    T* ptr_;
};
