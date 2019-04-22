# C++ priority_queue

### 1. priority_queue的概念

1. 优先队列是一种容器适配器，根据严格的弱排序标准，它的第一个元素总是它所包含的元素中最大的。
2. 此上下文类似于堆，在堆中可以随时插入元素，并且只能检索最大堆元素(优先队列中位于顶部的元
  素)。
3. 优先队列被实现为容器适配器，容器适配器即将特定容器类封装作为其底层容器类，queue提供一组特定的成员函数来访问其元素。元素从特定容器的“尾部”弹出，其称为优先队列的顶部。
4. 底层容器可以是任何标准容器类模板，也可以是其他特定设计的容器类。容器应该可以通过随机访问迭代器访问，并支持以下操作：
  empty()：检测容器是否为空
  size()：返回容器中有效元素个数
  front()：返回容器中第一个元素的引用
  push_back()：在容器尾部插入元素
  pop_back()：删除容器尾部元素
5. 标准容器类vector和deque满足这些需求。默认情况下，如果没有为特定的priority_queue类实例化指定容器类，则使用vector。
6. 需要支持随机访问迭代器，以便始终在内部保持堆结构。容器适配器通过在需要时自动调用算法函数
  make_heap、push_heap和pop_heap来自动完成此操作。

> [priority_queue详情](http://www.cplusplus.com/reference/queue/priority_queue/?kw=priority_queue )

### 2. priority_queue的使用

> 优先级队列默认使用vector作为其底层存储数据的容器，在vector上又使用了堆算法将vector中元素构造成堆的结构，因此priority_queue就是堆，所有需要用到堆的位置，都可以考虑使用priority_queue。
>
> **注意：**
> **默认情况下priority_queue是大堆**

priority_queue是一个容器，那么它就应该有各种接口供我们调用。

![微信截图_20190410140501](F:\CPPStudyJourney\Summary\12.stack_queue\微信截图_20190410140501.png)

```cpp
#include <iostream>
#include <functional>
#include <queue>
#include <vector>


int main(void)
{
    std::priority_queue<int> pq;
    std::vector<int> v;
    
    v.push_back(1);
    v.push_back(8);
    v.push_back(3);
    v.push_back(6);
    v.push_back(2);
    v.push_back(4);
    for(const auto& e : v)
    {
        pq.push(e);
    }

    std::cout << pq.top() << std::endl;

    std::priority_queue<int, std::vector<int>, std::greater<int> > pq1(v.begin(), v.end());
    std::cout << pq1.top() << std::endl;

    return 0;
}
```

