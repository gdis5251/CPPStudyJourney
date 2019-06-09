#pragma once
#include <iostream>
#include <vector>

enum Status
{
    EMPTY,
    DELETE,
    EXIST
};

template <class K, class V>
struct HashNode
{
    HashNode()
        :status_(EMPTY)
    {}

    Status status_;
    std::pair<K, V> kv_;
};

template <class K, class V>
class HashTable
{
public:
    typedef HashNode<K, V> Node;
    typedef Node* pNode;

    HashTable(int size = 5)
        :size_(0),
        hash_table_(size)
    {}

    ~HashTable() {}

    bool insert(std::pair<K, V> kv)
    {
        CheckCapacity();

        size_t index = kv.first % hash_table_.size();
        while (hash_table_[index].status_ == EXIST)
        {
            if (hash_table_[index].kv_.first == kv.first)
                return false;

            index++;
            if (hash_table_.size() == size_)
                index = 0;
        }

        hash_table_[index].kv_ = kv;
        hash_table_[index].status_ = EXIST;
        size_++;
        
        return true;
    }


    pNode find(std::pair<K, V> kv)
    {
       int index = kv.first % hash_table_.size(); 

       while (hash_table_[index].status_ == EXIST)
       {
           if (hash_table_[index].kv_.first == kv.first)
               return &hash_table_[index];

           index++;
           if (index == hash_table_.size())
               index = 0;
       }

       return nullptr;
    }

    bool erase(std::pair<K, V> kv)
    {
        pNode ret = find(kv);
        if (ret->status_ == EXIST)
        {
            ret->status_ = DELETE;
            size_--;

            return true;
        }

        return false;
    }
private:
    void CheckCapacity()
    {
        if ((size_ * 10) / hash_table_.size() >= 7)
        {
            size_t new_capacity = hash_table_.size() * 2;
            HashTable tmp(new_capacity);

            for (size_t i = 0; i < hash_table_.size(); i++)
            {
                if (hash_table_[i].status_ == EXIST)
                {
                    tmp.insert(hash_table_[i].kv_);
                }
            }

            hash_table_.swap(tmp.hash_table_);
        }
    }
private:
    int size_;
    std::vector<Node> hash_table_;
};

