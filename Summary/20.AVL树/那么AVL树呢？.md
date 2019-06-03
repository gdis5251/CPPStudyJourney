# 那么AVL树呢？:evergreen_tree:

> 虽然二叉搜索树可以缩短查找的效率，但是就像我这篇博客讲的[二叉搜索树你懂了么？](<https://blog.csdn.net/weixin_42678507/article/details/90703826>)如果插入的数据已经有序或者接近有序，那么二叉搜索树就会退化成单支树，这个时候再去查找，就相当于在顺序表中查找一样，时间复杂度是O(N)的。所以就有大佬发明了AVL树。
>
> 当向AVL树中插入数据时，如果某个结点的左右子树高度只差的绝对值超过1，那么就需要对树中的结点进行调整，即可降低高度，从而减少平均搜索的长度。

**一颗AVL树需要具备以下性质：**

- 它的左右子树都是AVL树。
- 左右子树高度只差（平衡因子）的绝对值小于2。

> 平衡因子 = 右子树高度 - 左子树高度

## AVL树节点定义：

```cpp
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
	int _bf; // 该结点的平衡因子
};
```

### AVL树的插入

```cpp
	bool Insert(const T& val)
	{
        // 如果是一个空树，直接在根结点上创建结点即可
		if (_root == nullptr)
		{
			_root = new node(val);
			return true;
		}

		pNode cur = _root;
		pNode parent = nullptr;

        // 寻找合适的插入位置，如果已经有值为val的结点，直接退出
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
			{
				return false;
			}
		}

        // 插入
		pNode newNode = new node(val);
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

        // 进行调整
		Adjust(parent, cur);

		return true;
	}
```

这里没什么好说的，基本流程跟二叉搜索树差不多，就是多了个调整。

## AVL树的删除

```cpp
	bool Erase(const T& val)
	{
        // 如果是空树，直接返回
		if (nullptr == _root)
		{
			return false;
		}

        // 找到需要删除的结点
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
        // 如果没有这个结点也是直接返回
		if (nullptr == cur)
			return false;

        // 下面开始对不同情况，进行不同的删除操作
        // 如果该结点是叶子结点
		if (nullptr == cur->_pLeft && nullptr == cur->_pRight)
		{
            // 如果该结点只有一个根结点。直接删除。
			if (cur == _root)
			{
				delete cur;
				cur = nullptr;
				_root = nullptr;
			}
			else
			{// 先判断该结点在父结点的哪个子树上，断开连接
				if (parent->_pLeft == cur)
					parent->_pLeft = nullptr;
				else
					parent->_pRight = nullptr;

				delete cur;
				cur = nullptr;

                // 进行从下到上的调整
				Adjust(parent, cur);
			}
		}
        // 如果该结点只有左子树
		else if (nullptr == cur->_pRight)
		{
            // 如果该结点是根结点，直接让根结点向左移一下
			if (cur == _root)
			{
				_root = _root->_pLeft;
			}
			else
			{
                // 先断开连接，并且让父结点指向cur的左子树
				if (parent->_pLeft == cur)
					parent->_pLeft = cur->_pLeft;
				else
					parent->_pRight = cur->_pLeft;
				
				pNode child = cur->_pLeft;
			
                // 调整
				Adjust(parent, child);
			}
			delete cur;
			cur = nullptr;
		}
        // 该结点只有右子树，与上种情况类似
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
        // 如果该结点既有左子树，又有右子树
        // 可以在左子树里找一个值最大的结点或者在右子树里找一个值最小的结点
        // 都可以保证AVL树的性质不改变(左子树都比该结点小，右子树都比该结点大)
        // 这里采取在右子树里找一个值最小的结点
		else
		{
            // 如果该结点是根结点，先让cur往右走一步
			pNode exchange = cur;
			if (cur == _root)
				cur = cur->_pRight;

            // 找到最小的一个结点
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
			
            // 这里的意思是，上面的个循环如果没有走
            // 说明右子树最小的结点是 newNode
            // 如果走了，需要让 parent 和 newNode 断开连接
			if (parent)
			{
				parent->_pLeft = nullptr;
			}
			else
			{
				exchange->_pRight = newNode->_pRight;
				parent = exchange;
			}
            // 这里直接交换两个结点的值，然后删除那个右子最小的结点
			exchange->_val = newNode->_val;

			
			delete newNode;
			newNode = nullptr;

			
            // 调整
			Adjust(parent, newNode);
		};
		
	}
```

这个删除跟二叉搜索树的情况一样，就是加了个调整，详细思路已经写在代码注释里了。

## AVL树的调整

这里面有四种调整方式和两种调整手段。

### 右单旋

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190603154808343.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

首先这是一个平衡二叉树。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190603154813765.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

当在a的下面插入一个结点的时候，根结点的平衡因子变成了-2，所以这个时候需要调整。

调整具体就是向右旋转，让 30 的右子树连接 60， 60 的左子树连接 30 的右子树。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190603154826298.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

最后更新平衡因子，让 30 和 60 的平衡因子都变为0。

```cpp
	void RotateR(pNode & parent)
	{
    	// 先记录旋转轴（父结点）的左孩子和左孩子的右孩子
		pNode subL = parent->_pLeft;
		pNode subLR = subL->_pRight;

        // 将左孩子的右子树连接父结点
        // 父结点的左子树连接左孩子的右子树
		subL->_pRight = parent;
		parent->_pLeft = subLR;

        // 如果左孩子的右子树存在，就更新其父结点
		if (subLR)
			subLR->_pParent = parent;

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
		parent->_pParent = subL;

		parent->_bf = subL->_bf = 0;
	}
```



### 左单旋

左单旋跟右单旋类似，就是换了个方向。当插入后的结点的祖父结点的平衡因子为 2 ，父结点的平衡因子为1，就需要左单旋。

```cpp
void RotateL(pNode& parent)
	{
		pNode subR = parent->_pRight;
		pNode subRL = subR->_pLeft;

		subR->_pLeft = parent;
		parent->_pRight = subRL;

		if (subRL)
			subRL->_pParent = parent;

		if (parent == _root)
		{
			subR->_pParent = nullptr;
			_root = subR;
		}
		else
		{
			pNode gParent = parent->_pParent;
			subR->_pParent = gParent;
			if (gParent->_pLeft == parent)
				gParent->_pLeft = subR;
			else
				gParent->_pRight = subR;
		}

		parent->_pParent = subR;

		parent->_bf = subR->_bf = 0;
	}
```

### 左右双旋

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190603161745152.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

这是一个AVL树。当在 b 上插入结点的时候。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190603161751224.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

90 的平衡因子变为 -2，30 的平衡因子变为1 。这个时候需要左右单旋。

先以 30 为轴左单旋。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190603161757703.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

然后以 90 为轴右单旋。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190603161802741.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

这里有一点需要注意。这里旋转之后 90 的平衡因子变成1， 而 30 的平衡因子变成 0 。 这是为什么呢？这里我们可以看一下第一张左右单旋的图，到最后一张图，我们发现，60 的左子树变成了 30 的右子树；60 的右子树，变成了 90 的左子树。就是说，父结点和祖父结点会瓜分孩子结点的左右子树。

所以当在孩子的左结点插入的时候 30 的平衡因子变成 0；90 的平衡因子变成 1。当在孩子的右结点插入的时候，30 的平衡因子变成 -1 ， 90 的平衡因子变成 0 。

### 右左双旋

跟相面类似。

### Code

```cpp
	void Adjust(pNode& parent, pNode& cur)
	{
		while (parent)
		{
            // 获取该父结点的平衡因子
			parent->_bf = _GetHeight(parent->_pRight) - _GetHeight(parent->_pLeft);

            // 如果该结点已经到达根结点，并且平衡因子的绝对值小于2，退出调整
			if (parent == _root && abs(parent->_bf) < 2)
				break;
            // 如果该结点不需要调整就继续往上走
			if (parent->_bf == 1 || parent->_bf == -1 || parent->_bf == 0)
			{
				cur = parent;
				parent = parent->_pParent;
			}
            // 这里就需要调整了
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
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateR(parent);
				}
                // 左右双旋
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
                // 右左双旋
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

				break;
			}
		}
	}
```

## AVL树的验证

这里验证是否是一个AVL树可以这么做：
先获取当前结点的平衡因子，然后求当前因子的左右子树的高度，算一下当前平衡因子是否等于当前结点的右子树高度减去左子树高度。如果等于递归判断其他结点，如果不等于，返回false。

## 完整代码：

```cpp
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
		if (_root == nullptr)
		{
			_root = new node(val);
			return true;
		}

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
			{
				return false;
			}
		}

		pNode newNode = new node(val);
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

	bool Erase(const T& val)
	{
		if (nullptr == _root)
		{
			return false;
		}

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
		if (nullptr == cur)
			return false;

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
		else
		{
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
		pNode subR = parent->_pRight;
		pNode subRL = subR->_pLeft;

		subR->_pLeft = parent;
		parent->_pRight = subRL;

		if (subRL)
			subRL->_pParent = parent;

		if (parent == _root)
		{
			subR->_pParent = nullptr;
			_root = subR;
		}
		else
		{
			pNode gParent = parent->_pParent;
			subR->_pParent = gParent;

            if (gParent->_pLeft == parent)
				gParent->_pLeft = subR;
			else
				gParent->_pRight = subR;
		}

		parent->_pParent = subR;

		parent->_bf = subR->_bf = 0;
	}

	void RotateR(pNode & parent)
	{
		pNode subL = parent->_pLeft;
		pNode subLR = subL->_pRight;

		subL->_pRight = parent;
		parent->_pLeft = subLR;

		if (subLR)
			subLR->_pParent = parent;

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
		parent->_pParent = subL;

		parent->_bf = subL->_bf = 0;
	}

	void Adjust(pNode& parent, pNode& cur)
	{
		while (parent)
		{
			parent->_bf = _GetHeight(parent->_pRight) - _GetHeight(parent->_pLeft);

			if (parent == _root && abs(parent->_bf) < 2)
				break;
			if (parent->_bf == 1 || parent->_bf == -1 || parent->_bf == 0)
			{
				cur = parent;
				parent = parent->_pParent;
			}
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
				else if (parent->_bf == 2 && cur->_bf == 1)
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


```

叮~:bell:

