#pragma once 
#include <iostream>
#include <vector>

void AdjustDown(std::vector<int>& arr, int size, int root)
{
    if (root * 2 + 1 >= size)
    {
        return;
    }
    
    int left = root * 2 + 1;
    int max = left;
    if (left + 1 < size)
    {
        int right = left + 1;
        if (arr[right] > arr[left])
            max = right;
    }

    if (arr[max] <= arr[root])
    {
        return;
    }

    std::swap(arr[max], arr[root]);

    AdjustDown(arr, size, max);
}

void HeapSort(std::vector<int>& arr)
{
    //建堆
    for (int i = ((int)arr.size() - 2) / 2; i >= 0; i--)
    {
        AdjustDown(arr, (int)arr.size(), i);
    }
    
    //排序
    for (int i = 0; i < (int)arr.size(); i++)
    {
        std::swap(arr[0], arr[arr.size() - 1 - i]);
        AdjustDown(arr, (int)arr.size() - 1 - i, 0);
    }
}


