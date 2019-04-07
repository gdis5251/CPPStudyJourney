#include "Queue.h"

int main(void)
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
   //q.display();//12345

    q.pop();
    //q.display();//2345

    std::cout << q.size() << std::endl;

    std::cout << q.empty() << std::endl;

    std::cout << q.back() << std::endl;

    q.pop();
    q.pop();
    q.pop();
    q.pop();
    std::cout << q.empty() << std::endl;

    return 0;

}
