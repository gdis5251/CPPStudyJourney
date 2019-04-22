# c++ vector迭代器失效问题

> 在STL中，有很多的容器，对于每个容器的迭代器失效问题都不尽相同。

### 1. 扩容导致迭代器失效问题

在使用vector容器的insert接口时，可能会出现因扩容而导致的迭代器失效问题。

举个栗子：

![1](F:\\CPPStudyJourney\Summary\9. vector的迭代器失效问题\1.png)

这个时候，你要插入的只是一个元素，而_finish离 _endOfStorage还很远，那么只要pos <= _finish无论在任何地方插入都不会导致迭代器失效。

![3](F:\\CPPStudyJourney\Summary\9. vector的迭代器失效问题\3.png)

可是如果_finish == _endOfStorage的时候，在插入的时候就会触发扩容操作，扩容后会将原有空间释放，而pos迭代器作为一个指针，它并没有改变，所以在解引用的时候就会发生解引用错误。所以底层实现的时候会在函数里对pos进行更新，让她指向新空间旧逻辑位置。

![2](F:\\CPPStudyJourney\Summary\9. vector的迭代器失效问题\2.png)

这样就完成了插入操作。

下面代码演示，发生扩容后，原来旧的迭代器失效（本来想演示第二种情况没想到扩容了）

```cpp
#include <iostream>
#include <vector>

int main(void)
{
	int arr[] = { 1, 2, 3, 4 };
	std::vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));

	std::vector<int>::iterator it_begin = v1.begin();
	std::vector<int>::iterator it_end = v1.end() - 1;
	v1.insert(v1.begin() + 1, 10);

	std::cout << *it_begin << std::endl;
	std::cout << *it_end << std::endl;
	while (it_begin <= it_end)
	{
		std::cout << *it_begin << " ";
		it_begin++;
	}
	std::cout << std::endl;

	return 0;
}
```

insert前：

![6](F:\\CPPStudyJourney\Summary\9. vector的迭代器失效问题\6.png)

insert后：

![7](F:\\CPPStudyJourney\Summary\9. vector的迭代器失效问题\7.png)



### 2. 进行插入或删除操作会使我们当初定义的迭代器的含义与我们想要的出现偏差

这种情况就是非扩容的情况下，进行插入或删除的时候，有一些我们之前定义好的迭代器，由于数据元素的移动，它原本的含义与我们想要的出现偏差。

![4](F:\\CPPStudyJourney\Summary\9. vector的迭代器失效问题\4.png)

首先我们对一个vector先定义两个迭代器，it_begin, it_end分别指向第一个元素和最后一个元素。

![5](F:\\CPPStudyJourney\Summary\9. vector的迭代器失效问题\5.png)

然后我们在it_begin后面插入一个元素，但是我们现在看，it_begin并没有改变，但是原本我们以为指向最后一个元素的it_end却变成了指向倒数第二个元素。这样就引起了迭代器的含义与我们想要得出现了偏差，也就是说迭代器失效。

```cpp
#include <vector>
#include <iostream>

int main(void)
{
    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    
    std::vector<int>::iterator it_begin = v1.begin();
    std::vector<int>::iterator it_end = v1.end() - 1;
    while (it_begin <= it_end)
    {
        std::cout << *it_begin << " ";
        it_begin++;
    }
    std::cout << std::endl;
    it_begin = v1.begin();
    v1.insert(v1.begin() + 1, 10);

    std::cout << *it_begin << std::endl;
    std::cout << *it_end << std::endl;
    while (it_begin <= it_end)
    {
        std::cout << *it_begin << " ";
        it_begin++;
    }
    std::cout << std::endl;

    return 0;
}
```

![8](F:\\CPPStudyJourney\Summary\9. vector的迭代器失效问题\8.png)

erase也是这样。