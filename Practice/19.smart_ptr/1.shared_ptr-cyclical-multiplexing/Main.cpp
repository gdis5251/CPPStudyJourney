#include <iostream>
#include <memory>

struct ListNode
{
    int value;
    std::weak_ptr<ListNode> _next;
    std::weak_ptr<ListNode> _prev;

    ~ListNode()
    {
        std::cout << "~ListNode" << std::endl;
    }
};

int main(void)
{
    std::shared_ptr<ListNode> p1(new ListNode());
    std::shared_ptr<ListNode> p2(new ListNode());

    p1->_next = p2;
    p2->_prev = p1;

    return 0;
}
