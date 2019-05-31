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

    bool Insert (pair<K, V>& kv)
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
                        RotateR(gParent);
                    }
                    else
                    {
                        RotateR(gParent);
                    }



                    gParent->_color = RED;
                    parent->_color = BLACK;
                }
            }
            else
                uncle = gParent->_pLeft;




        }
    }

private:
    void RotateR(pNode& parent)
    {
        pNode subL = parent->_pLeft;
        pNode subLR = subL->_pRight;

        // 先调整
        subL->_pRight = parent;
        parent->_pLeft = subLR;

        subLR->_pParent = parent;

        pNode gParent = parent->_pParent;
        if (gParent->_pLeft == parent)
        {
            gParent->_pLeft = subL;
        }
        else
        {
            gParent->_pRight = subL;
        }

        subL->_pParent = gParent;
        parent->_pParent = subL;
    }



    pNode _header;
};
