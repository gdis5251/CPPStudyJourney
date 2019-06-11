#pragma once
#include "HashTableOpen.hpp"
#include <string>

template <class K>
struct HFunc
{
    const K& operator()(const K& key)
    {
        return key;
    }
};

template <>
struct HFunc<std::string>
{
	size_t operator()(const std::string& str)
	{
		size_t hash = 0;
		for (const auto& e : str)
		{
			hash = hash * 131 + e;
		}
		return hash;
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

	iterator begin()
	{
		return ht_.begin();
	}

	iterator end()
	{
		return ht_.end();
	}

	V& operator[](const K& key)
	{
		return (*(ht_.insert(std::make_pair(key, V())).first)).second;
	}

    std::pair<iterator, bool> insert(const std::pair<K, V>& data)
    {
        return ht_.insert(data);
    }

	iterator find(const K& key)
	{
		return ht_.find(key);
	}

	bool erase(const K& key)
	{
		return ht_.erase(key);
	}
private:
    HashTable<K, std::pair<K, V>, MapKeyOfValue, HFunc> ht_;

};


template <class K, class HFunc = HFunc<K> >
class UnorderSet
{
	struct SetKeyOfValue
	{
		const K& operator()(const K& data)
		{
			return data;
		}
	};
public:
	typedef typename HashTable<K, K, SetKeyOfValue, HFunc>::iterator iterator; 

	iterator begin()
	{
		return ht_.begin();
	}

	iterator end()
	{
		return ht_.end();
	}

	std::pair<iterator, bool> insert(const K& data)
	{
		return ht_.insert(data);
	}
private:
	HashTable<K, K, SetKeyOfValue, HFunc> ht_;
};