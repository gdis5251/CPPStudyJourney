# C++ 单例模式

### 1.概念：

**一个类只能创建一个对象，即单例模式**，该模式可以保证系统中该类只有一个实例，并提供一个访问它的全局访问点，该实例被所有程序模块共享。

简单的说就是，整个程序就需要一份这个类，多了会浪费空间。怎么弄才能更好的处理这种情况。

### 2.单例模式有两种实现模式：

1. **饿汉模式**

   饿汉嘛！饿嘛！所以啥也不管先来一份吃的再说。

   **所以饿汉模式，就是在程序启动的时候就创建一个唯一的实例对象。**

   我们先看看代码：

   ```cpp
      class Hungry_Mode
      {
      public:
          static Hungry_Mode* get_instance()
          { 
              return &_m_instance;
          } 
     
      private:
          Hungry_Mode(){};
          Hungry_Mode(Hungry_Mode const&);
          Hungry_Mode& operator=(Hungry_Mode const&);
     
          //or C++11
          //Hungry_Mode(Hungry_Mode const&) = delete;
          //Hungry_Mode& operator=(Hungry_Mode const&) = delete;
     
          static Hungry_Mode _m_instance;
      };
     
      Hungry_Mode Hungry_Mode::_m_instance;
   ```

   1. 我们将对象声明为静态变量，这样就可以延长它的生命周期，并且，因为它的类型是这个类，所以声明为静态变量不算进类的大小里，不然类还没定义完，怎么计算大小。
   2. 因为，这个变量只能定义一次，也就是说整个程序里就只能有一个变量对象。所以我们要把这个类的默认构造函数放进私有域里，这样就不能再定义其他对象了。我个人觉得，copy 构造也有必要放进私有域，copy assignment（赋值运算符重载）没必要放进私有域。因为copy 构造也是在创建类的对象的时候调用，copy 构造也可以使用初始化列表来初始化对象。而copy assignment 就没必要，因为只有已有对象才可以调用它，无法创建新的对象就没办法调用它，所以可以不把它放进私有域，但是为了统一还是放吧。
   3. 在共有域里，定义了一个静态函数，用来返回这个静态成员的地址。这个时候就可以保证，在没有对象的时候可以通过类名去调用这个函数获取静态成员的地址。

   **优点**：结构简单，好理解。

   **缺点**：可能会导致进程启动慢，且如果有多个单例类对象实例启动顺序不确定。

   如果这个单例对象在**多线程高并发环境下频繁使用**，性能要求较高，那么显然使用饿汉模式来避免资源竞争，提高响应速度更好。

2. **懒汉模式**

   如果单例对象的构造十分耗时或者占用很多资源，那么进程启动时就创建对象未免有点难受。

   如果我们对这个单例对象的使用频率不高，或者干脆就用一次，那么我们为什么要在进程启动时就创建它呢。

   所以，懒汉模式就是用的时候再创建，并且只创建一次。懒汉，懒嘛！所以进程一启动它懒得创建，非要等你用的时候再创建。

   先看代码：

   ```cpp
     1 #include <iostream> 
     2 #include <mutex>
     3 
     4 class Idler
     5 {
     6 public:
     7     Idler* GetInstance(void)
     8     {
     9         if (_m_instance == nullptr)
    10         {
    11             _m_mtx.lock();
    12             if (_m_instance == nullptr)
    13             {
    14                 _m_instance = new Idler();
    15             }
    16             _m_mtx.unlock();
    17         }
    18 
    19         return _m_instance;
    20     }
    21 
    22     class CGorbo
    23     {
    24     public:
    25         ~CGorbo()
    26         {
    27             if (_m_instance != nullptr)
    28             {
    29                 delete _m_instance;
    30             }
    31         }
    32     };
    33 
    34     static CGorbo _CGorbo;
    35 
    36 private:
    37     Idler(){};
    38     Idler(Idler const&) = delete;
    39     Idler& operator=(Idler const&) = delete;
    40 
    41     static std::mutex _m_mtx;
    42     static Idler *_m_instance;
    43 };
    44 
    45 Idler* Idler::_m_instance = nullptr;
    46 std::mutex Idler::_m_mtx;
    47 Idler::CGorbo _CGorbo;  
   ```

   > 因为是在```linux```下写的代码，行太多了懒得删行号了。

   1. 懒汉模式是在用的时候调用创建对象，所以我们声明一个指针，创建的时候直接``new``， 得到地址返回地址。

   2. 如果在多线程情况下，无法保证线程的执行顺序，或者有可能同时执行，所以一个```if```的判断，有可能两个线程的``_m_pInstance``指针都为``nullptr``。所以我们需要加锁。但是如果不用```double check```，那么效率是非常低下的。就是这种情况：

      ```cpp
      Idler* GetInstance(void)
      {
      	_m_mtx.lock();
      	if (_m_instance == nullptr)
      	{
      		_m_instance = new Idler();
      	}
      	_m_mtx.unlock();
      	return _m_instance;
      }
      ```

      所有的线程判断前，全部被挡住，一个一个判断，这样的效率非常低。```double check```就是保证了，第一次创建完成后，其他的线程只需要第一层判断即可，大大提高了效率。

   3. 这里有一个内部类，完成清理的工作，这个内部类也是定义了一个静态变量，程序启动时，就有，当程序结束时，它会自动调用内部类的析构函数，完成对单例对象的清理。

   **优点：**第一次使用实例对象时，创建对象。进程启动无负载。多个单例实例启动顺序自由控制。

   **缺点：**设计太复杂啦。

