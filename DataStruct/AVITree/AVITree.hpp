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
		// �����һ��������ֱ�Ӵ��������ͺ�
		if (_root == nullptr)
		{
			_root = new node(val);
			return true;
		}

		// ������ǿ����������ҵ��Ƿ���Բ���
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
			else // ���ֵ��ȣ�˵����������Ѵ������ֵ�����ܲ���
			{
				return false;
			}
		}

		pNode newNode = new node(val);
		// �ں��ʵĵط�����
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

		// ����ƽ�����ӣ��ж��Ƿ���Ҫ��ת
		while (parent)
		{
			if (parent->_pLeft == cur)
				--parent->_bf;
			else
				++parent->_bf;

			// �����ʱ������ƽ������Ϊ0��˵���ﵽ���ƽ�⣬����Ҫ��ת��
			if (parent->_bf == 0)
				break;

			// ���������ƽ������Ϊ 1 �� -1������Ҫ���´�·���ϵ�ƽ������
			if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = parent->_pParent;
			}
			// ���������ƽ������Ϊ 2 �� -2��˵����ʱ��Ҫ��ת��������ת�꣬AVI������ƽ��
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				if (parent->_bf == 2 && cur->_bf == 1)// ����
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

				// ��ת��һ���ﵽƽ�⣬���Կ���ֱ���˳�ѭ��
				break;
			}
		}

		return true;
	}

	void RotateL(pNode& parent)
	{
		// �ȼ�¼������Ҫ�޸����ԵĽ��
		pNode subR = parent->_pRight;
		pNode subRL = subR->_pLeft;

		// 1.����������ӵ��ҽ�����������
		subR->_pLeft = parent;
		parent->_pRight = subRL;

		// 2.��� subRL ���ھ͸��� subRL �ĸ��������
		if (subRL)
			subRL->_pParent = parent;

		// 3.���� subR �ĸ��������
		if (parent == _root)
		{
			subR->_pParent = nullptr;
			_root = subR;
		}
		else
		{
			// �������㲻�Ǹ��ڵ�
			// ��¼�����ĸ����
			pNode gParent = parent->_pParent;
			subR->_pParent = gParent;
			// �� subR ���ӵ��游�����
			if (gParent->_pLeft == parent)
				gParent->_pLeft = subR;
			else
				gParent->_pRight = subR;
		}

		// ���¸����ĸ��������
		parent->_pParent = subR;

		// 4.����ƽ������
		parent->_bf = subR->_bf = 0;
	}

	void RotateR(pNode& parent)
	{
		// �ȼ�¼��Ҫ��ת�Ľ��
		pNode subL = parent->_pLeft;
		pNode subLR = subL->_pRight;

		// 1.�������ŵ� subL ����������, ���� subLR �ŵ���������������
		subL->_pRight = parent;
		parent->_pLeft = subLR;

		// 2.����� subLR �������ĸ��������
		if (subLR)
			subLR->_pParent = parent;

		// 3.���� subL �ĸ��������
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
		// ����parent��parent����
		parent->_pParent = subL;

		// 4.����ƽ������
		parent->_bf = subL->_bf = 0;
	}

	// �����������һ�������
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