#include <iostream>
#include <vector>
#include <algorithm>

int main(void)
{
    std::vector<int> arr{4, 5, 2, 7, 1, 0, 9};

    for (const auto& e : arr)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    std::sort(arr.begin(), arr.end(), [](const int lhs, const int rhs) {
        return lhs > rhs;
    });
    for (const auto& e : arr)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;


    return 0;
}