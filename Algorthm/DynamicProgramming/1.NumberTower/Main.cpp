#include "Solution.h"

int main(void)
{
    std::vector<std::vector<int> > nums;
    int n = 0;
    std::cout << "Please Input How Many Levels The Tower has :> ";
    std::cin >> n;
    nums.resize(n);

    //存储数塔
    for (int i = 0;  i < n; i++)
    {
        nums[i].resize(i + 1);

        for (int j = 0; j <= i; j++)
        {
            std::cin >> nums[i][j];
        }
    }

    std::vector<std::vector<int> > path;
    path.resize(n);
    //初始化路径数组
    for (int i = 0;  i < n; i++)
    {
        path[i].resize(i + 1, 0);
    }

    int ans = Solution::FindMinPath(nums, path);
    
    std::cout << ans << std::endl;

    return 0;
}
