#include "BSTree.hpp"

int main(void)
{
	BSTree<int> bt;

	bt.Insert(4);
	bt.Insert(6);
	bt.Insert(7);
	bt.Insert(9);
	bt.Insert(3);
	bt.Insert(2);
	bt.Insert(1);
	bt.Inorder();

    bt.Erase(4);
	bt.Inorder();

	return 0;
}
