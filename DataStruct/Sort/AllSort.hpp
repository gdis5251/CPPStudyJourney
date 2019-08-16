#pragma once
#include <iostream>
#include <vector>
#include <stack>


// 插入排序
//
// 时间复杂度
// a. 最好：O(N)    已经有序的情况
// b. 平均：O(N^2)  
// c. 最坏：O(N^2)  已经有序是逆序
//
// 空间复杂度
// O(1)
//
// 稳定性：稳定
void InsertSort(std::vector<int>& arr)
{
    // 外循环实现减治过程
    // 一次取一个数，插入到前面的有序区间里
    for (size_t i = 1; i < arr.size(); i++)
    {
        int key = arr[i];
        // 内部的循环实现的是插入的过程
        // j 从 [i - 1, 0]
        // 如果 arr[j] > key， 往后搬
        // 如果 arr[j] == key, 跳出循环（保证了稳定性）
        // 如果 arr[j] < key, 跳出循环
        int j;
        for (j = i - 1; j >= 0 && arr[j] > key; j--)
        {
            arr[j + 1] = arr[j];
        }

        // j + 1 就是要插入的位置
        arr[j + 1] = key;
    }
}


// 希尔排序
// 希尔排序是插入排序的优化版本
// 在插入排序之前，尽可能的让数据有序
// 分组插排
// 通过维护一个 gap 来实现分组
// gap 初始化 为 gap = arr.size() / 3 + 1
// 后面 gap = gap / 3 + 1
//
// 时间复杂度
// a. 最好： O(N)
// b. 平均： O(N^1.2) ~ O(N^1.3)
// c. 最坏： O(N^2) 这里虽然跟插入排序的最坏时间复杂度一样
// 可是它把遇到最坏情况的概率变小了
//
// 空间复杂度
// O(1)
//
// 稳定性：不稳定。
// 一旦分组，很难保证相同的数在一个组里

// 可以设置 gap 间隔的插入排序
void InsertSortWithGap(std::vector<int>& arr, int gap)
{
    for (size_t i = gap; i < arr.size(); i++)
    {
        int key = arr[i];
        int j;
        for (j = i - gap; j >= 0 && arr[j] > key; j -= gap)
        {
            arr[j + 1] = arr[j];
        }

        // j + 1 就是要插入的位置
        arr[j + gap] = key;
    }
}

// 希尔排序
void ShellSort(std::vector<int>& arr)
{
    int gap = arr.size();
    while (true)
    {
        gap = gap / 3 + 1;

        InsertSortWithGap(arr, gap);

        // 如果 gap == 1 ，说明上次排序已经排完了整个数组
        if (gap == 1)
            break;
    }
}


// 选择排序
//
// 每次遍历无序区间，找到最大数的下标
// 1. 交换最大的数和无序区间的最后一个数
// 2. 区间 size - 1
// 3. 重新循环

// 时间复杂度
// 最好 = 最坏 = 平均 = O(N^2)
//
// 空间复杂度
// O(1)
//
// 稳定性：不稳定。 
// {9， 4， 3， 5a， 5b} 无法保证5a在5b前
void SelectSort(std::vector<int>& arr)
{
    for (int i = 0; i < (int)arr.size() - 1; i++)
    {
        int max = 0;
        for (int j = 0; j < (int)arr.size() - i; j++)
        {
            if (arr[j] > arr[max])
                max = j;
        }

        std::swap(arr[max], arr[arr.size() - 1 - i]);
    }
}


