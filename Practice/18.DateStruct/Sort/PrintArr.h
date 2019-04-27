#pragma once
#include <iostream>
#include <vector>

void PrintArray(const std::vector<int>& arr)
{
   for (size_t i = 0; i < arr.size(); i++) 
   {
      std::cout << arr[i] << std::endl;
   }
   std::cout << std::endl;
}
