#pragma once
#include <iostream>

namespace Gerald
{
template<class T>
struct ListNode
{
    T _date;
    ListNode<T>* _next;
    ListNode<T>* _prev;

    ListNode(const T& data = T())
        :_date(data)
        ,_next(nullptr)
        ,_prev(nullptr)
    {}

};

//iterator class 
template<class T, class Ref, class Ptr>
struct _ListIterator
{
    typedef ListNode<T> Node;
    typedef _ListIterator<T, T&, T*> iterator;
    Node *_node;
    
    _ListIterator(Node *node)
        :_node(node)
    {}


    Ref operator*()
    {
        return _node->_date;
    }
    
    Ptr operator->()
    {
        return &_node->_date;
    }

    iterator& operator++()
    {
        _node = _node->_next;
        return *this;
    }

    iterator operator++(int)//The compiler according to int to judgement preposition or postposition
    {
        iterator oldit(*this);

        _node = _node->_next;
        return oldit;
    }

    iterator& operator--()
    {
        _node = _node->_prev;
        return *this;
    }

    iterator operator--(int)
    {
        iterator oldit(*this);

        _node = _node->_prev;
        return oldit;
    }

    bool operator!=(const iterator& it)
    {
        return _node != it._node;
    }

    iterator operator-(size_t step)
    {
        iterator cur = *this;

        while (step)
        {
            --cur;
            step--;
        }

        return cur;
    }

    iterator operator+(size_t step)
    {
        iterator cur = *this;
        while (step)
        {
            ++cur;
            step--;
        }

        return cur;
    }
};
// end of iterator class 

template<class T>
class List
{
    typedef ListNode<T> Node;
public:
    //iterator 
    typedef _ListIterator<T, T&, T*> iterator;
    typedef _ListIterator<T, const T&, const T*> const_iterator;
  
    iterator begin()
    {
        return iterator(_head->_next);
    }

    iterator end()
    {
        return iterator(_head);
    }

    const iterator begin() const
    {
        return iterator(_head->_next);
    }

    const iterator end() const
    {
        return iterator(_head);
    }
    //end of iterator
    //
    //Member function
    List(const T& val = T())
        :_head(new Node(val))
    {
        _head->_next = _head;
        _head->_prev = _head;
    }


    List(const List<T>& l, const T& val = T())
        :_head(new Node(val))
    {
        _head->_next = _head;
        _head->_prev = _head;
       
        iterator lit = l.begin();
        while (lit != l.end())
        {
            push_back(*lit);
            ++lit;
        }
    }


    List<T> operator=(List<T> l)
    {
        Node *tail = l._head->_prev;

        _head->_next = l._head->_next;
        l._head->_next->_prev = _head;
        _head->_prev = tail;
        tail->_next = _head;
        
        l._head->_next = l._head;
        l._head->_prev = l._head;

        return *this;
    }


    ~List()
    {
        if (_head->_next != _head)
        {
            Node *node = _head->_next;
            while (node != _head)
            {
                Node *next = node->_next;
                delete node;
                node = next;
            }
        }

        delete _head;
        _head = nullptr;
    }

    //end of Member function
    //
    //
    //Modify function  
    void push_back(const T& val)
    {
     //   Node *newNode = new Node(val);
     //   Node *tail = _head->_prev;

     //   tail->_next = newNode;
     //   newNode->_prev = tail;
     //   _head->_prev = newNode;
     //   newNode->_next = _head;
     
        insert(end(), val);
    }


    void pop_back()
    {
        erase(end() - 1);
    }


    void push_front(const T& val)
    {
        insert(begin(), val);
    }


    void pop_front()
    {
        erase(begin());
    }


    void insert(iterator pos, const T& val)
    {
        Node *newNode = new Node(val);
        Node *prev = pos._node->_prev;
        Node *cur = pos._node;

        newNode->_next = cur;
        newNode->_prev = prev;
        prev->_next = newNode;
        cur->_prev = newNode;
        
    }


    iterator erase(iterator pos)
    {
        Node *prev = pos._node->_prev;
        Node *next = pos._node->_next;

        prev->_next = next;
        next->_prev = prev;

        delete pos._node;
        pos._node = nullptr;

        return next;
    }


    size_t size()
    {
        iterator it = begin();
        size_t count = 0;

        while (it != end())
        {
            ++it;
            ++count;
        }

        return count;
    }


    bool empty()
    {
        if (_head->_next == _head)
            return true;

        return false;
    }

    void clear()
    {
        if (_head)
        {
            Node *cur = _head->_next;
            while (cur != _head)
            {
                Node *_next = cur->_next;
                delete cur;
                cur = _next;
            }
        }

        _head->_next = _head;
        _head->_prev = _head;
    }

private:
    Node* _head;
};
}
