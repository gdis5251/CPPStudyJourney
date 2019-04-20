#include <iostream>

class Person
{
public:
    virtual void Strength() = 0;
};

class Adult : public Person
{
public:
    virtual void Strength()
    {
        std::cout << "Adult have big Strength!" << std::endl;
    }
};

class Child : public Person
{
public:
    virtual void Strength()
    {
        std::cout << "Child have Small Strength!" << std::endl;
    }
};
