#include "Vector.h"

void TestMemberFunc()
{
	Gerald::Vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	//1 2 3 4 5

	Gerald::Vector<int>::iterator it = v1.begin();
	it = v1.insert(it, 10);
	//10 1 2 3 4 5

	it += 2;
	it = v1.insert(it, 30);
	//10 1 30 2 3 4 5

	it = v1.erase(it);
	//10 1 2 3 4 5

	v1.pop_back();
	//10 1 2 3 4

}
#include<vector>
using namespace std;
void TestVector1()
{
	std::vector<int> v(4, 100);

	// constructors used in the same order as described above:
	Gerald::Vector<int> first; // empty vector of ints
	//Gerald::Vector<int> second(4, 100);
	first.push_back(100);
	first.push_back(100);
	first.push_back(100);
	first.push_back(100);

	Gerald::Vector<int> third(first.begin(), first.end()); // iterating through second
	Gerald::Vector<int> fourth(third); // a copy of third
	//the iterator constructor can also be used to construct from arrays:
	int myints[] = { 16, 2, 77, 29 };
	Gerald::Vector<int> fifth(myints, (myints + sizeof(myints) / sizeof(int)));
	std::cout << "The contents of fifth are:";
	for (Gerald::Vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	// 测试T是string时，拷贝问题
	Gerald::Vector<string> strV;
	strV.push_back("1111");
	strV.push_back("2222");
	strV.push_back("3333");
	strV.push_back("4444");
	for (size_t i = 0; i < strV.size(); ++i)
	{
		cout << strV[i] << " ";
	}
	cout << endl;
}
//vector iterator的使用
void PrintVector(const Gerald::Vector<int>& v)
{
	// 使用const迭代器进行遍历打印
	Gerald::Vector<int>::const_iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

int main(void)
{
	TestVector1();
	return 0;
}