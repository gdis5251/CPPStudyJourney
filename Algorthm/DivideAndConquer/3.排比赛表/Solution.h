#pragma once 
#include <iostream>

class Solution
{
public:
    static void plan(int arr[1024][1024], int k)
    {
    //先手动定义一个基础块
    arr[0][0] = 1;
    arr[0][1] = 2;
    arr[1][0] = 2;
    arr[1][1] = 1;

    int n = 2;

    for (int i = 0; i < k - 1; i++)
    {
        int tmp = n;
        n *= 2;

        for (int j = 0; j < tmp; j++)
        {
            for (int t = 0; t < tmp; t++)
            {
                arr[j + tmp][t] = arr[j][t] + tmp;
                arr[j][t + tmp] = arr[j][t] + tmp;
                arr[j + tmp][t + tmp] = arr[j][t];
            }
        }
    }
    }
static void print(int arr[1024][1024], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
};