// 堆排序--》升序建大堆
//
// 时间复杂度
// 最好 = 平均 = 最坏 = O(N * LogN)
// 向下调整时间复杂度是 O(LogN)
// 建堆的时间复杂度是 O(N * LogN)
// 排序的时间复杂是 O(O * LogN)
//
// 空间复杂度 O(1)
//
// 稳定性：不稳定
// 向下调整过程中，无法保证相等数的前后关系
//
// 向下调整
// void AdJustDown(std::vector<int>& arr, int size, int root)
// {
//     // 如果此时 root 是叶子结点，调整结束退出
//     if (root * 2 + 1 >= size)
//         return;
// 
//     // 找到最大的孩子
//     int left = (root * 2) + 1;
//     int max = left;
//     int right = (root * 2) + 2;
//     if (right < size && arr[right] > arr[left])
//     {
//         max = right;
//     }
// 
//     // 判断当前 root 是否小于叶子结点
//     if (arr[root] < arr[max])
//     {
//         std::swap(arr[root], arr[max]);
//         AdJustDown(arr, size, max);
//     }
//     
//     return;
// }
// // 建堆
// void CreateHeap(std::vector<int>& arr)
// {
//     // 从第一个双亲结点开始向下调整
//     // 逐渐向上走，直到根结点向下调整结束
//     for (int i = (int)(arr.size() - 2) / 2; i >= 0; i--)
//     {
//         AdJustDown(arr, (int)arr.size(), i);
//     }
// }
// // 堆排序
// void HeapSort(std::vector<int>& arr)
// {
//     // 先建堆
//     CreateHeap(arr);
// 
//     // 然后每次将堆顶元素和最后一个元素交换
//     // size - 1
//     // 向下调整
//     for (int i = 0; i < (int)arr.size(); i++)
//     {
//         std::swap(arr[0], arr[arr.size() - i - 1]);
// 
//         AdJustDown(arr, arr.size() - i - 1, 0);
// 
//     }
// }

// 向下调整
void AdjustDown(std::vector<int>& arr, int size, int root)
{
    // 如果此时的结点是叶子结点退出
    if (root * 2 + 1 >= size)
    {
        return;
    }

    int max = root * 2 + 1;
    if (root * 2 + 2 < size && arr[root * 2 + 2] > arr[root * 2 + 1])
    {
        max += 1;
    }

    // 比较当前结点和最大的叶子结点的大小
    if (arr[root] < arr[max])
    {
        std::swap(arr[root], arr[max]);

        AdjustDown(arr, size, max);
    }

    return;
}

// 建堆
void CreateHeap(std::vector<int>& arr)
{
    // 从最后一个非叶子结点开始向下调整
    for (int i = (arr.size() - 2) / 2; i >= 0; i--)
    {
        AdjustDown(arr, arr.size(), i);
    }
}

// 排序
void HeapSort(std::vector<int>& arr)
{
    // 先建堆
    CreateHeap(arr);

    // 将堆顶元素和最后一个元素交换，进行减置算法
    for (int i = 0; i < arr.size() - 1; i++)
    {
        std::swap(arr[0], arr[arr.size() - 1 - i]);

        AdjustDown(arr, arr.size() - i - 1, 0);
    }
}


// 冒泡排序
//
// 时间复杂度
// 最好 ：O(N)
// 最坏|平均：O(N^2) 逆序
//
// 空间复杂度
// O(1)
//
// 稳定性：稳定

void BubbleSort(std::vector<int>& arr)
{
    for (int i = 0; i < (int)arr.size(); i++)
    {
        int sorted = 0;
        for (int j = 0; j < (int)arr.size() - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                sorted = 1;
            }
        }

        if (sorted == 0)
            break;
    }
}



// 快速排序
// [left, right]
// 1. 在要排序的区间内选择一个基准值
//  具体方法：
//  1）选择区间最右边这个数 arr[right]
//
// 2. 遍历整个区间，做一些数据交换，达到效果：
// 比基准值小的数，放到基准值左侧
// 比基准值大的数，放到基准值右侧
//
// 3. 分治算法：把一个问题变成两个同样的小问题
//
// 4. 用递归或非递归
// 终止条件：
//  1）分出来的小区间没有数了：分出的区间 size == 0
//  2）分出来的小区间已经有序了：区间的 size == 1

