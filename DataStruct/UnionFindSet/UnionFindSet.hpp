#pragma once
#include <iostream>
#include <vector>


class UnionFindSet
{
public:
    UnionFindSet(int n)
        :ufs_(n, -1)
    {}

    bool Union(int x, int y)
    {
        int root1 = Find(x);
        int root2 = Find(y);

        if (root1 == root2)
        {
            return false;
        }
        
        ufs_[root1] += ufs_[root2];
        ufs_[root2] = root1;

        return true;
    }

    int Count()
    {
        int count = 0;
        for (const auto& e : ufs_)
        {
            if (e < 0)
            {
                count++;
            }
        }

        return count;
    }

private:
    int Find(int x)
    {
        while (ufs_[x] >= 0)
        {
           x = ufs_[x]; 
        }

        return x;
    }
private:
    std::vector<int> ufs_;
};



