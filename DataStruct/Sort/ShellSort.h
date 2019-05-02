#pragma once
#include <iostream>
#include <vector>

void SortWithGarp(std::vector<int>& arr, int gap)
{
    for (int i = 0; i < (int)arr.size(); i++)
    {
        int k = arr[i];
        int j;

        for (j = i - gap; j >= 0; j -= gap)
        {
            if (arr[j] <= k) // 如果要从大到小，只需要把 <= 改为 >=
                break;
            else 
            {
                arr[j + gap] = arr[j];
            }
        }

        arr[j + gap] = k;
    }
}

void ShellSort(std::vector<int>& arr)
{
    int gap = arr.size();

    while (1)
    {
        gap = gap / 3 + 1;
        SortWithGarp(arr, gap);
        if (gap == 1)
            break;
    }
}
