#include "list.h"

void TestList1(void)
{
    Gerald::List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);

    for(const auto& e : l1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    Gerald::List<int> l2(l1);
    Gerald::List<int>::iterator it = l2.begin();
    while (it != l2.end())
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;

    Gerald::List<int> l3;
    l3 = l2;
    for(const auto& e : l1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

void TestList2()
{
    Gerald::List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    for(const auto& e : l1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;


    l1.push_front(9);
    l1.push_front(8);
    l1.push_front(7);
    l1.push_front(6);
    for(const auto& e : l1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;


    l1.pop_back();
    l1.pop_back();
    l1.pop_back();
    for(const auto& e : l1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;


    l1.pop_front();
    l1.pop_front();
    l1.pop_front();
    for(const auto& e : l1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

void TestList3()
{
    Gerald::List<int> l1;
    std::cout << l1.empty() << std::endl;

    l1.push_back(1);
    l1.push_back(1);
    l1.push_back(1);
    l1.push_back(1);
    
    std::cout << l1.size() << std::endl;
    std::cout << l1.empty() << std::endl;

}

int main(void)
{
    TestList1();  
    return 0;
}
