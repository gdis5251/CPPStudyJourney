#include "BitSet.hpp"

template <class K, class HashFun1, class HashFun2, class HashFun3>
class BloomFilter
{
public:
    BloomFilter(size_t range)
        :bs_(range),
        bit_count_(range)
    {}
    
void Set(const K& key)
{
    // 先通过哈希函数将 key 转成整数
    size_t index1 = HashFun1()(key) % bit_count_;
    size_t index2 = HashFun2()(key) % bit_count_;
    size_t index3 = HashFun3()(key) % bit_count_;

    bs_.set(index1);
    bs_.set(index2);
    bs_.set(index3);
}

bool Test(const K& key)
{
    size_t index1 = HashFun1()(key) % bit_count_;
    if (!bs_.test(index1))
        return false;
    size_t index2 = HashFun2()(key) % bit_count_;
    if (!bs_.test(index2))
        return false;
    size_t index3 = HashFun3()(key) % bit_count_;
    if (!bs_.test(index3))
        return false;

    return true;
}
private:
    BitSet bs_;
    size_t bit_count_;
};

struct HF1
{
    size_t operator()(const std::string& str)
    {
        size_t hash = 0;
        for (const auto& e : str)
        {
            hash = hash * 65599 + e;
        }
        
        return hash;
    }
};

struct HF2
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

struct HF3
{
    size_t operator()(const std::string& str)
    {
        size_t hash = 0;
        size_t magic = 63689;
        for (const auto& e : str)
        {
            hash = hash * magic + e;
            magic *= 378551;
        }
        
        return hash;
    }
};

void Test()
{
    BloomFilter<std::string, HF1, HF2, HF3> bf(100);
    std::string str1 = "https://sports.qq.com/kbsweb/";
    std::string str2 = "http://www.cplusplus.com/";
    std::string str3 = "http://www.github.com/gdis5251/";

    bf.Set(str1);
    bf.Set(str2);

    std::cout << bf.Test(str3) << std::endl;
}