# shared_ptr循环复用问题

## 什么是shared_ptr?

`shared_ptr`是一个只能指针，但是它区别于`auto_ptrd`的管理权转移（进行拷贝构造或赋值操作时，原指针会被释放）和`unique_ptr`的不可以进行拷贝构造和赋值操作。`shared_ptr`采用引用计数的方式来管理一个指针，可以让多个`shared_ptr`对象指向同一个地址，当没有指向的时候才释放，这也算是智能指针里面最好用的一个了。

## 描述问题：

虽然`shared_ptr`很强大，但是还是有一些缺陷的，那就是今天要说的循环复用问题。

看例子：

```cpp
#include <iostream>
#include <memory>

struct ListNode
{
    int value;
    std::shared_ptr<ListNode> _next;
    std::shared_ptr<ListNode> _prev;

    ~ListNode()
    {
        std::cout << "~ListNode" << std::endl;
    }
};

int main(void)
{
    std::shared_ptr<ListNode> p1(new ListNode());
    std::shared_ptr<ListNode> p2(new ListNode());

    p1->_next = p2;
    p2->_prev = p1;

    return 0;
}

```

![1](F:\CPPStudyJourney\Summary\18.shared_ptr循环复用问题\1.png)

首先结果是并没有释放两个`ListNode`申请的内存，造成了内存泄漏。那么到底为什么呢？我来画个图来帮助理解：

![2](F:\CPPStudyJourney\Summary\18.shared_ptr循环复用问题\2.png)

- 首先创建了两个对象p1 p2 然后他们的引用数都为1。
- 然后这两个结点内部的`shared_ptr`指针互相指了一下，所以他们的引用数又都增加了1，变成了2。
- 当程序运行结束，p1 p2 会因为出作用域而调用析构函数，但是这两个结点的引用计数都是2，p1 p2 调用析构函数后，这两个结点的引用计数变为1。
- 根据`shared_ptr`的规则，当引用计数为0时才会释放对象，所以这里就造成了内存泄漏问题。

## 解决方法！

C++标准库里还提供了一个叫做`weak_ptr`的智能指针，是专门为了解决`shared_ptr`的循环复用问题而存在的。因为`weak_ptr`不会增加引用计数，所以当两个结点互指的时候，p1 p2的引用计数还是1。这样就不会造成内存泄漏了。

```cpp
#include <iostream>
#include <memory>

struct ListNode
{
    int value;
    std::weak_ptr<ListNode> _next;
    std::weak_ptr<ListNode> _prev;

    ~ListNode()
    {
        std::cout << "~ListNode" << std::endl;
    }
};

int main(void)
{
    std::shared_ptr<ListNode> p1(new ListNode());
    std::shared_ptr<ListNode> p2(new ListNode());

    p1->_next = p2;
    p2->_prev = p1;

    return 0;
}

```

![TIM截图20190512204742](F:\CPPStudyJourney\Summary\18.shared_ptr循环复用问题\TIM截图20190512204742.png)



叮~:bell: