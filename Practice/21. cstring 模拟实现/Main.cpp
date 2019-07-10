#include <iostream>
#include <cstdio>
#include "My_Cstring.hpp"

void Test_strlen(void)
{
    const char* str = "Hello BAT";
    std::cout << My_Strlen1(str) << std::endl;
    std::cout << My_Strlen2(str) << std::endl;
    std::cout << My_Strlen3(str) << std::endl;
}

void Test_strcpy(void)
{
    char str1[] = {"I Love You!"};
    const char* str2 = "ditto!";

    std::cout << My_strcpy(str1, str2) << std::endl;
}

void Test_strcat(void)
{
    // char str1[] = "I am ";
    char str1[] = {"I am "};
    const char* str2 = "Gerald";

    std::cout << My_strcat(str1, str2) << std::endl;
}

void Test_strstr(void)
{
    const char* str1 = "HHHHHHHAAA";
    const char* str2 = "OOOOO";
    const char* str3 = "HA";

    std::cout << My_strstr(str1, str2) << std::endl;

    // cout 无法打印出来， printf 可以打印出来？？
    std::cout << My_strstr(str1, str3) << std::endl;
    printf("%s\n", My_strstr(str1, str3));
}

void Test_memcpy(void)
{
    char src1[] = {"abcdef"};
    char src2[] = {"abcdef"};
    char src3[] = {"abcdef"};


    std::cout << (char*)My_memcpy(src1 + 1, src1, 1) << std::endl; // acdef
    std::cout << (char*)My_memcpy(src2 + 1, src2, 2) << std::endl; // abdef
    std::cout << (char*)My_memcpy(src3 + 1, src3, 3) << std::endl; // abcef
}

void Test_memmove()
{
    char src1[] = {"abcdef"};
    char src2[] = {"abcdef"};
    char src3[] = {"abcdef"};

    std::cout << (char*)My_memmove(src1 + 1, src1, 1) << std::endl; // acdef
    std::cout << (char*)My_memmove(src2 + 1, src2, 2) << std::endl; // abdef
    std::cout << (char*)My_memmove(src3 + 1, src3, 3) << std::endl; // abcef
}

int main(void)
{
    // Test_strcpy();
    // Test_strcat();
    // Test_strstr();
    // Test_memcpy();
    Test_memmove();
    return 0;
}
