# C++ 多态的实现原理

> 多态的概念：在一个继承体系中，不同对象，执行同一动作，产生不同结果。

## 1.虚函数表

### 1.1 牛刀小试

我们以一道题来展开这篇博客要讲的内容。

```cpp
class a
{
public:
	virtual void fun()
	{

	}
protected:
	int a;
};

void Test()
{
    a a;
	std::cout << sizeof(a) << std::endl;
}
```

![2.虚函数表指针](F:\CPPStudyJourney\Summary\15.多态\2.虚函数表指针.png)

为什么命名`a`类里只有一个变量，而按理来说函数的代码应该存在代码区，不占对象空间呀？

那我们来看看这个对象里面到底有什么。

![2.虚函数表指针2](F:\CPPStudyJourney\Summary\15.多态\2.虚函数表指针2.png)

竟然多了一个指针，这个指针的全称为`_vfptr(virtual function ptr)`，这是一个指针，指向一个名叫**虚函数表**的指针，这个**虚函数表是一个指针数组**，**里面放着一个个虚函数的地址**。

记住这个概念，后面慢慢来说明。

### 1.2 验证猜想

我们来进一步试验一下，看代码

```cpp
class base
{
public:
	virtual void fun1()
	{
		std::cout << "base::fun1()" << std::endl;
	}
	virtual void fun2()
	{
		std::cout << "base::fun2()" << std::endl;
	}
	void fun3()
	{
		std::cout << "base::fun3() non-virtual" << std::endl;
	}

protected:
	int _b;
};

class derive : public base
{
public:
	void fun5()
	{
		std::cout << "derive::fun5()" << std::endl;
	}

protected:
	int _d;
};

void Test(void)
{
	base b;
	derive d;
    
    std::cout << sizeof(b) << std::endl;
	std::cout << sizeof(d) << std::endl;
}
```

首先，我们不对基类的函数进行重写，看看现象。

![3](F:\CPPStudyJourney\Summary\15.多态\3.png)

我们看到，派生类不仅会继承基类的成员变量，还会继承虚表，**但是虚表的首地址不一样。**记住这个现象下面说。

那么我们再来在派生类里对一个基类函数进行重写会发生什么呢？

```cpp
class base
{
public:
	virtual void fun1()
	{
		std::cout << "base::fun1()" << std::endl;
	}
	virtual void fun2()
	{
		std::cout << "base::fun2()" << std::endl;
	}
	void fun3()
	{
		std::cout << "base::fun3() non-virtual" << std::endl;
	}

protected:
	int _b;
};

class derive : public base
{
public:
	virtual void fun1()
	{
		std::cout << "derive::fun1()" << std::endl;
	}

protected:
	int _d;
};

void Test(void)
{
	base b;
	derive d;

	std::cout << sizeof(b) << std::endl;
	std::cout << sizeof(d) << std::endl;
}
```

![4](F:\CPPStudyJourney\Summary\15.多态\4.png)

大体跟上面的情况一样，但是，发现虚函数表里的第一个，也就是重写的函数地址不一样了。

**基于以上两种现象的解释：**

1. 在继承发生后，若**基类有虚函数**，将会在**基类对象内生成一个虚函数表指针**。
2. **若派生类继承了基类**，将会**另开辟一个与基类虚函数表相同大小的地方，先将基类的虚函数表的内容全部拷贝过来。**
3. 如果**派生类重写了某个基类的虚函数**，那么这个虚函数的地址将会**直接覆盖派生类虚函数表中相应的基类的虚函数的地址**。**所以函数重写也叫做覆盖**。
4. 普通函数会被继承，但是不会被放进虚表里。
5. **虚函数表是一个指针数组**，放着虚函数的地址。**这个数组最后放了一个`nullptr`。**
6. 派生类新增加的虚函数按其**声明次序增加到虚表的最后。**

### 1.3 虚函数放在哪里？

**我们知道每个程序就是一个进程，程序就是进程的实例化。**而我们的操作系统**为了保护内存**，在进程启动的时候会为进程**分配一个虚拟地址空间**。而这个虚拟地址空间都有几个区域。

这里我们简单说。从上到下我们能访问的都有，**栈、堆、未初始化全局变量、已初始化全局变量、常量段、代码段**。所以，我通过代码，分别在这里面创建空间，然后看看这些空间的地址，对比之后我们就知道 **虚函数和虚表放在哪里了。**

