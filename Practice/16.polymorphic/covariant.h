#include <iostream>

class A
{
public:
    virtual A* fun()
    {
        return new A;
    }
};

class B : public A
{
public:
    virtual B* fun()
    {
        return new B;
    }
};
