// #include "HashTableClose.hpp"
#include "UnorderedMap_Set.hpp"
#include <ctime>

void TestUnorderedMap()
{
    UnorderedMap<int, int> umap;

    umap.insert(std::make_pair(1, 1));
    umap.insert(std::make_pair(2, 1));
    umap.insert(std::make_pair(3, 1));


}

void TestUnorderedMap1()
{
	UnorderedMap<int, int> umap;
	srand(time(nullptr));

	for (int i = 0; i < 100; i++)
	{
		umap[rand() % 10]++;
	}

	for (const auto& e : umap)
	{
		std::cout << e.first << "   " << e.second << std::endl;
	}
}

void TestUnorderedMap2()
{
	UnorderedMap<int, int> umap;
	srand(time(nullptr));

	for (int i = 0; i < 100; i++)
	{
		umap[rand() % 10]++;
	}

	for (int i = 0; i < 10; i++)
	{
		auto it = umap.find(rand() % 10);
		if (it != umap.end())
			umap.erase((*it).first);
	}

	for (const auto& e : umap)
	{
		std::cout << e.first << std::endl;
	}
}

void TestUnorderedSet()
{
	UnorderSet<int> uset;
	srand(time(nullptr));

	for (int i = 0; i < 100; i++)
	{
		uset.insert(rand() % 10);
	}

	for (const auto& e : uset)
	{
		std::cout << e << std::endl;
	}
}

void TestUnorderedMapString()
{
	UnorderedMap<std::string, int> umap;
	umap.insert(std::make_pair("aaa", 1));
	umap.insert(std::make_pair("bbb", 1));
	umap.insert(std::make_pair("dsa", 1));
	umap.insert(std::make_pair("asd", 1));
	umap.insert(std::make_pair("aaeqwea", 1));
	umap.insert(std::make_pair("gdfgd", 1));


	for (const auto& e : umap)
	{
		std::cout << e.first << "--> " << e.second << std::endl;
	}
}
int main()
{
    TestUnorderedMapString();

    return 0;
}

