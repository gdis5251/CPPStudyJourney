#include "RBTree.hpp"
#include <time.h>

void TestRBTree()
{
    RBTree<int, int> rb;
#if 0
    int arr[] = {4, 5, 2, 6, 7, 8, 9, 1, 3};

    for (const auto& e : arr)
    {
        rb.Insert(std::make_pair(e, e));
    }
#endif

	srand(time(nullptr));
	int num = (rand() % 100);
	for (int i = 0; i < num; i++)
	{
		int input = rand();
		rb.Insert(std::make_pair(input, input));
	}

    rb.Inorder();
    std::cout << rb.IsValidRBTree() << std::endl;
}

int main(void)
{
    TestRBTree();

    return 0;
}
