#include "heap.hpp"

int main()
{
    Heap h;
    h.Push(4);
    h.Push(3);
    h.Push(6);
    h.Push(9);
    h.Push(2);
    h.Push(1);
    h.Push(8);
    h.Push(0);
    h.Push(3);
    h.Push(1);
    h.Push(5);

    while (!h.Empty())
    {
        std::cout << h.Top() << " ";
        h.Pop();
    }
    std::cout << std::endl;

    return 0;
}

