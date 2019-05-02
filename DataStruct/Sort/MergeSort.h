#pragma once 
#include <iostream>
#include <vector>

void Merge(std::vector<int>& arr, int left, int mid, int right)
{
    int *tmp = new int[right - left + 1];
    int p1 = left;
    int p2 = mid + 1;
    int k = 0;

    while (p1 <= mid && p2 <= right)
    {
         if (arr[p1] <= arr[p2])
             tmp[k++] = arr[p1++];
         else 
             tmp[k++] = arr[p2++];
    }

    while (p1 <= mid)
        tmp[k++] = arr[p1++];
    while (p2 <= right)
        tmp[k++] = arr[p2++];

    for (int i = left, k = 0; i <= right; i++, k++)
    {
        arr[i] = tmp[k];
    }

    delete[] tmp;
}

void _MergeSort(std::vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = (left + right) / 2;
    _MergeSort(arr, left, mid);
    _MergeSort(arr, mid + 1, right);
    Merge(arr, left, mid, right);
}

void MergeSort(std::vector<int>& arr)
{
    _MergeSort(arr, 0, (int)arr.size() - 1);
}

