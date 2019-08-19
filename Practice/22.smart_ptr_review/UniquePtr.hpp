#pragma once

template <class T>
class UniquePtr
{
public:
    UniquePtr(T* ptr)
        :ptr_(ptr)
    {}

    ~UniquePtr() 
    {
        if (ptr_ != nullptr)
        {
            delete ptr_;
        }
    }

    T& operator*()
    {
        return *ptr_;
    }

    T* operator->()
    {
        return ptr_;
    }
private:
    UniquePtr(const UniquePtr<T>&) = delete;
    UniquePtr& operator=(const UniquePtr<T>&) = delete;

    T* ptr_;
};

