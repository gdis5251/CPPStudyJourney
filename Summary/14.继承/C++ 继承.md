# C++ 继承

## 1.什么是继承

### 1.继承的概念：

> 继承(inheritance)机制是面向对象程序设计使代码可以复用的最重要的手段，它允许程序员在保持原有类特性的基础上进行扩展，增加功能，这样产生新的类，称派生类。继承呈现了面向对象程序设计的层次结构，体现了由简单到复杂的认知过程。以前我们接触的复用都是函数复用，继承是类设计层次的复用。

说白了，就是在一个基类的基础上，新定义一个类，这个新的类保留了基类除了private限定符内的所有东西并且，还多加了一些东西。这就叫做继承。

![1.继承的概念](F:\CPPStudyJourney\Summary\14.继承\1.继承的概念.png)

我们来看一个代码，稍微理解一下。

```cpp
//基类
class Person
{
public:
	Person(const std::string& name = "GeraldKwok", const size_t age = 21, const std::string& sex = "male")
		:_name(name),
		_age(age),
		_sex(sex)
	{}

	void print()
	{
		std::cout << "name: " << _name.c_str() << std::endl;
		std::cout << "age: " << _age << std::endl;
		std::cout << "sex: " << _sex.c_str() << std::endl;
	}

protected:
	std::string _name;
	size_t _age;
	std::string _sex;
};


//派生类
class Student : public Person
{
public:
	Student(const size_t sno = 110)
		:_sno(sno)
	{
	}

	void print()
	{
		std::cout << "name: " << _name.c_str() << std::endl;
		std::cout << "age: " << _age << std::endl;
		std::cout << "sex: " << _sex.c_str() << std::endl;
		std::cout << "sno: " << _sno << std::endl;
	}

protected:
	size_t _sno;
};

int main(void)
{
	Person p;
	Student s;

	p.print();
	std::cout << "===============================" << std::endl;
	s.print();

	return 0;
}
```

![2.继承演示](F:\CPPStudyJourney\Summary\14.继承\2.继承演示.png)

我们可以看到，虽然Student类里面没有一些变量，但是他依然可以打印。这就完美的说明了，Student类继承了Person类，并且，**Person类的成员变量，直接在Student类里也有一份**。

但是为什么构造函数里没有对那些成员的初始化呢？我们下面再说。

### 2.继承的定义

**1.2.1 定义格式**

```cpp
class Student : public Person
{
public:
	size_t sno;
}；
```

1. 先是定义派生类的名字。
2. 冒号后跟继承方式 + 基类名称。
3. 然后类里写自己的成员。

**1.2.2 继承方式**

**继承一共有三种方式**：

public：不改变基类的权限。该是啥还是啥，**基类的private成员，在子类中无法被访问**。基类的protected成员，在子类内部可以被访问，在子类外部无法被访问，就算是在子类外部子类变量调都无法使用。

protected：基类的所有成员最大的权限也就是protected。

private：基类的所有成员最大的权限也就是private。

**注意：**

1. 使用关键字class默认继承方式是private，使用关键字struct默认继承方式是public。
2. 实际运用中，一般都是public继承，很少用到其他继承方式。



## 2.基类和派生类对象赋值转换

**派生类对象可以赋值给基类的对象或基类的指针或基类的引用。**这种方式叫做**切片或切割**。

![3.派生类给基类赋值](F:\CPPStudyJourney\Summary\14.继承\3.派生类给基类赋值.png)

这张图非常的形象了。就是多的可以给少的赋值，大不了多余的部分不要了。可是少的无法给多的赋值，因为有一部分无法赋值。

所以，**基类无法给派生类赋值。**

## 3.继承中的作用域

1. **基类和派生类都有独立的作用域**，换句话说就是，你是你的，我是我的。
2. 如果基类和派生类有**同名成员**，派生类对屏蔽对基类同名成员的访问，这叫做**隐藏或重定义**。但是可以用  **基类::同名成员**  的方式来使用基类中的同名成员。（没事就不要定义同名的了。）
3. **如果函数名相同，也会构成隐藏**。（**参数一样不一样都无所谓，只要名字一样**。所以还是不要定义同名的了。）

