#include "Priority_queue.h"

int main(void)
{
    Priority_queue<int> pq;
    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.push(4);
    pq.push(5);

    while (!pq.empty())
    {
        std::cout << pq.top() << std::endl;
        pq.pop();
    }
    return 0;
}
