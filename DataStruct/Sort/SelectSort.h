#pragma once 
#include <algorithm>
#include <iostream>
#include <vector>

void SelectSort(std::vector<int>& arr)
{
    for (int i = 0; i < (int)arr.size(); i++)
    {
        int j;
        int min = i;
        for (j = i + 1; j < (int)arr.size(); j++)
        {
            if (arr[j] < arr[min])
              min = j;
        }

        std::swap(arr[i], arr[min]);
    }
}

void SelectSortOP(std::vector<int>& arr)
{
   int minSpace = 0;
   int maxSpace = arr.size() - 1;

   while (minSpace < maxSpace)
   {
      int min = minSpace;
      int max = maxSpace;

      for (int i = min; i <= maxSpace; i++)
      {
        if (arr[i] < arr[min])
            min = i;
        if (arr[i] > arr[max])
            max = i;
      }

      std::swap(arr[minSpace], arr[min]);
      std::swap(arr[maxSpace], arr[max]);

      minSpace++;
      maxSpace--;
   }
}
