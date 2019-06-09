#pragma once
#include <iostream>
#include <vector>

class BitSet
{
public:
    BitSet(int range)
        :bit_((range >> 5) + 1)
    {}
    ~BitSet() {}

    // 置1
    void set(int num)
    {
        int index = num >> 5;
        int pos = index % 32;

        bit_[index] |= (1 << pos);
    }

    // 置0
    void reset(int num)
    {
        int index = num >> 5;
        int pos = index % 32;

        bit_[index] &= ~(1 << pos);
    }

    bool test(int num)
    {
        int index = num >> 5;
        int pos = index % 32;

        return bit_[index] & (1 << pos);
    }
private:
    std::vector<int> bit_;
};

