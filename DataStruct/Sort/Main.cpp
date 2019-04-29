#include "InsertingSort.h"
#include "PrintArr.h"
#include "ShellSort.h"
#include "SelectSort.h"
#include "HeapSort.h"

int main(void)
{
    std::vector<int> arr = {4, 5, 1, 9, 7, 5, 2, 8};
    //InsertingSort(arr);
    //PrintArray(arr);
    //InsertingSortDown(arr);
    //ShellSort(arr);    
    //SelectSort(arr);
    //SelectSortOP(arr);
    HeapSort(arr);
    PrintArray(arr);

    return 0;
}