// 时间复杂度
// 最好|平均：O(N * LogN)
// 遍历一遍数组：O(N)
// 高度: Log N
//
// 最差：O(N^2) 
// 如果已经有序，就是一个单支树。
//
// 空间复杂度
// O(LogN) ~ O(N)  
// 递归调用的深度（二叉树的高度）
//
// 稳定性：不稳定

// Parition 三种方式
// hoare 版本
#if 0
int Parition(std::vector<int>& arr, int left, int right)
{
    int div = right;

    while (left < right)
    {
        // 比较的时候要加 = 的情况
        // 比如说一个例子 1 1 1 1 1 
        // 如果不加等于 就成死循环了
        
        // 先从左边找到一个比基准值大的数字
        while (left < right && arr[left] <= arr[div])
            left++;

        // 从右边开始找一个比基准大小的数字
        while (left < right && arr[right] >= arr[div])
            right--;

        if (left < right)
            std::swap(arr[left], arr[right]);
    }

    std::swap(arr[left], arr[div]);

    return left;
}

// 挖坑法
int ParitionDiggintPit(std::vector<int>& arr, int left, int right)
{
    int base_value = arr[right];
    int pit = right;
    int div = right;

    while (left < right)
    {
        while (left < right && arr[left] <= arr[div])
        {
            left++;
        }
        // 找到一个比基准值大的值，将这个值填入坑中
        arr[pit] = arr[left];
        // 更新坑的位置
        pit = left;

        while (left < right && arr[right] >= arr[div])
        {
            right--;
        }
        // 找到了一个比基准值小的值，将这个值填入坑中
        arr[pit] = arr[right];
        // 更新坑的位置
        pit = right;
    }

    arr[pit] = base_value;

    return pit;
}

// 拉窗帘法
int ParitionSlideWindow(std::vector<int>& arr, int left, int right)
{
    int div = right;
    int d = 0;
    int c = 0;

    while (c < div)
    {
        // 始终让滑动窗口内部的值大于基准值
        if (arr[c] >= arr[div])
        {
            c++;
        }
        else
        {
            if (d < c)
                std::swap(arr[d], arr[c]);
            
            d++;
            c++;
        }
    }

    // 走到这表示 d 之前的值都比基准值小
    // 把基准值和 arr[d] 交换即可
    std::swap(arr[d], arr[div]);

    return d;
}

void _QuickSort(std::vector<int>& arr, int left, int right)
{
    // 终止条件
    if (left >= right)
        return;

    int div; // 基准值取最右边的值
    div = ParitionSlideWindow(arr, left, right); // 遍历 arr[left, right],把小的放左，大的放右

    _QuickSort(arr, left, div - 1);     
    _QuickSort(arr, div + 1, right);
}
#endif

int parition(std::vector<int>& arr, int left, int right)
{
    int div = right;

    // 大循环调整
    while (left < right)
    {
        // 从左边找一个比基准值大的
        while (left < right && arr[left] <= arr[div])
        {
            left++;
        }

        // 从右边找一个比基准值小的
        while (left < right && arr[right] >= arr[div])
        {
            right--;
        }

        if (left < right)
        {
            std::swap(arr[left], arr[right]);
        }
    }

    // 走到这说明 left 和 right 重合 
    std::swap(arr[left], arr[div]);
    return left;
}

// 左闭右闭
void _QuickSort(std::vector<int>& arr, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int div = parition(arr, left, right);

    _QuickSort(arr, left, div - 1);
    _QuickSort(arr, div + 1, right);
}

void __QuickSort(std::vector<int>& arr, int left, int right)
{
    std::stack<int> s;
    s.push(left);
    s.push(right);

    while (!s.empty())
    {
        int c_right = s.top();
        s.pop();
        int c_left = s.top();
        s.pop();

        int div = parition(arr, c_left, c_right);
        
        if (c_left < div - 1)
        {
            s.push(c_left);
            s.push(div - 1);
        }

        if (div + 1 < c_right)
        {
            s.push(div + 1);
            s.push(c_right);
        }
    }
}

