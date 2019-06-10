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

    _Iterator(pNode node, HashTable ht)
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
            size_t index = ht_->GetIndex(kov(node_));

            // 找到第一个不为空的结点
            for (; index < ht_->ht_.size(); index++)
            {
               if (ht_->ht_[index])
               {
                   node_ = ht_->ht_[index];
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
    
    iterator& begin()
    {
        for (size_t i = 0; i < ht_.size(); i++)
        {
            if (ht_[i])
                return iterator(ht_[i], this);
        }
        
        return iterator(nullptr, this);
    }

    iterator& end()
    {
        return iterator(nullptr, this);
    }

    std::pair<iterator, bool> insert (const V& data)
    {
        // 先拿到 data 的 index
        KeyOfValue kov;
        size_t index = GetIndex(kov(data));

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

private:
    size_t GetIndex(const K& key)
    {
        HFunc hf;
        return hf(key) % ht_.size();
    }
private:
    std::vector<pNode> ht_;
    int size_;
};
