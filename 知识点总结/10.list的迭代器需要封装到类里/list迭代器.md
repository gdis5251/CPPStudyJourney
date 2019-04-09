# list容器的迭代器

> list不同于其他容器，他是一个链表，物理地址并不连续。所以在实现list类的迭代器的时候，需要将迭代器单独封装到一个类里，因为需要重载很多操作符来跟其他容器的迭代器使用达成一致

**list迭代器：**

1. **完成元素访问，具有类似于指针的++，--， *， !=, ==这些操作**
2. **对于链表，结点之间的空间不连续，原生指针++，--不能移动到下一个结点的位置，迭代器不能用原生指针来实现**
3. **故通过封装结点间接实现迭代器的相关操作：**
   - **++， --:通过结点的->next, ->prev:clown_face:**
   - ***:通过获取结点数据:fallen_leaf:**
   - **!=、==:通过判断结点的地址是否相等:cowboy_hat_face:**

```cpp
//iterator class 
template<class T>
struct _ListIterator
{
    typedef ListNode<T> Node;
    typedef _ListIterator<T> iterator;
    Node *_node;
    
    _ListIterator(Node *node)
        :_node(node)
    {}

    T& operator*()
    {
        return _node->_date;
    }
    
    T* operator->()
    {
        return &_node->_data;
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
```

**对于前置++和后置++：**

> 编译器通过参数(int)来判断是前置++ 还是后置++

> 有（int）是后置++

---

### const迭代器

> iterator 和 const_iterator唯一的不同的地方在于：操作符 * 和 -> 返回值不同

> iterator的 * 和 -> 操作符是可读可写的操作，返回值不加const。

> const_iterator的 * 和 -> 操作符只是可读的操作，返回值加const。

**但是普通迭代器和const迭代器唯一不同的就是在于上面那两个函数的返回值不同而已，所以，只要在泛类里加两个类型就行。**

```cpp
//iterator class 
template<class T, class Ref, class Ptr>
struct _ListIterator
{
    typedef ListNode<T> Node;
    typedef _ListIterator<T, T&, T*> iterator;
    Node *_node;
    
    ......
    
    Ref operator*()
    {
        return _node->_date;
    }
    
    Ptr operator->()
    {
        return &_node->_date;
    }

   	......
};
// end of iterator class 

```

