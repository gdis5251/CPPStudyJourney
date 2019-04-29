#pragma once 
#include <iostream>
#include <vector>

void BubbleSort(std::vector<int>& arr)
{
    for (int i = 0; i < (int)arr.size(); i++)
    {
        for (int j = 0; j < (int)arr.size() - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}
