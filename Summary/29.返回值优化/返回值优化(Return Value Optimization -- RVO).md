# 返回值优化(Return Value Optimization -- RVO)

在日常开发中，我们不得不会遇到返回对象的情况。那么对于 **追求效率** 的程序员来说，返回对象是一件很痛苦的事情。

### 举个栗子:chestnut:

考虑这样的一种情况：分数相乘

有这么一个分数类：

```cpp
#include <iostream>

class Rational {
public:    
    Rational (int numerator = 0, int denominator = 1);
	...
    int numerator() const;
    int denominator() const;
};

```

那么 ```operator*```应该是这样的

```cpp
const Rational operator*(const Rational& lhs, const Rational& rhs);
```

这个情况下，就算我们看不到函数内容，我们都知道应该是返回对象的。因为是两个任意的数相乘，没有办法在不构造新对象的情况下返回结果。



**错误一：返回指针**

有些人可能会想到在函数内部动态开辟一段空间，在这个空间上构造一次对象，然后返回指针就可以了，这样就可以避免在返回的时候又要构造临时对象的开销。

但是，如果动态开辟空间，那么在 C/C++ 中是要手动释放的，如果程序员忘记释放内存，就会造成内存泄漏的问题。所以这个方法是不可取的。



**错误二：返回引用**

如果说返回指针是一个不妥的行为，那么返回引用就是一个滑稽的行为。

因为如果你返回在函数内部构造的对象的引用。那么当这个函数结束后，编译器会自动销毁对象，那么用户拿到的就只是一个被销毁的对象，产生的行为就是未定义行为。



那么应该怎么样去设计这个函数在保证安全的情况下又能让效率最大？

```cpp
const Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator * rhs.denominator())
}
```

这样看上去仅仅是构造了一个临时对象然后返回。难道不是还需要编译器销毁该对象，再构造匿名临时对象返回吗？

但是 C++ 允许编译器将临时对象优化，使它们不存在。你的编译器可以将 return 表达式所定义的对象构造于 C 的内存中。那么这样你就只需要一次构造就可以啦。

这种方法叫做 Return Value Optimization 简称 RVO。

叮~:bell:

