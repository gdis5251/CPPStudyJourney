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

		Adjust(parent, cur);

		return true;
	}

	// ɾ�����
	bool Erase(const T& val)
	{
		if (nullptr == _root)
		{
			return false;
		}

		// ���ҵ�ֵ��Ӧ�Ľ��
		pNode parent = nullptr;
		pNode cur = _root;
		while (cur)
		{
			if (val == cur->_val)
				break;
			
			parent = cur;
			if (val < cur->_val)
				cur = cur->_pLeft;
			else
				cur = cur->_pRight;
		}
		// ���û�ҵ��ͷ��� false
		if (nullptr == cur)
			return false;

		// �������ʼɾ�����
		// ����ý����Ҷ�ӽ��
		if (nullptr == cur->_pLeft && nullptr == cur->_pRight)
		{
			if (cur == _root)
			{
				delete cur;
				cur = nullptr;
				_root = nullptr;
			}
			else
			{
				if (parent->_pLeft == cur)
					parent->_pLeft = nullptr;
				else
					parent->_pRight = nullptr;

				delete cur;
				cur = nullptr;

				Adjust(parent, cur);
			}
		}
		// ���curֻ��������
		else if (nullptr == cur->_pRight)
		{
			if (cur == _root)
			{
				_root = _root->_pLeft;
			}
			else
			{
				if (parent->_pLeft == cur)
					parent->_pLeft = cur->_pLeft;
				else
					parent->_pRight = cur->_pLeft;
				
				pNode child = cur->_pLeft;
			
				Adjust(parent, child);
			}
			delete cur;
			cur = nullptr;
		}
		// ���ֻ��������
		else if (nullptr == cur->_pLeft)
		{
			if (cur == _root)
			{
				_root = _root->_pLeft;
			}
			else
			{
				if (parent->_pLeft == cur)
					parent->_pLeft = cur->_pRight;
				else
					parent->_pRight = cur->_pRight;

				pNode child = cur->_pRight;
				
				Adjust(parent, child);
			}
			delete cur;
			cur = nullptr;
		}
		// ���������������
		// ����������ѡһ�����Ļ�������������ѡһ����С��
		// �����������������ѡһ����С��
		else
		{
			// �ҵ�����������С�Ľ��
			pNode exchange = cur;
			if (cur == _root)
				cur = cur->_pRight;

			pNode newNode = cur;
			parent = nullptr;
			while (newNode)
			{
				if (newNode->_pLeft)
				{
					parent = newNode;
					newNode = newNode->_pLeft;
				}
				else
					break;
			}
			
			if (parent)
			{
				parent->_pLeft = nullptr;
			}
			// ��� parent Ϊ�գ�˵��newNodeû�ж�������newNodeû��������
			else
			{
				exchange->_pRight = newNode->_pRight;
				parent = exchange;
			}
			exchange->_val = newNode->_val;

			
			delete newNode;
			newNode = nullptr;

			
			Adjust(parent, newNode);
		};
		
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

	void RotateR(pNode & parent)
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

	void Adjust(pNode& parent, pNode& cur)
	{
		// ����ƽ�����ӣ��ж��Ƿ���Ҫ��ת
		while (parent)
		{
			parent->_bf = _GetHeight(parent->_pRight) - _GetHeight(parent->_pLeft);

			if (parent == _root && abs(parent->_bf) < 2)
				break;
			// ���������ƽ������Ϊ 1 �� -1������Ҫ���´�·���ϵ�ƽ������
			if (parent->_bf == 1 || parent->_bf == -1 || parent->_bf == 0)
			{
				cur = parent;
				parent = parent->_pParent;
			}
			// ���������ƽ������Ϊ 2 �� -2��˵����ʱ��Ҫ��ת��������ת�꣬AVI������ƽ��
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				if (parent->_bf == 2 && cur == nullptr)
				{
					pNode subR = parent->_pRight;
					RotateL(parent);

					subR->_bf = _GetHeight(subR->_pRight) - _GetHeight(subR->_pLeft);
					parent->_bf = _GetHeight(parent->_pRight) - _GetHeight(parent->_pLeft);
				}
				else if (parent->_bf == -2 && cur == nullptr)
				{
					pNode subL = parent->_pLeft;
					RotateR(parent);

					subL->_bf = _GetHeight(subL->_pRight) - _GetHeight(subL->_pLeft);
					parent->_bf = _GetHeight(parent->_pRight) - _GetHeight(parent->_pLeft);
				}
				else if (parent->_bf == 2 && cur->_bf == 1)// ����
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
	}

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

