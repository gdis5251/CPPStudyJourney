#include "AVITree.hpp"

void TestAVLTree()
{
	AVLTree<int> t;
	t.Insert(16);
	t.Insert(3);
	t.Insert(7);
	t.Insert(11);
	t.Insert(9);
	t.Insert(26);
	t.Insert(18);
	t.Insert(14);
	t.Insert(15);

	t.InorderTraversal();
	std::cout << t.JudgeIfBalance() << std::endl;


	t.Erase(16);
	t.InorderTraversal();
	std::cout << t.JudgeIfBalance() << std::endl;

	t.Erase(15);
	t.InorderTraversal();
	std::cout << t.JudgeIfBalance() << std::endl;

	t.Erase(14);
	t.InorderTraversal();
	std::cout << t.JudgeIfBalance() << std::endl;

	t.Erase(18);
	t.InorderTraversal();
	std::cout << t.JudgeIfBalance() << std::endl;

	t.Erase(11);
	t.InorderTraversal();
	std::cout << t.JudgeIfBalance() << std::endl;
	
}


int main(void)
{
	TestAVLTree();

	return 0;
}