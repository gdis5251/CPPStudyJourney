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
	v1.insert(it, 10);
	//10 1 2 3 4 5

	it += 2;
	v1.insert(it, 30);
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
	//std::vector<int> v(4, 100);

	// constructors used in the same order as described above:
	Gerald::Vector<int> first; // empty vector of ints
	Gerald::Vector<int> second(4u, 100);//这里有点问题，如果不加u，编译器会自动调用第三种（给迭代器用的）构造函数

	Gerald::Vector<int> third(second.begin(), second.end()); // iterating through second
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
	//strV.push_back("4444");
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



void TestVector2()
{
	// 使用push_back插入4个数据
	Gerald::Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	// 使用迭代器进行遍历打印
	Gerald::Vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	// 使用迭代器进行修改
	it = v.begin();
	while (it != v.end())
	{
		*it *= 2;
		++it;
	}
	PrintVector(v);
}


void TestVector4()
{
	size_t sz;
	Gerald::Vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i = 0; i < 100; ++i) {
		foo.push_back(i);
		if (sz != foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	// resverse
	Gerald::Vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100); // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i = 0; i < 100; ++i) {
		bar.push_back(i);
		if (sz != bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	// resize
	Gerald::Vector<int> myvector;
	// set some initial content:
	for (int i = 1; i < 10; i++)
	myvector.push_back(i);
	myvector.resize(5);
	myvector.resize(8, 100);
	myvector.resize(12);
	std::cout << "myvector contains:";
	
	for (size_t i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

// find / insert / erase
void TestVector5()
{
	int a[] = { 1, 2, 3, 4 };
	Gerald::Vector<int> v(a, a + sizeof(a) / sizeof(int));
	// 使用find查找3所在位置的iterator
	Gerald::Vector<int>::iterator pos = find(v.begin(), v.end(), 3);
	// 在pos位置之前插入30
	v.insert(pos, 30);
	// 1 2 30 3 4
	Gerald::Vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
	pos = find(v.begin(), v.end(), 3);
	// 删除pos位置的数据
	v.erase(pos);
	it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
	//1 2 30 4
}


// operator[]
void TestVector6()
{
	int a[] = { 1, 2, 3, 4 };
	Gerald::Vector<int> v(a, a + sizeof(a) / sizeof(int));
	// 通过[]读写第0个位置。
	v[0] = 10;
	cout << v[0] << endl;
	// 通过[i]的方式遍历vector
	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;
		
	Gerald::Vector<int> swapv;
	swapv.swap(v);
	cout << "v data:";
	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;
	cout << "swapv data:";
	for (size_t i = 0; i < swapv.size(); ++i)
	{
		cout << swapv[i] << " ";
	}
	cout << endl;
}

// iterator失效问题
void TestVector7()
{
	int a[] = { 1, 2, 3, 4 };
	Gerald::Vector<int> v(a, a + sizeof(a) / sizeof(int));
	// 使用find查找3所在位置的iterator
	Gerald::Vector<int>::iterator pos = find(v.begin(), v.end(), 3);
	// 删除pos位置的数据，导致pos迭代器失效。
	pos = v.erase(pos);
	cout << *pos << endl; // 此处会导致非法访问
	// 在pos位置插入数据，导致pos迭代器失效。
	// insert会导致迭代器失效，是因为insert可
	// 能会导致增容，增容后pos还指向原来的空间，而原来的空间已经释放了。
	pos = find(v.begin(), v.end(), 3);
	v.insert(pos, 30);
	cout << *pos << endl; // 此处会导致非法访问
	// 实现删除v中的所有偶数
	// 下面的程序会崩溃掉，如果是偶数，erase导致it失效
	// 对失效的迭代器进行++it，会导致程序崩溃
	Gerald::Vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			v.erase(it);
			continue;
		}
		++it;
	}
	// 以上程序要改成下面这样，erase会返回删除位置的下一个位置
	it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
			it = v.erase(it);
		else
			++it;
	}
}
	

int main(void)
{
	TestVector7();
	return 0;
}