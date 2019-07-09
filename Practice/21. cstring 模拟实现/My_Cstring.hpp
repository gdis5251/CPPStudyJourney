#pragma once
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