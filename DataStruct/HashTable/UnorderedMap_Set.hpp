#pragma once
#include "HashTableOpen.hpp"

template <class K>
struct HFunc
{
    const K& operator()(const K& key)
    {
        return key;
    }
};

template <class K, class V, class HFunc = HFunc<K> >
class UnorderedMap
{
    struct MapKeyOfValue
    {
        const K& operator()(const std::pair<K, V>& data)
        {
            return data.first;
        }
    };
public:
    typedef typename HashTable<K, std::pair<K, V>, MapKeyOfValue, HFunc>::iterator iterator;

    std::pair<iterator, bool> insert(const std::pair<K, V>& data)
    {
        return ht_.insert(data);
    }

private:
    HashTable<K, std::pair<K, V>, MapKeyOfValue, HFunc> ht_;

};
