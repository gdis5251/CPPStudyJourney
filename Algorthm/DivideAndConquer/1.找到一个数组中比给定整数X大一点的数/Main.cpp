#include <iostream>
#include <vector>
#include <limits.h>

int FindMidPlusNum(std::vector<int>& arr, int x)
{
    if (x > arr[arr.size() - 1])
        return INT_MIN;
    if (x < arr[0])
        return arr[0];

    size_t left = 0;
    size_t right = arr.size();
    size_t mid = (left + right) / 2;

    while (left < right)
    {
        if (arr[mid] > x)
        {
            right = mid;
            mid = (left + right) / 2;
        }
        else if (arr[mid] < x)
        {
            left = mid + 1;
            mid = (left + right) / 2;
        }
        else
            break;
    }

    if (mid == arr.size() - 1)
    {
        return INT_MAX;
    }

    return arr[mid + 1];
}

int main(void)
{
    std::vector<int> arr = {1, 3, 5, 9, 12, 40, 70, 85, 90, 99};
    int x = 0;

    std::cout << "Please Input X Value:";
    while (std::cin >> x)
    {
        int ans = FindMidPlusNum(arr, x);

        if (INT_MIN == ans)
        {
            std::cout << "X bigger than the max in this array." << std::endl;
            std::cout << "Please Input X Value:";
            continue;
        }
        else if (INT_MAX == ans)
        {
            std::cout << "X is the max in this array." << std::endl;
            std::cout << "Please Input X Value:";
            continue;
        }

        std::cout << ans << std::endl;
        std::cout << "Please Input X Value:";
    }
    return 0;
}
