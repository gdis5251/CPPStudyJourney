#pragma once
#include <iostream>

enum Color 
{
    RED,
    BLACK
};

template <class K, class V>
struct RBTreeNode
{
    std::pair<K, V> _kv;
    RBTreeNode* _pLeft = nullptr;
    RBTreeNode* _pRight = nullptr;
    RBTreeNode* _pParent = nullptr;

    // 之所以默认为红色，是为了调整
    // 有一个规则是红结点不能连续
    Color _color = RED;    
};


template <class K, class V>
class RBTree 
{
public:
    typedef RBTreeNode<K, V> Node;
    typedef Node* pNode;

    RBTree()
        :_header(new Node)
    {
        _header->_pLeft = _header;
        _header->_pRight = _header;
    }

    bool Insert (const std::pair<K, V>& kv)
    {
        if (_header->_pParent == nullptr)
        {
            pNode root = new Node;
            root->_kv = kv;
            root->_color = BLACK;

            _header->_pParent = root;
            root->_pParent = _header;

            _header->_pLeft = root;
            _header->_pRight = root;

            return true;
        }

        // 查找合适的位置准备插入
        pNode cur = _header->_pParent;
        pNode parent = nullptr;

        while (cur)
        {
            if (kv.first < cur->_kv.first)
            {
                parent = cur;
                cur = cur->_pLeft;
            }
            else if (kv.first > cur->_kv.first)
            {
                parent = cur;
                cur = cur->_pRight;
            }
            else  // 不允许有相同结点
                return false;
        }

        cur = new Node;
        cur->_kv = kv;

        if (cur->_kv.first < parent->_kv.first)
            parent->_pLeft = cur;
        else 
            parent->_pRight = cur;

        cur ->_pParent = parent;

        // 调整变色
        while (cur->_pParent->_color == RED && cur != _header->_pParent)
        {
            pNode parent = cur->_pParent;
            // 如果父结点为红色，说明父结点绝对不是根结点，所以绝对存在祖父结点
            pNode gParent = parent->_pParent;

            pNode uncle;
            if (gParent->_pLeft == parent)
            {
                uncle = gParent->_pRight;
                // 存在且为红
                if (uncle && uncle->_color == RED)
                {
                    parent->_color = BLACK;
                    uncle->_color = BLACK;
                    gParent->_color = RED;

                    cur = gParent;
                }
                // 不存在或者存在且为黑
                else
                {
                    // 判断cur插入到了parent的哪个分支上
                    // 若为左分支直接右旋
                    // 若为右分支需要先左旋再右旋
                    
                    // 检查是否需要双旋
                    // 左右双旋
                    if (parent->_pRight == cur)
                    {
                        // 做单旋
                        RotateL(parent);
                        std::swap(cur, parent); // 这里交换两个指针是为了后面统一改变颜色
                    }
                    RotateR(gParent);

                    gParent->_color = RED;
                    parent->_color = BLACK;

                    break;
                }
            }
            else
            {
                uncle = gParent->_pLeft; 
                if (uncle && uncle->_color == RED)
                {
                    uncle->_color = BLACK;
                    parent->_color = BLACK;
                    gParent->_color = RED;

                    cur = gParent;
                }
                else 
                {
                    // 判断插入位置，根据插入位置再做处理
                    if (parent->_pLeft == cur)
                    {
                        RotateR(parent);
                        std::swap(parent, cur);
                    }
                    RotateL(gParent);

                    parent->_color = BLACK;
                    gParent->_color = RED;

                    break;
                }
            }
            // 红黑树根始终是黑色的
            _header->_pParent->_color = BLACK;

            // 为了以后实现迭代器
            _header->_pLeft = LeftMost();
            _header->_pRight = RightMost();
        }
    }

    void Inorder()
    {
        _Inorder(_header->_pParent);
        std::cout << std::endl;
    }

private:
    void _Inorder(pNode& root)
    {
        _Inorder(root->_pLeft);
        std::cout << root->_kv.second << " ";
        _Inorder(root->_pRight);
    }
    pNode LeftMost()
    {
        pNode cur = _header->_pParent;
        while (cur && cur->_pLeft)
        {
            cur = cur->_pLeft;
        }

        return cur;
    }

    pNode RightMost()
    {
        pNode cur = _header->_pParent;
        while (cur && cur->_pRight)
        {
            cur = cur->_pRight;
        }

        return cur;
    }

    void RotateR(pNode& parent)
    {
        pNode subL = parent->_pLeft;
        pNode subLR = subL->_pRight;

        // 先调整
        subL->_pRight = parent;
        parent->_pLeft = subLR;

        if (subLR)
            subLR->_pParent = parent;

        if (parent == _header->_pParent)
        {
            subL->_pParent == _header;
            parent->_pParent = subL;
        }
        else
        {
            pNode gParent = parent->_pParent;
            subL->_pParent = gParent;
            if (gParent->_pLeft == parent)
            {
                gParent->_pLeft = subL;
            }
            else
            {
                gParent->_pRight = subL;
            }

        }

        parent->_pParent = subL;
    }

    void RotateL(pNode& parent)
    {
        pNode subR = parent->_pRight;
        pNode subRL = subR->_pLeft;

        subR->_pLeft = parent;
        parent->_pRight = subRL;

        if (subRL)
            subRL->_pParent = parent;
        
        if (parent == _header->_pParent)
        {
            subR->_pParent = _header;
            parent->_pParent = subR;
        }
        else
        {
            pNode gParent = parent->_pParent;
            if (gParent->_pLeft == parent)
                gParent->_pLeft = subR;
            else
                gParent->_pRight = subR;
            
            subR->_pParent = gParent;

        }
        parent->_pParent = subR;
    }



    pNode _header;
};
