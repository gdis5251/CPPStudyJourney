#include <iostream>
#include <string>

double Division(int lhs, int rhs)
{
    if (rhs == 0)
        throw "the rhs is 0";
    else
        return (double)lhs / (double)rhs;
}

void Func()
{
    int *array = new int[10];

    try
    {
        int lhs, rhs;
        std::cin >> lhs >> rhs;
        Division(lhs, rhs);
    }
    catch(...)//...表示接收任何异常
    {
        std::cout << "delete[] array" << std::endl;
        delete[] array;
        throw;//重新抛出异常信息
    }

    std::cout << "delete[] array" << std::endl;
    delete[] array;
}
void Test()
{
    try
    {
        Func();
    }
    catch(const char*  errmsg)
    {
        std::cout << errmsg << std::endl;
    }
}