```cpp
class base
{
public:
	virtual void fun1()
	{
		std::cout << "base::fun1()" << std::endl;
	}
	virtual void fun2()
	{
		std::cout << "base::fun2()" << std::endl;
	}
	void fun3()
	{
		std::cout << "base::fun3() non-virtual" << std::endl;
	}

protected:
	int _b;
};

class derive : public base
{
public:
	virtual void fun1()
	{
		std::cout << "derive::fun1()" << std::endl;
	}

protected:
	int _d;
};

int _globe = 0;

void Test(void)
{
	//base b;
	derive d;
	int a = 0;
	int *p = new int;

	std::cout << "栈：" << &a << std::endl;
	std::cout << "堆：" << p << std::endl;
	std::cout << "数据段：" << &_globe << std::endl;
	printf("代码段：%p\n", &base::fun3);
	printf("虚函数：%p\n", *((int*)*(int*)&d));
	printf("虚表：%p\n", *(int*)&d);
}
```

![5](F:\CPPStudyJourney\Summary\15.多态\5.png)

**这里就很清晰了，虚函数和虚表非常接近代码段和数据段。**

所以我们推断，虽然是虚函数，但是依然跟普通函数一样**存在代码段。**

---

## 2.多态的原理

### 2.1 实现原理

上面说了这么多关于虚表的事情，那么为什么要有虚表呢？

我们结合例子来说吧。

```cpp
![6](F:\CPPStudyJourney\Summary\15.多态\6.png)class OrdinaryUser
{
public:
	virtual void WatchFiles()
	{
		std::cout << "Ordinary User can't see files" << std::endl;
	}
};

class VIPUser : public OrdinaryUser
{
public:
	virtual void WatchFiles() override
	{
		std::cout << "VIP User can see files" << std::endl;
	}
};

void Func(OrdinaryUser& user)
{
	user.WatchFiles();
}

void Test()
{
	OrdinaryUser o_user;
	VIPUser vip_user;

	Func(o_user);
	Func(vip_user);
}
```

![6](F:\CPPStudyJourney\Summary\15.多态\6.png)

我现在来解释一下为什么会有这样的现象：

1. 这个继承关系**构成多态**。
2. 基类对象和派生类对象都有一个**属于自己的虚表**。
3. 在调用```Func```函数的时候，基类对象很清晰的调用自己的`WatchFiles`函数，而派生类对象调用`Func`函数时，发生**切片操作**，**将自己的基类部分给了`user`，然后`user`通过虚表找到派生类的虚函数，然后调用派生类的虚函数。**
4. 其实**不管是基类对象还是派生类对象都是通过`user`寻找虚表，再找到虚函数，然后调用该对象的虚函数。**
5. **为什么`Func`不能传值**：如果传值，派生类修改了虚表的内容，所以虚表属于派生类了，传值只会把基类的部分给它，不会给虚表，所以无法找到派生类的虚函数。

### 2.2 有两个小概念

**动态绑定和静态绑定**。

1. 静态绑定又称为前期绑定(早绑定)，在程序编译期间确定了程序的行为，也称为静态多态，比如：函数重载，编译期间就知道要调用哪个函数了。
2. 动态绑定又称后期绑定(晚绑定)，是在程序运行期间，根据具体拿到的类型确定程序的具体行为，调用具体的函数，也称为动态多态。

---

## 3.单继承和多继承关系的虚函数表

我们前面了解了多态的原理以及虚表的作用，那么在单继承和多继承下，虚表都是怎么存的呢？

### 3.1 单继承中的虚表

```cpp
class Base
{
public:
	virtual void Fun1() 
	{
		std::cout << "Base::Fun1()" << std::endl;
	};
	virtual void Fun2()
	{
		std::cout << "Base::Fun2()" << std::endl;
	};
};

class Derive : public Base
{
public:
	virtual void Fun2() override
	{
		std::cout << "Derive::Fun2()" << std::endl;
	}
	virtual void Fun3()
	{
		std::cout << "Derive::Fun3()" << std::endl;
	}
	virtual void Fun4()
	{
		std::cout << "Derive::Fun4()" << std::endl;
	}
};

void Test(void)
{
	Base b;
	Derive d;
}
```

![7](F:\CPPStudyJourney\Summary\15.多态\7.png)

