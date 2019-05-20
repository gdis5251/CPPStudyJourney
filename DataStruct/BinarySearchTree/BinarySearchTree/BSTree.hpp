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