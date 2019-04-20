#include <deque>
#include <list>
#include <iostream>


template<class T, class container = std::deque<T> >
class Queue
{
public:
    void push(const T& val)
    {
        _con.push_back(val);
    }

    void pop()
    {
        _con.pop_front();
    }

    T& front()
    {
        return _con.front();
    }

    size_t size()
    {
        return _con.size();
    }

    bool empty()
    {
        return _con.empty();
    }

    T& back()
    {
        return _con.back();
    }

//    void display() const
//    {
//        for (const auto& e : _con)
//        {
//            std::cout << e << " ";
//        }
//
//        std::cout << std::endl;
//    }
private:
    container _con;
};