```cpp
//基类
class Person
{
public:
	void print()
	{
		std::cout << "name: " << _name.c_str() << std::endl;
		std::cout << "age: " << _age << std::endl;
		std::cout << "sex: " << _sex.c_str() << std::endl;
	}

protected:
	std::string _name = "Gerald";
	size_t _age = 21;    //这里和派生类构成同名成员
	std::string _sex = "male";
};


//派生类
class Student : public Person
{
public:
	

	void print()
	{
		std::cout << "name: " << _name.c_str() << std::endl;
		std::cout << "age: " << _age << std::endl;
		std::cout << "sex: " << _sex.c_str() << std::endl;
		std::cout << "sno: " << _sno << std::endl;
	}

protected:
	size_t _sno = 110;
	size_t _age = 18; //这里和基类构成同名成员
};
```

![4.同名成员的隐藏](F:\CPPStudyJourney\Summary\14.继承\4.同名成员的隐藏.png)

不知道大家发现了没有，这里有两个隐藏。

1. _age同名变量，派生类隐藏了基类的变量。所以我们才看到Student的age为18，Person的age为21
2. 同名print函数的隐藏，在派生类里就没有调用基类的函数了，这里打印结果很明显证实。
3. 如果想调用基类的函数， **基类::同名成员**

## 4.派生类默认成员函数

在派生类中，默认成员函数有这么几条规则：

**构造：**
**1.默认生成：首先会自动调用父类的默认构造函数，再调用自己的构造函数**
**2.显式调用：如果父类有默认构造函数，可以不显式调用，如果父类无默认构造函数，需要在初始化列表显式调用**

**拷贝构造：**
**1.默认生成：编译器会自动调用父类的拷贝构造**
**2.显式调用：如果不显式调用父类的拷贝构造，编译器会自动调用父类默认构造**

**赋值运算符：**
**1.默认生成：编译器会自动调用父类的赋值运算符重载**
**2.显式调用：如果不显式调用，编译器不会调用父类赋值运算符重载**

**析构函数：**
**1.默认生成：先执行自己的析构，再执行父类的析构**
**2.显式调用：不需要显式调用父类析构，编译器会自动调用，注意父类析构和子类析构构成函数隐藏。**

**取地址：使用编译器默认生成的即可**

以下代码会验证上面这几条规则：

```cpp
//基类
class Person
{
public:
	Person()
	{
		std::cout << "Person()" << std::endl;
	}

	Person(const Person& x)
	{
		std::cout << "Person(const Person& x)" << std::endl;
	}

	Person& operator=(const Person& x)
	{
		std::cout << "Student operator=" << std::endl;

		return *this;
	}

	~Person()
	{
		std::cout << "~Person()" << std::endl;
	}

	void print()
	{
		std::cout << "name: " << _name.c_str() << std::endl;
		std::cout << "age: " << _age << std::endl;
		std::cout << "sex: " << _sex.c_str() << std::endl;
	}

protected:
	std::string _name = "Gerald";
	size_t _age = 21;
	std::string _sex = "male";
};


//派生类
class Student : public Person
{
public:
	Student()
	{
		std::cout << "Student()" << std::endl;
	}
	
	Student(const Student& x)
	{
		std::cout << "Student(const Student& x)" << std::endl;
	}

	Student& operator=(const Student& x)
	{
		std::cout << "Student operator=" << std::endl;

		return *this;
	}

	~Student()
	{
		std::cout << "~Student()" << std::endl;
	}
	void print()
	{
		std::cout << "name: " << _name.c_str() << std::endl;
		std::cout << "age: " << _age << std::endl;
		std::cout << "sex: " << _sex.c_str() << std::endl;
		std::cout << "sno: " << _sno << std::endl;
	}

protected:
	size_t _sno = 110;
	size_t _age = 18;
};

int main(void)
{
	Student s;
	std::cout << "===============================" << std::endl;
	Student s2(s);
	std::cout << "===============================" << std::endl;
	s2 = s;
	std::cout << "===============================" << std::endl;


	return 0;
}
```

![5.派生类的成员函数规则](F:\CPPStudyJourney\Summary\14.继承\5.派生类的成员函数规则.png)

## 5.继承与友元

**友元不可以被继承，就是基类的友元，不可以访问派生类的成员。**

这很好理解了，刚刚再说基类和派生类的作用域都是独立的。所以你是你的，我是我的。

## 6.继承与静态成员

**基类如果定义了一个静态成员，那么下面继承的派生类，也都只有这一个静态成员。**

**这里想说明的是，基类的静态成员生命周期将会是整个进程的生命周期，一旦定义，将会一直存在。**

