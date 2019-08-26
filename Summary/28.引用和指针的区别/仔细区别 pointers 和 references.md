# 仔细区别 pointers 和 references

> 参考《More Effective C++》

## 没有所谓的 null references

一个引用必须总代表某个对象。所以如果有一个变量，其目的是用来指向（代表）另一个对象，但是也有可能他不指向（代表）任何对象，那么你应该使用 **pointers**，因为你可以将 **pointers** 设为 **null**。换句话说，如果一个变量总是代表一个对象，也就是不能使这个变量为 **null**，那么你应该使用 **references**。

**以下是某种未定义行为：**

```cpp
char* p = nullptr;
char& rp = *p;
```

这是一种未定义行为，编译器可能会产生任何可能的输出。

> 《More Effective C++》的作者说，写出这种代码的人，应该与世隔绝。

## references 必须初始化

在定义引用变量的时候，一定要初始化，不然编译器会报错。而指针可以不进行初始化。

正因为如此，有的时候 **references** 会比 **pointers** 的效率高。

**举个**:chestnut:

```cpp
void PrintSliegman(const int& Sliegman)
{
    std::cout << Sliegman << std::endl;
}

void PrintSliegman(const int* Sliegman)
{
    if (nullptr != Sliegman)
    {
	    std::cout << *Sliegman << std::endl;
    }
}
```

如果使用 **pointers** 还要进行一步判断操作，因为 **pointers** 有可能指向 **null**，而使用引用就可以直接打印，因为它一定指向某个 **int** 类型的数据。

## pointers 可以被重新赋值

因为 **references** 总是代表某一个对象，所以它不可以重新赋值，但是 **pointers** 可以。

一般来说，当你考虑到你有可能不指向任何对象的时候或者在不同时刻指向不同的对象的时候，要使用 **pointers**。而当你确定“总是指向某一个对象”，而且“一旦代表了该对象就不能够再改变”，那么你应该使用 **references**。

## 某些特殊情况

例如 **operator[]** 的时候要返回引用而不是指针，这种操作符很特别的必须返回某种“能够被当做 **assignment** 赋值对象”的东西:

``` std::vector<int> a;``` 

当你想访问某个值的时候，你会进行 [] 操作。

``` a[1] = 999;```

可是如果你返回指针的话，就会变成这样：

``` *a[1] = 999;```

这看起来就很别扭，所以这种情况下就需要返回一个 **references**。

## 常规区别

- 指针++ 是指针向后偏移一个类型的字节，而 引用++ 就是代表的值++
- sizeof(指针) 是指针的大小，32位平台下指针占4个字节，64位平台下指针占8个字节。而sizeof(引用) 表示引用代表的值得大小。
- 有多级指针，没有多级引用
- 访问实体的时候，指针需要显示解引用，引用编译器自己处理。
- 引用比指针相对安全

叮~:bell: