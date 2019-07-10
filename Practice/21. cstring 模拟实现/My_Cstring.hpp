#pragma once
#include <iostream>
#include <assert.h>

int My_Strlen1(const char* str)
{
    assert(str != NULL);

    int count = 0;
    while ('\0' != *str++)
    {
        count++;
    }

    return count;
}

int My_Strlen2(const char* str)
{
    assert (str != NULL);

    if ('\0' == *str)
    {
        return 0;
    }
    else
    {
        return 1 + My_Strlen2(str + 1);
    }
}

int My_Strlen3(const char* str)
{
    assert(str != NULL);

    const char* p = str;
    while ('\0' != *p++);

    p--;
    return p - str;
}

char* My_strcpy(char* dest, const char* src)
{
    assert(dest != NULL && src != NULL);

    char* ret = dest;

    while ((*dest++ = *src++))
    {}

    return ret;
}

char* My_strcat(char* dest, const char* src)
{
    assert(dest != NULL && src != NULL);

    char* ret = dest;

    while (*dest != '\0')
    {
        dest++;
    }

    while (*dest++ = *src++);

    return ret;
}

char* My_strstr(const char* str1, const char* str2)
{
    assert(str1 != NULL && str2 != NULL);

    if ('\0' == *str2)
    {
        return NULL;
    }

    char* ret = (char*)str1;
    char* substr = (char*)str2;
    char* s1 = NULL;

    while (*ret != '\0')
    {
        s1 = ret;
        substr = (char*)str2;

        while (*s1 != '\0' && *substr != '\0' && *s1 == *substr)
        {
            s1++;
            substr++;
        }

        if ('\0' == *substr)
        {
            return ret;
        }
        else
        {
            ret++;
        }
    }

    return NULL;
}

void* My_memcpy(void* dest, const void* src, size_t count)
{
    assert(dest != NULL && src != NULL);

    char* my_dest = static_cast<char*>(dest);
    const char* my_src = static_cast<const char*>(src);

    while (count--)
    {
        *my_dest++ = *my_src++;
    }

    return dest;
}

void* My_memmove(void* dest, const void* src, size_t count)
{
    assert(dest != NULL && src != NULL);

    char* my_dest = static_cast<char*>(dest);
    const char* my_src = static_cast<const char*>(src);

    // 考虑覆盖的情况
    if (my_src < my_dest && (my_src + count) >= my_dest)
    {
        // 会产生覆盖的情况，从后往前赋值
        my_dest = my_dest + count - 1;
        my_src = my_src + count - 1;

        while (count--)
        {
            *my_dest-- = *my_src--;
        }
    }
    else
    {
        while (count--)
        {
            *my_dest-- = *my_src--;
        }
    }

    return dest;
}
