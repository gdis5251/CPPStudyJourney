// #include "HashTableClose.hpp"
#include "UnorderedMap_Set.hpp"

void TestUnorderedMap()
{
    UnorderedMap<int, int> umap;

    umap.insert(std::make_pair(1, 1));
    umap.insert(std::make_pair(2, 1));
    umap.insert(std::make_pair(3, 1));
}
int main()
{
    TestUnorderedMap();

    return 0;
}

