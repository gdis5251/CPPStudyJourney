#pragma once 
#include <iostream>
#include <algorithm>
#include <vector>

// 建大堆
class Heap
{
public:
    Heap()
    {}

    ~Heap()
    {}

    void Push(const int val)
    {
        // 如果这堆为空，直接放到第一个即可
        if (heap_arr_.size() == 0)
        {
            heap_arr_.push_back(val);
            return;
        }
        
        // 否则，先放到最后，然后向上调整
        heap_arr_.push_back(val);
        AdjustUp(heap_arr_.size() - 1);
        
    }

    void Pop()
    {
        // 把堆顶元素和最后一个元素交换
        // 然后 size - 1
        // 然后把堆顶元素向下调整
        std::swap(heap_arr_[0], heap_arr_[heap_arr_.size() - 1]);
        heap_arr_.resize(heap_arr_.size() - 1);

        AdjustDown(0);
    }

    size_t Size()
    {
        return heap_arr_.size();
    }

    bool Empty()
    {
        return heap_arr_.size() == 0;
    }

    int Top()
    {
        return heap_arr_[0];
    }

private:
    void AdjustDown(int pos)
    {
        // if current node is leaf node
        // return
        if (pos * 2 + 1 >= heap_arr_.size())
        {
            return;
        }

        // if there is a right node
        // And the right node is lager then left node
        // rewrite max
        int max = pos * 2 + 1;
        if (pos * 2 + 2 < heap_arr_.size())
        {
            if (heap_arr_[pos * 2 + 2] > heap_arr_[max])
            {
                ++max;
            }
        }

        // if current node is lager then the max node
        // return
        if (heap_arr_[pos] > heap_arr_[max])
        {
            return;
        }

        // change
        // And continue Adjust down
        std::swap(heap_arr_[pos], heap_arr_[max]);

        AdjustDown(max);
    }

    void AdjustUp(int pos)
    {
        // 如果已经是根结点了，就停下来
        if (pos == 0)
        {
            return;
        }

        int parent = (pos - 1) / 2;
        // 如果当前值比父结点小，停止
        if (heap_arr_[parent] > heap_arr_[pos])
        {
            return;
        }

        // 交换
        std::swap(heap_arr_[parent], heap_arr_[pos]);
        
        AdjustUp(parent);
    }

private:
    std::vector<int> heap_arr_;
};
