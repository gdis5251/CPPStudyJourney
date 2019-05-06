#pragma once
#include <iostream>
#include <vector>

int max(const int a, const int b)
{
	return a > b ? a : b;
}

class Solution
{
public:
	static int FindMinPath(std::vector<std::vector<int> >& nums, std::vector<std::vector<int> >& path)
	{
		//将最后一行的值给path
		for (size_t i = 0; i < nums[nums.size() - 1].size(); i++)
		{
			path[path.size() - 1][i] = nums[nums.size() - 1][i];
		}

		//找到数值最大的路径，最大值存到ans里
		for (int row = (int)nums.size() - 2; row >= 0; row--)
		{
			for (int col = 0; col < (int)nums[row].size(); col++)
			{
				path[row][col] = max(path[row + 1][col], path[row + 1][col + 1]) + nums[row][col];
			}
		}
		int ans = path[0][0];

		size_t row = 0;
		size_t col = 0;
		for (size_t i = 0; i < path.size(); i++)
		{
			if (i == path.size() - 1)
			{
				std::cout << path[row][col];
				break;
			}

			int j = col;
			//找到该行中最大的数字的小标
			if (path[i + 1][j] > path[i + 1][j + 1])
			{
				row = i + 1;
				col = j;
			}
			else
			{
				row = i + 1;
				col = j + 1;  
			}
			std::cout << path[i][j] - path[row][col] << " ";
		}
		std::cout << std::endl;

		return ans;
	}
};
