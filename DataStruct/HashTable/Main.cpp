#include "HashTableClose.hpp"

int main()
{
    HashTable<int, int> hash;

    hash.insert(std::make_pair(1, 1));
    hash.insert(std::make_pair(2, 1));
    hash.insert(std::make_pair(3, 1));
    hash.insert(std::make_pair(4, 1));
    hash.insert(std::make_pair(5, 1));
    hash.insert(std::make_pair(6, 1));
    hash.insert(std::make_pair(7, 1));
    hash.insert(std::make_pair(8, 1));

    std::cout << hash.find(std::make_pair(2, 1))->kv_.first << std::endl;
    
    std::cout << hash.erase(std::make_pair(5, 1)) << std::endl;



    return 0;
}

