# C++内存管理

> C/C++的内存分布，并且各个内存区域都存储那些数据
>
> 1. **栈**又叫堆栈，非静态局部变量/函数参数/返回值等等，栈是向下增长的。
> 2. **内存映射段**是高效的I/O映射方式，用于装载一个共享的动态内存库。用户可使用系统接口创建共享内存，做进程间通信。
> 3. **堆**用于程序运行时动态内存分配，堆是向上增长的。
> 4. **数据段**存储全局数据和静态数据。
> 5. **代码段**可执行代码（这里的可执行代码是编译后的01机器码）和只读常量。

### 1.C++内存管理方式

> C语言的内存管理方式C++依然可以用，可是C++用起来比较麻烦，所以C++就有了自己的内存管理方式：**通过new和delete操作符来进行动态内存管理。**
>
> **注意：**C语言的malloc之类的都是**函数**，可是C++的new/delete都是**操作符**。

**1.1 new/delete操作内置类型**

```cpp
void Test()
{
	int *p1 = new int;
	//动态申请一个int型的空间

	int *p2 = new int(2);
	//动态申请一个int型空间，并且进行初始化为2

	int *p3 = new int[3];
	//动态连续申请3个int型的空间

	delete p1;
	delete p2;
	delete[] p3; //若删除多个连续的内存块需要在Delete后面加[]

}
```

**注意：如果申请或释放一个类型空间，使用new/delete即可；如果要申请或释放多个类型空间需要用new[]/delete[]。**

**1.2 new/delete操作自定义类型**

```cpp
class Test
{
public:
	Test()
		:_data(0)
	{
		std::cout << "Test()" << std::endl;
	}

	~Test()
	{
		std::cout << "~Test()" << std::endl;
	}

private:
	int _data;
};

void TestNewDelete()
{
	Test *t1 = new Test;
	delete t1;

	Test *t2 = new Test[10];
	delete[] t2;

	/*Test *t3 = (Test *)malloc(sizeof(Test));
	free(t3);

	Test *t4 = (Test *)malloc(sizeof(Test) * 10);
	free(t4);
*/

}
```

**注意：**在申请自定义类型的空间时，new会调用构造函数，delete会调用析构函数。而malloc/free不会调用。所以C++才会引入new/delete关键字。

---

### 2.operator new 与 operator delete函数

> **new和delete是用户进行动态内存申请和释放的操作符**，**operator new 和 operator delete是系统提供的全局函数。** **new在底层调用operator new全局函数**来申请空间，**delete在底层通过operator delete全局函数**来释放空间。

```cpp
/*
operator new：该函数实际通过malloc来申请空间，当malloc申请空间成功时直接返回；申请空间失败，尝试
执行空 间不足应对措施，如果改应对措施用户设置了，则继续申请，否则抛异常。
*/
void *__CRTDECL operator new(size_t size) _THROW1(_STD bad_alloc)
{
 	// try to allocate size bytes
	void *p;
 	while ((p = malloc(size)) == 0)
 		if (_callnewh(size) == 0)
 		{
 			// report no memory
 			// 如果申请内存失败了，这里会抛出bad_alloc 类型异常
 			static const std::bad_alloc nomem;
 			_RAISE(nomem);
 		}
 	return (p);
}
/*
operator delete: 该函数最终是通过free来释放空间的
*/
void operator delete(void *pUserData)
{
 	_CrtMemBlockHeader * pHead;
    
 	RTCCALLBACK(_RTC_Free_hook, (pUserData, 0));
    
 	if (pUserData == NULL)
 		return;

 	_mlock(_HEAP_LOCK); /* block other threads */
 	__TRY
        
 		/* get a pointer to memory block header */
 		pHead = pHdr(pUserData);
    
 		/* verify block type */
 		_ASSERTE(_BLOCK_TYPE_IS_VALID(pHead->nBlockUse));
    
 		_free_dbg( pUserData, pHead->nBlockUse );
    
 	__FINALLY
 		_munlock(_HEAP_LOCK); /* release other threads */
 	__END_TRY_FINALLY
        
 	return;
}
/*
free的实现
*/
#define free(p) _free_dbg(p, _NORMAL_BLOCK)
```

从上面的两个源码可以看出，**operator new 实际也是通过malloc来申请空间，**但是他比直接用malloc的好处是，如果申请成功直接返回，否则执行空间不足应对措施，如果提供了措施就继续申请，否则就抛异常。**operator delete最终是通过free来释放空间的。**

---

### 3.new和delete的实现原理

**3.1 内置类型**

如果申请的是内置类型的空间，new和malloc，delete和free基本类似，不同的地方是：new/delete申请和释放的是单个元素的空间，new[]和delete[]申请的是连续空间，而且new在申请空间失败时会抛异常，malloc会返回NULL。

**3.2 自定义类型**

- new的原理
  1. 调用operator new函数申请空间
  2. 在申请的空间上执行构造函数，完成对象的构造

- delete的原理
  1. 在空间上执行析构函数，完成对象中资源的清理工作
  2. 调用operator delete函数释放对象的空间

- new T[N]的原理
  1. 调用operator new[]函数，在operator new[]中实际调用operator new函数完成N个对象空间的申请
  2. 在申请的空间上执行N次构造函数

- delete[]的原理
  1. 在释放的对象空间上执行N次析构函数，完成N个对象中资源的清理
  2. 调用operator delete[]释放空间，实际在operator delete[]中调用operator delete来释放空间