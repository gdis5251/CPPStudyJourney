#include <iostream>

class Person 
{
public:
    virtual void BuyTicket(int)
    {
        std::cout << "Adult need Full Fare!" << std::endl;
    }
};

class Child : public Person
{
public:
    virtual void BuyTicket(int)
    {
        std::cout << "Child Free!" << std::endl;
    }
};

void fun(Person& obj)
{
    obj.BuyTicket(1);
}
