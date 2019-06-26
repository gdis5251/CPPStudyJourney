#include "BitSet.hpp"

int main()
{
    BitSet bitset(100);

    // bitset.set(5);
    // bitset.set(8);
    bitset.set(20000);

    // std::cout << bitset.test(5) << std::endl;
    // std::cout << bitset.test(8) << std::endl;
    std::cout << bitset.test(20000) << std::endl;

    // bitset.reset(8);
    // std::cout << bitset.test(8) << std::endl;

    return 0;
}

