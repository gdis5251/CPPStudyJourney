#include "RBTree.hpp"

void TestRBTree()
{
    RBTree<int, int> rb;
    int arr[] = {4, 5, 2, 6, 7, 8, 9, 1, 3};

    for (const auto& e : arr)
    {
        rb.Insert(std::make_pair(e, e));
    }

    rb.Inorder();
}

int main(void)
{
    TestRBTree();

    return 0;
}
