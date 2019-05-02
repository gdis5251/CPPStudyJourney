#pragma once 
#include <iostream>
#include <vector>

void _QuickSort(std::vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;
    
    int tmp = left;
    int i = left;
    int j = right;
    while (i < j)
    {
        while (i < j && arr[j] >= arr[tmp])
            j--;

        while (i < j && arr[i] <= arr[tmp])
            i++;

        if (i < j)
        {
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[tmp], arr[i]);

    _QuickSort(arr, left,i - 1);
    _QuickSort(arr, i + 1, right);
}

void QuickSort(std::vector<int>& arr)
{
    _QuickSort(arr, 0, arr.size() - 1);
}