![img](file:///C:\Users\DELL\AppData\Local\Temp\SGPicFaceTpBq\2624\0EE67AD6.gif)

怎么派生类的另外两个虚函数没有呢？

其实是在里面存的，但是VS做了优化，没有显示出来。为什么它不显示呢？其实很好理解。

**虚表的作用就是为了实现多态，而多态在调用函数的时候形参的类型是基类引用。说白了，就是只能多态基类的函数，所以你派生类的虚函数就没有用。它就不给你显示了。**

那么再加一个派生类继承`Derive`呢？

```cpp
class Derive2 : public Derive
{
public:
	virtual void Fun2() override
	{
		std::cout << "Derive::Fun2()" << std::endl;
	}
	virtual void Fun3()
	{
		std::cout << "Derive::Fun3()" << std::endl;
	}
	virtual void Fun4()
	{
		std::cout << "Derive::Fun4()" << std::endl;
	}
};

void Test(void)
{
	Base b;
	Derive d;
	Derive2 d2;

}
```

![8](F:\CPPStudyJourney\Summary\15.多态\8.png)

结果一样还是不显示，跟上面的解释一样，毕竟你调用函数的形参是最上面的基类的引用或指针，其他派生类的虚函数没有办法实现多态。

![9](F:\CPPStudyJourney\Summary\15.多态\9.png)

你看，基类对象的选项只有`Fun1 Fun2`。

那么两个派生类之间是否可以实现多态呢？答案是可以的。

![10](F:\CPPStudyJourney\Summary\15.多态\10.png)

只要修改调用函数的形参就行。

### 3.2 那么怎么把VS优化隐藏起来的虚函数打出来呢？

看代码：

```cpp
class Base
{
public:
	virtual void Fun1() 
	{
		std::cout << "Base::Fun1()" << std::endl;
	};
	virtual void Fun2()
	{
		std::cout << "Base::Fun2()" << std::endl;
	};
};

class Derive : public Base
{
public:
	virtual void Fun2() override
	{
		std::cout << "Derive::Fun2()" << std::endl;
	}
	virtual void Fun3()
	{
		std::cout << "Derive::Fun3()" << std::endl;
	}
	virtual void Fun4()
	{
		std::cout << "Derive::Fun4()" << std::endl;
	}
};


typedef void(*VFTPtr)();

void Print(VFTPtr table[])
{
	std::cout << table << std::endl;
	for (int i = 0; table[i] != nullptr; i++)
	{
		std::cout << table[i] << ":  ";
		VFTPtr v = table[i];
		v();
	}
}

void Test(void)
{
	Base b;
	Derive d;
	//Derive2 d2;

	std::cout << "Base的虚表:  ";
	Print((VFTPtr*)(*(int*)&b));

	std::cout << "Derive的虚表:  ";
	Print((VFTPtr*)(*(int*)&d));
}
```

![11](F:\CPPStudyJourney\Summary\15.多态\11.png)

> 如果在VS下实现，要先清理解决方案，然后重新生成解决方案，才有这个现象，这是编译器的一个BUG，我被这个坑了很久。。。

### 3.3 多继承中的虚表

```cpp
class Base1
{
public:
	virtual void Fun1()
	{
		std::cout << "Base1::Fun1()" << std::endl;
	}
	virtual void Fun2()
	{
		std::cout << "Base1::Fun2()" << std::endl;
	}
};

class Base2
{
public:
	virtual void Fun1()
	{
		std::cout << "Base2::Fun1()" << std::endl;
	}
	virtual void Fun2()
	{
		std::cout << "Base2::Fun2()" << std::endl;
	}
};

class Derive : public Base1, public Base2
{
	virtual void Fun1() override
	{
		std::cout << "Derive::Fun1()" << std::endl;
	}
	virtual void Fun3()
	{
		std::cout << "Derive::Fun3()" << std::endl;
	}
};

typedef void(*VFTPtr)();

void Print(VFTPtr table[])
{
	std::cout << table << std::endl;
	for (int i = 0; table[i] != nullptr; i++)
	{
		std::cout << table[i] << ":  ";
		VFTPtr v = table[i];
		v();
	}
}

void Test(void)
{
	Base1 b1;
	Base2 b2;
	Derive d;
	//Derive2 d2;

	std::cout << "Base1的虚表:  ";
	Print((VFTPtr*)(*(int*)&b1));

	std::cout << "Base2的虚表:  ";
	Print((VFTPtr*)(*(int*)&b2));

	std::cout << "Derive的虚表:  " << std::endl;
	std::cout << "继承Base1的虚表:  ";
	Print((VFTPtr*)(*(int*)&d)); //继承Base1 的虚表
	std::cout << "继承Base2的虚表:  ";
	Print((VFTPtr*)(*(int*)((char*)&d + sizeof(Base1)))); //继承Base2的虚表
}
```

![12](F:\CPPStudyJourney\Summary\15.多态\12.png)

这说明了两条规则：

1. 多继承的时候如果自己有一个虚函数，这个虚函数往第一个虚表里放
2. 多继承的时候重写的话，两个虚表都重写