void QuickSort(std::vector<int>& arr)
{
    __QuickSort(arr, 0, (int)arr.size() - 1);
}





// 归并排序
// 对一个大数组进行排序的问题
// 变成了对左右两个小数组进行排序的问题o
//
// 时间复杂度
// 最好|平均|最坏：O(N * LogN)
//
// 空间复杂度
// O(N)
//
// 稳定性：稳定
//
// 优点：可以对硬盘上的数据进行排序

// 合并两个有序数组
// arr[left, mid)
// arr[mid, right)
// 该操作的
// 时间复杂度 
// O(N)
//
// 空间复杂度
// O(N)
#if 0
void Merge(std::vector<int>& arr, int left, int mid, int right, std::vector<int>& tmp)
{

    int left_index = left;
    int right_index = mid;
    int index = 0;

    while (left_index < mid && right_index < right)
    {
        if (arr[left_index] <= arr[right_index]) // <= 之所以加 = 是为了保证稳定性
        {
            tmp[index++] = arr[left_index++];
        }
        else
        {
            tmp[index++] = arr[right_index++];
        }
    }

    while (left_index < mid)
    {
        tmp[index++] = arr[left_index++];
    }

    while (right_index < right)
    {
        tmp[index++] = arr[right_index++];
    }
    
    for (int i = 0; i < right - left; i++)
    {
        arr[left + i] = tmp[i];
    }
}

void _MergeSort(std::vector<int>& arr, int left, int right, std::vector<int>& tmp)
{
    if (right == left + 1)// 区间内还剩一个数
    {
        return;
    }
    if (left >= right)// 区间内没有数了
    {
        return;
    }

    int mid = left + (right - left) / 2;
    //  区间被分成左右两个小区间
    //  [left, mid)
    //  [mid, right)
    //  先把左右两个小区间进行排序，分治算法，递归解决
    
    _MergeSort(arr, 0, mid, tmp);
    _MergeSort(arr, mid, right, tmp);

    // 左右两个小区间已经有序
    // 合并两个有序数组
    Merge(arr, left, mid, right, tmp);
}

void MergeSort(std::vector<int>& arr)
{
    std::vector<int> tmp(arr.size());
    _MergeSort(arr, 0, arr.size(), tmp);
}
#endif 

void _Merge(std::vector<int>& arr, int left, int mid, int right, std::vector<int>& tmp)
{
    // 设置左右数组的开始下标
    int left_index = left;
    int right_index = mid;
    int index = 0;

    while (left_index < mid && right_index < right)
    {
        if (arr[left_index] < arr[right_index])
        {
            tmp[index++] = arr[left_index++];
        }
        else
        {
            tmp[index++] = arr[right_index++];
        }
    }

    // 将剩余没有进行排序的数字全部入数组
    while (left_index < mid)
    {
        tmp[index++] = arr[left_index++];
    }
    while (right_index < right)
    {
        tmp[index++] = arr[right_index++];
    }

    // 将 tmp 数组排好序的部分给 arr 重新赋值
    for (int i = 0; i < right - left; i++)
    {
        arr[i + left] = tmp[i];
    }
}

void _MergeSort(std::vector<int>& arr, int left, int right, std::vector<int>& tmp)
{
    // 判断跳出条件
    // 只剩下一个数跳出或者区间内没有数了，跳出
    if (left + 1 == right || left >= right)
    {
        return;
    }

    // 算出中间数下标，若为偶数个数字，中间数为中间两个数的偏右的数字
    // 这个算的原因是防止溢出
    int mid = left + (right - left) / 2;

    _MergeSort(arr, left, mid, tmp);
    _MergeSort(arr, mid, right, tmp);

    _Merge(arr, left, mid, right, tmp);

}

void MergeSort(std::vector<int>& arr)
{
    // 建立一个 O(N) 的空间
    std::vector<int> tmp(arr.size(), 0);
    // 调用 _MergeSort 去划分空间
    // 给的区间是左闭右开的
    _MergeSort(arr, 0, arr.size(), tmp);
}
