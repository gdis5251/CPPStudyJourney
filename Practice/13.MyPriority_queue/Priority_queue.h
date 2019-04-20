#include <vector>
#include <iostream>
#include <algorithm>

template<class T>
class Greater
{
public:
    bool operator()(const T& a, const T& b)
    {
        return a > b;
    }
};

template<class T>
class Less
{
public:
    bool operator()(const T& a, const T& b)
    {
        return a < b;
    }
};

template<class T, class container = std::vector<T>, class compare = Greater<T> >
class Priority_queue
{
public:
    void push(const T& val)
    {
        _con.push_back(val);

        adjust_up(_con.size() - 1);
    }

    void adjust_up(size_t child)
    {
        compare _cmp;
        size_t parent = (child - 1) / 2;

        while (child > 0)
        {
            if (_cmp(_con[child], _con[parent]))
            {
                std::swap(_con[parent], _con[child]);
                child = parent;
                parent = (child - 1) / 2;
            }
            else
                break;
        }
    }

    void pop()
    {
        std::swap(_con[0], _con[_con.size() - 1]);

        _con.pop_back();
        adjust_down(0);
    }

    void adjust_down(size_t parent)
    {
        compare _cmp;
        size_t child = parent * 2 + 1;

        while (parent < _con.size())
        {
            if (child >= _con.size())
                break;

            if (child + 1 < _con.size() && _cmp(_con[child + 1], _con[child]))
                child++;

            if (_cmp(_con[child], _con[parent]))
            {
                std::swap(_con[parent], _con[child]);
                parent = child;
                child = parent * 2 + 1;
            }
            else
                break;
        }

    }

    bool empty()
    {
        return _con.empty();
    }

    T& top()
    {
        return _con[0];
    }

private:
    container _con;
};
