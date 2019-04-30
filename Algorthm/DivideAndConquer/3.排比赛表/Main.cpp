#include <iostream>
#include "Solution.h"

int main(void)
{
    int k = 0;
    std::cin >> k;

    //n为2的k次方
    int n = 1 << k;
    int arr[1024][1024] = {0};

    Solution::plan(arr, k);
    Solution::print(arr, n);

    return 0;
}
