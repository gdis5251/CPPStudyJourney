#pragma once
#include <iostream>
#include <vector>

template <class V>
struct HashNode
{
    HashNode(const V& data = V())
        :next_(nullptr),
        data_(data)
    {}

    HashNode *next_;
    V data_;
};

// 前置声明，为了给迭代器类可以访问哈希表中的元素
template <class K, class V, class KeyOfValue, class HFunc>
class HashTable;

template <class K, class V, class KeyOfValue, class HFunc>
struct _Iterator
{
    typedef HashNode<V> Node;
    typedef Node* pNode;

    typedef _Iterator<K, V, KeyOfValue, HFunc> Self;
    typedef HashTable<K, V, KeyOfValue, HFunc> HashTable;

    pNode node_;
    HashTable* ht_;

    _Iterator(pNode node, HashTable* ht)
        :node_(node),
        ht_(ht)
    {}

    V& operator*()
    {
        return node_->data_;
    }

    V& operator->()
    {
        return &(operator*());
    }

    bool operator!=(const Self& it)
    {
        return node_ != it.node_;
    }

    // 前置++
    Self& operator++()
    {
        if (node_->next_)
        {
            node_ = node_->next_;
            return *this;
        }
        else
        {
            // 如果当前结点的下一个结点为空
            // 找到下一个不为空的链表
            // 返回头结点
            
            // 先获取当前 node 的 index
            KeyOfValue kov;
            size_t index = ht_->GetIndex(kov(node_->data_), ht_->ht_.size());
			index++;

            // 找到第一个不为空的结点
            for (; index < ht_->ht_.size(); index++)
            {
               if (ht_->ht_[index])
               {
                   node_ = ht_->ht_[index];
				   break;
               }
            }

            if (index == ht_->ht_.size())
                node_ = nullptr;
        }

        return *this;
    }

};

// 这里的V不是 map 里的V，是传的值得类型
// 例如 map 传的就是 pair
template <class K, class V, class KeyOfValue, class HFunc>
class HashTable
{
public:
    typedef HashNode<V> Node;
    typedef Node* pNode;

    typedef _Iterator<K, V, KeyOfValue, HFunc> iterator;

	template <class K, class V, class KeyOfValue, class HashFun>
	friend struct _Iterator;

	HashTable()
		:ht_(1),
		size_(0)
	{}
    
    iterator begin()
    {
        for (size_t i = 0; i < ht_.size(); i++)
        {
            if (ht_[i])
                return iterator(ht_[i], this);
        }
        
        return iterator(nullptr, this);
    }

    iterator end()
    {
        return iterator(nullptr, this);
    }

    std::pair<iterator, bool> insert (const V& data)
    {
		// 先判断是否要扩容
		CheckCapacity();

        // 先拿到 data 的 index
        KeyOfValue kov;
        size_t index = GetIndex(kov(data), ht_.size());

        // 然后在该位置上遍历整个链表，看看有没有重复的结点
        pNode cur = ht_[index];
        while (cur)
        {
            if (kov(cur->data_) == kov(data))
                return std::make_pair(iterator(cur, this), false);

            cur = cur->next_;
        }

        // 如果没有相同的结点
        // 申请新结点，插入
        cur = new Node(data);
        // 头插
        cur->next_ = ht_[index];
        ht_[index] = cur;

        size_++;
        return std::make_pair(iterator(cur, this), true);
    }

	iterator find(const K& key)
	{
		size_t index = GetIndex(key, ht_.size());
		KeyOfValue kov;
		
		pNode cur = ht_[index];
		while (cur)
		{
			if (kov(cur->data_) == key)
				return iterator(cur, this);

			cur = cur->next_;
		}

		return end();
	}

	bool erase(const K& key)
	{
		// 先拿到 key 对应的下标
		size_t index = GetIndex(key, ht_.size());
		
		KeyOfValue kov;

		pNode cur = ht_[index];
		pNode prev = nullptr;
		while (cur)
		{
			if (kov(cur->data_) == key)
			{
				if (prev == nullptr)
				{
					ht_[index] = cur->next_;
				}
				else
				{
					prev->next_ = cur->next_;
				}

				delete cur;
				cur = nullptr;
				size_--;

				return true;
			}

			prev = cur;
			cur = cur->next_;
		}

		return true;
	}
private:
    size_t GetIndex(const K& key, size_t sz)
    {
        HFunc hf;
        return hf(key) % sz;
    }

	size_t getNextPrime(const size_t prime)
	{
		static const int PRIMECOUNT = 28;
		static const size_t primeList[PRIMECOUNT] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};

		for (size_t i = 0; i < PRIMECOUNT; ++i)
		{
			if (primeList[i] > prime)
				return primeList[i];
		}

		return primeList[PRIMECOUNT - 1];
	}

	void CheckCapacity()
	{
		if (size_ == ht_.size())
		{
			size_t new_size = getNextPrime(size_);

			std::vector<pNode> tmp(new_size);
			// 重新把 ht_ 里的元素按照 tmp 的 size 插入进去
			KeyOfValue kov;

			for (size_t i = 0; i < ht_.size(); i++)
			{
				pNode cur = ht_[i];
				while (cur)
				{
					pNode next = cur->next_;

					// 获取该结点在新 vector 中的下标
					size_t index = GetIndex(kov(cur->data_), tmp.size());

					// 将该结点插入到新的下标中
					cur->next_ = tmp[index];
					tmp[index] = cur;

					cur = next;
				}
			}

			ht_.swap(tmp);
		}
	}
private:
    std::vector<pNode> ht_;
    int size_;
};