```cpp
class A
{
public:
	A()
	{
		++_count;
	}
	static int _count;
};
int A::_count = 0;

class B : public A
{

};

class C : public B
{

};


int main(void)
{
	A a;
	B b;
	C c;

	std::cout << A::_count << std::endl;

	B b2;
	C c2;
	A a2;
	std::cout << A::_count << std::endl;


	return 0;
}
```

![6.继承的静态成员](F:\CPPStudyJourney\Summary\14.继承\6.继承的静态成员.png)

## 7.菱形继承

**这是继承里最重要的点！！！**

**坐直！认真听！手背后！**

首先我们先引入三个概念：

1. **单继承：一个子类只有一个直接父类时，称这个继承关系为单继承。**

   画个图理解一下：

   ![7.单继承](F:\CPPStudyJourney\Summary\14.继承\7.单继承.png)

2. **多继承：一个子类有两个或以上直接父类时称这个继承关系为多继承**

   ![8.多继承](F:\CPPStudyJourney\Summary\14.继承\8.多继承.png)

3. **菱形继承：菱形继承是多继承的一种特殊情况**

   ![9.菱形继承](F:\CPPStudyJourney\Summary\14.继承\9.菱形继承.png)

   但是菱形继承存在一个问题：就是比如```class G```里有一个成员变量```int _g```。那么到```class C```里是不是就有两个```_g```变量了，因为它继承了两个类，而每个类里又分别有一个```_g```变量啊。

   ```cpp
   class G
   {
   public:
   	int _g;
   };
   
   class A : public G
   {
   protected:
   	int _a;
   };
   
   class B : public G
   {
   protected:
   	int _b;
   };
   
   class C : public A, public B
   {
   protected:
   	int _c;
   };
   
   void test(void)
   {
   	C c;
   	c._g = 1;
   }
   
   ```

   如果这样使用```_g```变量会报错。

   ![10.数据重定义](F:\CPPStudyJourney\Summary\14.继承\10.数据重定义.png)

   但是可以这样用

   ```cpp
   void test(void)
   {
   	C c;
   	c.A::_g = 1;
       c.B::_g = 2;
   }
   ```

   这样虽然可以解决二义性的问题，但是无法解决数据冗余。这个变量我们只需要一个就可以啦，不需要两份。

   它在虚拟地址空间存储的结构是这样的。

   ![11.菱形继承的存储方式1](F:\CPPStudyJourney\Summary\14.继承\11.菱形继承的存储方式1.png)

   A的数据在上面两格，B的数据在中间两格（并不真正是A B的数据，而是A B的对象）。这整个就是C。很明显看到，```_g```变量占了两个空间。这肯定不行呀，肯定要解决呀。

   所以才有了下面的解决方法。

   **虚拟继承可以解决菱形继承的二义性和数据冗余**

   ```cpp
   class G
   {
   public:
   	int _g;
   };
   
   class A : virtual public G
   {
   protected:
   	int _a;
   };
   
   class B : virtual public G
   {
   protected:
   	int _b;
   };
   
   class C : public A, public B
   {
   protected:
   	int _c;
   };
   
   void test(void)
   {
   	C c;
   	c.A::_g = 1;
   	c.B::_g = 2;
   	c._a = 3;
   	c._b = 4;
   	c._c = 5;
   }
   
   ```

   **那么虚拟继承的原理是什么呢？**

   先看图：

   ![12.菱形继承的存储方式2](F:\CPPStudyJourney\Summary\14.继承\12.菱形继承的存储方式2.png)

   这次可以看到，```_g```只有一份了，就是绿色的那个，在最下面。但是我们注意到原来存A B类```_g```的放怎么是看不懂的东西。不，那里存的是地址。那我们到响应的地址看看。

   ![13.菱形虚拟继承](F:\CPPStudyJourney\Summary\14.继承\13.菱形虚拟继承.png)

   这两个地址分别存的都是0。但是他们下面的那个地址存的分别是20  12 。为什么呢？

   再看最右边的地址。A成员区，那个地址到最下面```G```类的```_g```成员共需要20个字节。而B成员区那个地址到最下面```G```类的```_g```共需要12个字节。那么现在很清楚了。原来用虚拟继承了之后，原本存数据的地方现在存了该地址到共有数据的偏移量。

   **那么为什么要这样设计呢？这么复杂。**

   因为如果需要将c 赋值 给 a 或 b  就要发生切片的操作。然后可以直接通过偏移量找到基类的变量，直接赋值。



