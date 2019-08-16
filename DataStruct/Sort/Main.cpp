#include "AllSort.hpp"
#include "PrintArr.h"

int main(void)
{
    std::vector<int> arr = {4, 0, 5, 1, 9, 7, 5, 2, 8};
    //InsertingSort(arr);
    //PrintArray(arr);
    //InsertingSortDown(arr);
    //ShellSort(arr);    
    //SelectSort(arr);
    //SelectSortOP(arr);
    //HeapSort(arr);
    //BubbleSort(arr);
    //QuickSort(arr);
    //MergeSort(arr);
    
    // InsertSort(arr);
    // PrintArray(arr);

    // ShellSort(arr);
    // PrintArray(arr);

    // SelectSort(arr);
    // PrintArray(arr);

     HeapSort(arr);
    // PrintArray(arr);

    // BubbleSort(arr);
    
    // QuickSort(arr);
    // MergeSort(arr);
    PrintArray(arr);
    return 0;
}
