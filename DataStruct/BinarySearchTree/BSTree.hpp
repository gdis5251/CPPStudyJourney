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

		// 找到要删除的结点
		pNode cur = _root;
		pNode parent = nullptr;

		while (cur)
		{
			// 如果找到跳出循环，交给后面处理
			if (cur->_val == val)
			{
				break;
			}
			// 如果当前值大于需要找的值，往左走
			else if (cur->_val > val)
			{
				parent = cur;
				cur = cur->_left;
			}
			// 如果当前值小于需要找的值，往右走
			else if (cur->_val < val)
			{
				parent = cur;
				cur = cur->_right;
			}
		}

		// 找到需要删除的结点
		// 如果该结点是叶子结点，直接删除即可
		if (cur->_left == nullptr && cur->_right == nullptr)
		{
			// 如果不是根节点
			if (cur != _root)
			{
				// 在判断该结点是父结点的哪个子树，并将其置空
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
		// 如果该结点只有右子树
		else if (cur->_left == nullptr && cur->_right != nullptr)
		{
			// 如果不是根结点
			if (cur != _root)
			{
				// 让父结点原本连cur的指针现在连cur的右子树
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
		// 如果cur只有左子树
		else if (cur->_left != nullptr && cur->_right == nullptr)
		{
			// 如果不是根结点
			if (cur != _root)
			{
				// 让父结点原本连cur的指针现在连cur的右子树
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
		// 如果cur既有左子树也有右子树
		// 那么就可以在左子树里找一个最大结点或在右子树里找一个最小结点
		// 来替换cur
		// 这里采用在左子树里找一个最大结点
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

			// 置换左子树的最大结点和cur，其实就是换一下值
			exchange->_val = newNode->_val;
			// 删除newNode
			// 因为newNode只往右走，所以直接改nParent的右子树就行
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
