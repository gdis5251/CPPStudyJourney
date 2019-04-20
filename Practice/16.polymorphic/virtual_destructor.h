#include <iostream>

class Person
{
public:
    virtual ~Person()
    {
        std::cout << "~Person()" << std::endl;
    }
};

class Child
{
public:
    virtual ~Child()
    {
        std::cout << "~Child()" << std::endl;
    }
};
