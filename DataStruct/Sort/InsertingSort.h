#pragma once 

#include <iostream>
#include <vector>

void InsertingSort(std::vector<int>& arr)
{
    for (int i = 0; i < (int)arr.size(); i++)
    {
        int k = arr[i];
        int j;

        for (j = i - 1; j >= 0; j--)
        {
            if (arr[j] <= k)
                break;
            else 
            {
                arr[j + 1] = arr[j]; 
            }
        }

        arr[j + 1] = k;
    }
}

void InsertingSortDown(std::vector<int>& arr)
{
    for (int i = 0; i < (int)arr.size(); i++)
    {
        int k = arr[i];
        int j;

        for (j = i - 1; j >= 0; j--)
        {
            if (arr[j] >= k)
                break;
            else 
            {
                arr[j + 1] = arr[j];
            }
        }

        arr[j + 1] = k;
    }
}
