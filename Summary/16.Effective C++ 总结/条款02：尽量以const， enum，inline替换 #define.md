### 条款02：尽量以const， enum，inline替换 #define

### Prefer consts, enums, and inlines to #define

`#define`我们知道是定义宏，这是在编译器**预处理阶段就会进行宏替换**。那么在C++里为什么尽量不要用`#define`而要用以上那些呢？

**1. #define不被视为语言的一部分，在预处理阶段就会进行替换，并且宏不会进入符号表**

例如：```#define ASPECT_RATIO 1.653```  那么在**预处理阶段编译器就会对这个符号进行替换**，那么也就是说，**这个符号根本不会进入到符号表里**。如果**在这个时候发生了编译错误**，并且碰巧牵扯到了你定义的宏，**那么编译器就只会显示`1.653`而不是`ASPECT_RATIO`**。这个时候如果你忘记了`1.653`是什么意思了，那么估计你会找很久的错误。

那么怎么解决呢？就是用常量来替换这个宏。

```const double AspectRatio = 1.653;```

那么这个常量就会进入到符号表里，编译出错你也能直接看到哪里错了。

**2. const 替换 #define 有两种特殊情况**

1. 定义常量指针

   一般常量指针放在头文件里，为了被不同的源码含入，所以得把这个指针定义为`const`,  如果要在头文件里放一个常量字符串，就得这么写：

   ``` const char* const myName = "GeraldKwok";```

   但是string 对象往往比常量指针合适，所以这样定义更好：

   ```const std::string myName = "GeraldKwok";```

2. class 专属常量。

   为了将常量的作用域限定在class内，可以这么定义：

   ```cpp
   class Test
   {
       ...
   private:
       static const int num = 5;
       int scores[num]
       ...
   };
   const int Test::num;
   //num在声明时已经获得初值，所以定义时可以不给值
   ```

**3. #define 不能够提供任何封装性**

**4. the enum hack 补偿做法**

如果上面的类不允许在静态常量在声明时初始化，而且数组又必须在编译期间获得大小，那么可以这么做。

```cpp
class Test
{
    ...
private:
    enum
    {
		num = 5;
    }
    int scores[num]
    ...
};
```

**5. 用inline而不用 #define**

通常#define定义的宏函数，往往会出错，为什么呢？各种括号呀，前后顺序呀，bulabula....

但是用inline函数，就不会，你不必担心函数本体中为参数加括号，也不用担心参数被核算多次。。。等等



**对于单纯常量，最好以const对象或enum替换 #define**

**对于形似函数的宏，最好用inline函数替换#define