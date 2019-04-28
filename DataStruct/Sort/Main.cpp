#include "InsertingSort.h"
#include "PrintArr.h"

int main(void)
{
    std::vector<int> arr = {4, 5, 1, 9, 7, 5, 2, 8};
    InsertingSort(arr);
    PrintArray(arr);
    InsertingSortDown(arr);
    PrintArray(arr);

    return 0;
}
