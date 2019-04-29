#include "InsertingSort.h"
#include "MergeSort.h"
#include "PrintArr.h"
#include "ShellSort.h"
#include "SelectSort.h"
#include "HeapSort.h"
#include "BubbleSort.h"
#include "QuickSort.h"

int main(void)
{
    std::vector<int> arr = {4, 5, 1, 9, 7, 5, 2, 8};
    //InsertingSort(arr);
    //PrintArray(arr);
    //InsertingSortDown(arr);
    //ShellSort(arr);    
    //SelectSort(arr);
    //SelectSortOP(arr);
    //HeapSort(arr);
    //BubbleSort(arr);
    //QuickSort(arr);
    MergeSort(arr);
    PrintArray(arr);

    return 0;
}
