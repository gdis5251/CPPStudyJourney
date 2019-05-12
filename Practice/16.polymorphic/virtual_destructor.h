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

void Test(void)
{
    Person *p1 = new Person;
    Child *p2 = new Child;

    delete p1;
    delete p2;
}
