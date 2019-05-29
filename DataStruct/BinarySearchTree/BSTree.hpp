#pragma once
#include <iostream>

template <class T>
struct BSTNode
{
	BSTNode(const T& val = T())
		:_val(val),
		_left(nullptr),
		_right(nullptr)
	{}

	T _val;
	BSTNode<T>* _left;
	BSTNode<T>* _right;
};

template <class T>
class BSTree
{
public:
	typedef BSTNode<T> Node;
	typedef Node* pNode;
	
	BSTree(const pNode root = nullptr)
		:_root(root)
	{}

	pNode Find(const T& val)
	{
		if (_root == nullptr)
			return nullptr;

		pNode cur = _root;
		while (cur)
		{
			if (cur->_val == val)
			{
				return cur;
			}
			else if (cur->_val > val)
			{
				cur = cur->_left;
			}
			else if (cur->_val < val)
			{
				cur = cur->_right;
			}
		}

		return nullptr;
	}

	bool Insert(const T& val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);

			return true;
		}

		pNode cur = _root;
		pNode parent = nullptr;
		while (cur)
		{
			parent = cur;
			
			if (cur->_val > val)
			{
				cur = cur->_left;
			}
			else if (cur->_val < val)
			{
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		pNode newNode = new Node(val);
		if (parent->_val > val)
		{
			parent->_left = newNode;
		}
		else
		{
			parent->_right = newNode;
		}

		return true;
	}

	bool Erase(const T& val)
	{
		if (_root == nullptr)
		{
			return false;
		}

		// �ҵ�Ҫɾ���Ľ��
		pNode cur = _root;
		pNode parent = nullptr;

		while (cur)
		{
			// ����ҵ�����ѭ�����������洦��
			if (cur->_val == val)
			{
				break;
			}
			// �����ǰֵ������Ҫ�ҵ�ֵ��������
			else if (cur->_val > val)
			{
				parent = cur;
				cur = cur->_left;
			}
			// �����ǰֵС����Ҫ�ҵ�ֵ��������
			else if (cur->_val < val)
			{
				parent = cur;
				cur = cur->_right;
			}
		}

		// �ҵ���Ҫɾ���Ľ��
		// ����ý����Ҷ�ӽ�㣬ֱ��ɾ������
		if (cur->_left == nullptr && cur->_right == nullptr)
		{
			// ������Ǹ��ڵ�
			if (cur != _root)
			{
				// ���жϸý���Ǹ������ĸ��������������ÿ�
				if (parent->_left == cur)
					parent->_left = nullptr;
				else
					parent->_right = nullptr;
			}
			else
			{
				_root = nullptr;
			}

			delete cur;
			cur = nullptr;

		}
		// ����ý��ֻ��������
		else if (cur->_left == nullptr && cur->_right != nullptr)
		{
			// ������Ǹ����
			if (cur != _root)
			{
				// �ø����ԭ����cur��ָ��������cur��������
				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
				}
				else if (parent->_right == cur)
				{
					parent->_right = cur->_right;
				}
			}
			else
			{
				_root = _root->_right;
			}

			delete cur;
			cur = nullptr;
		}
		// ���curֻ��������
		else if (cur->_left != nullptr && cur->_right == nullptr)
		{
			// ������Ǹ����
			if (cur != _root)
			{
				// �ø����ԭ����cur��ָ��������cur��������
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				else if (parent->_right == cur)
				{
					parent->_right = cur->_left;
				}
			}
			else
			{
				_root = _root->_left;
			}

			delete cur;
			cur = nullptr;
		}
		// ���cur����������Ҳ��������
		// ��ô�Ϳ���������������һ��������������������һ����С���
		// ���滻cur
		// �������������������һ�������
		else
		{
            pNode exchange = cur;
            if (cur == _root)
                cur = cur->_left;

			pNode newNode = cur;
			pNode nParent = nullptr;
			while (newNode)
			{
				if (newNode->_right)
				{
					nParent = newNode;
					newNode = newNode->_right;
				}
				else
					break;
			}

			// �û���������������cur����ʵ���ǻ�һ��ֵ
			exchange->_val = newNode->_val;
			// ɾ��newNode
			// ��ΪnewNodeֻ�����ߣ�����ֱ�Ӹ�nParent������������
			nParent->_right = nullptr;
			delete newNode;
			newNode = nullptr;
		}

		return true;
	}
	
	void Inorder(void)
	{
		_Inorder(_root);
		std::cout << std::endl;
	}
private:
	void _Inorder(const pNode root)
	{
		if (root)
		{
			_Inorder(root->_left);
			std::cout << root->_val << " ";
			_Inorder(root->_right);
		}
	}

	pNode _root;
};
