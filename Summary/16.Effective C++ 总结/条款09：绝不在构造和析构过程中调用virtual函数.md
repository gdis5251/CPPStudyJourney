## 条款09：绝不在构造和析构过程中调用virtual函数

### Never call virtual function during construction or destruction

> 开始之间先说一个结论来开门见山！！绝对不要在构造和析构中调用virtual函数。这会导致发生不是你期望的事情。

比如，我们举个栗子！:yum:

游戏我们都玩过吧，就好比MOBA类游戏。你击杀敌人和敌人把你击杀，都会有记录。那么来看看下面这个实现：

```cpp
#include <iostream>

class Game {
public:
    Game();
    ~Game();
    virtual void Log() const = 0;

};
Game::Game(){
        Log();
        std::cout << "Game() Log()" << std::endl;
    };
Game::~Game(){
        Log();
        std::cout << "~Game() Log()" << std::endl;
    };

class Kill : public Game {
public:
    virtual void Log() const override {
        std::cout << "Kill Log()" << std::endl;
    }
};

class BeKill : public Game {
public:
    virtual void Log() const override {
        std::cout << "BeKill Log()" << std::endl;
    }
};

int main(void)
{
    Kill a;

    return 0;
}

```

![9.1](F:\CPPStudyJourney\Summary\16.Effective C++ 总结\9.1.png)

首先，结果在运行时报错了。

因为这样创建对象时，派生类会先会调用基类的默认构造函数，然后，你基类的默认构造函数里面调用的虚函数，其实就是基类的虚函数。

说白了，就是你想通过派生类调用一下虚函数，结果调成了基类的虚函数，然后就报错了。

这是因为在`linux`平台下的`gcc`编译器报错。在其他平台下的其他编译器说不定不会报错（因为effective C++提出这个观点，说不定作者用的编译器没有报错呢）。试想想如果没有报错，那是不是就造成了一个错误。以后改的时候会比较麻烦。

析构函数也一样，如果你在析构函数里调用虚函数，那就会调用基类的虚函数。

**然后你可能会说：卧槽这么明显的错误我怎么会犯呢？嘘~射程范围内。**

试想下面的场景，假设这个基类里面有很多构造函数，那么我们每个构造函数虽然功能或接受参数不是那么完全相同，但是里面都要重复的初始化一些相同的成员变量，这些重复的代码会造成代码量过大，这样我们可以定义一个

```init()```函数，来初始化这相同的部分，**那么如果，这个虚函数不是纯虚函数，并且这个```init()```还调用了它，此时就不会报错，还不容易被发现。等你定义了派生类对象之后，你就会发现，这个虚函数并不是你想要的，你也不知道怎么回事。**

> 根据我的实验，之前那么报错只是因为虚函数被定义成了纯虚函数，没有实体连接不到。

```cpp
#include <iostream>

class Game {
public:
    Game(){
        init();
    };

    void init() {
        Log();
    }

    ~Game(){
        std::cout << "~Game() Log()" << std::endl;
    };

    virtual void Log() const {
        std::cout << "Game() Log()" << std::endl;
    }

};

class Kill : public Game {
public:
    virtual void Log() const override {
        std::cout << "Kill Log()" << std::endl;
    }
};

class BeKill : public Game {
public:
    virtual void Log() const override {
        std::cout << "BeKill Log()" << std::endl;
    }
};

int main(void)
{
    Kill a;

    return 0;
}
```

![9.2](F:\CPPStudyJourney\Summary\16.Effective C++ 总结\9.2.png)

看吧。你本来想调用该对象类的Log()函数来初始化，结果调成了基类的Log()函数了。



### 解决办法：

唯一的一个解决办法就是，确定你的构造函数个析构函数里面没有调用虚函数！唯一！的！办法！