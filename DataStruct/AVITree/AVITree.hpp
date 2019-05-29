#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>

template<class T>
struct AVLTreeNode
{
	AVLTreeNode(const T& val = T()) noexcept
		:_val(val),
		_pLeft(nullptr),
		_pRight(nullptr),
		_pParent(nullptr),
		_bf(0)
	{}

	T _val;
	AVLTreeNode<T>* _pLeft;
	AVLTreeNode<T>* _pRight;
	AVLTreeNode<T>* _pParent;
	int _bf;
};

template <class T>
class AVLTree
{
public:
	typedef AVLTreeNode<T> node;
	typedef node* pNode;

	bool Insert(const T& val)
	{
		// 如果是一个空树，直接创建根结点就好
		if (_root == nullptr)
		{
			_root = new node(val);
			return true;
		}

		// 如果不是空树，先来找到是否可以插入
		pNode cur = _root;
		pNode parent = nullptr;

		while (cur)
		{
			parent = cur;

			if (val < cur->_val)
			{
				cur = cur->_pLeft;
			}
			else if (val > cur->_val)
			{
				cur = cur->_pRight;
			}
			else // 如果值相等，说明这个树中已存在这个值，不能插入
			{
				return false;
			}
		}

		pNode newNode = new node(val);
		// 在合适的地方插入
		if (val < parent->_val)
		{
			parent->_pLeft = newNode;
		}
		else if (val > parent->_val)
		{
			parent->_pRight = newNode;
		}
		newNode->_pParent = parent;
		cur = newNode;

		// 更新平衡因子，判断是否需要旋转
		while (parent)
		{
			if (parent->_pLeft == cur)
				--parent->_bf;
			else
				++parent->_bf;

			// 如果此时父结点的平衡因子为0，说明达到最佳平衡，不需要旋转了
			if (parent->_bf == 0)
				break;

			// 如果父结点的平衡因子为 1 或 -1，还需要更新此路径上的平衡因子
			if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = parent->_pParent;
			}
			// 如果父结点的平衡因子为 2 或 -2，说明此时需要旋转，并且旋转完，AVI树到达平衡
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				if (parent->_bf == 2 && cur->_bf == 1)// 左旋
				{
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateR(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					pNode subL = parent->_pLeft;
					pNode subLR = subL->_pRight;
					int bf = subLR->_bf;
					
					RotateL(cur);
					RotateR(parent);

					if (bf == -1)
					{
						parent->_bf = 1;
						subL->_bf = 0;
					}
					else if (bf == 1)
					{
						parent->_bf = 0;
						subL->_bf = -1;
					}
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					pNode subR = parent->_pRight;
					pNode subRL = subR->_pLeft;
					int bf = subRL->_bf;

					RotateR(cur);
					RotateL(parent);

					if (bf == -1)
					{
						parent->_bf = 0;
						subR->_bf = 1;
					}
					else if (bf == 1)
					{
						parent->_bf = -1;
						subR->_bf = 0;
					}
				}

				// 旋转完一定达到平衡，所以可以直接退出循环
				break;
			}
		}

		return true;
	}

	void RotateL(pNode& parent)
	{
		// 先记录所有需要修改属性的结点
		pNode subR = parent->_pRight;
		pNode subRL = subR->_pLeft;

		// 1.将父结点连接到右结点的左子树上
		subR->_pLeft = parent;
		parent->_pRight = subRL;

		// 2.如果 subRL 存在就更新 subRL 的父结点属性
		if (subRL)
			subRL->_pParent = parent;

		// 3.更新 subR 的父结点属性
		if (parent == _root)
		{
			subR->_pParent = nullptr;
			_root = subR;
		}
		else
		{
			// 如果父结点不是根节点
			// 记录父结点的父结点
			pNode gParent = parent->_pParent;
			subR->_pParent = gParent;
			// 将 subR 连接到祖父结点上
			if (gParent->_pLeft == parent)
				gParent->_pLeft = subR;
			else
				gParent->_pRight = subR;
		}

		// 更新父结点的父结点属性
		parent->_pParent = subR;

		// 4.更新平衡因子
		parent->_bf = subR->_bf = 0;
	}

	void RotateR(pNode& parent)
	{
		// 先记录需要旋转的结点
		pNode subL = parent->_pLeft;
		pNode subLR = subL->_pRight;

		// 1.将父结点放到 subL 的右子树上, 并把 subLR 放到父结点的左子树上
		subL->_pRight = parent;
		parent->_pLeft = subLR;

		// 2.如果有 subLR 更新它的父结点属性
		if (subLR)
			subLR->_pParent = parent;

		// 3.更新 subL 的父结点属性
		if (parent == _root)
		{
			subL->_pParent = nullptr;
			_root = subL;
		}
		else
		{
			pNode gParent = parent->_pParent;

			subL->_pParent = gParent;

			if (gParent->_pLeft == parent)
				gParent->_pLeft = subL;
			else
				gParent->_pRight = subL;
		}
		// 更新parent的parent属性
		parent->_pParent = subL;

		// 4.更新平衡因子
		parent->_bf = subL->_bf = 0;
	}

	// 中序遍历，是一个有序的
	void InorderTraversal()
	{
		_InorderTraversal(_root);
		std::cout << std::endl;
	}

	int GetHeight()
	{
		return _GetHeight(_root);
	}

	

	bool JudgeIfBalance()
	{
		return _JudgeIfBalance(_root);
	}

private:

	int _GetHeight(const pNode& _root)
	{
		if (_root == nullptr)
			return 0;

		int left = _GetHeight(_root->_pLeft);
		int right = _GetHeight(_root->_pRight);

		return left > right ? left + 1 : right + 1;
	}


	void _InorderTraversal(const pNode& _root)
	{
		if (_root == nullptr)
			return;

		_InorderTraversal(_root->_pLeft);
		std::cout << _root->_val << " ";
		_InorderTraversal(_root->_pRight);
	}


	bool _JudgeIfBalance(const pNode& _root)
	{
		if (_root == nullptr)
			return true;

		int left = _GetHeight(_root->_pLeft);
		int right = _GetHeight(_root->_pRight);

		if (_root->_bf != right - left)
		{
			return false;
		}

		return abs(_root->_bf) < 2 &&
			_JudgeIfBalance(_root->_pLeft) &&
			_JudgeIfBalance(_root->_pRight);
	}

private:
	pNode _root = nullptr;
};

void TestAVLTree()
{
	AVLTree<int> t;
	t.Insert(16);
	t.Insert(3);
	t.Insert(7);
	t.Insert(11);
	t.Insert(9);
	t.Insert(26);
	t.Insert(18);
	t.Insert(14);
	t.Insert(15);

	t.InorderTraversal();

	std::cout << t.JudgeIfBalance() << std::endl;
}