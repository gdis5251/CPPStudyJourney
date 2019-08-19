#include <iostream>
#include <cstdio>
#include "AutoPtr.hpp"
#include "UniquePtr.hpp"

int main()
{
#if 0
    AutoPtr<int> ap(new int);
    *ap = 1;

    AutoPtr<int> tmp(ap);
    if (ap == nullptr)
    {
        std::cout << "Change Charge" << std::endl;
    }
#endif
    UniquePtr<int> up((int*)malloc(sizeof(int) * 10));
    *up = 100;

    // UniquePtr<int> tmp(up);
    return 0;
}

