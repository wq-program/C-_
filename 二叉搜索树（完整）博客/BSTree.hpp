
#pragma once
#include<iostream>
using namespace std;

template<class K>
struct BSTreeNode
{
	BSTreeNode(const K& key)
		:_key(key),
		_right(nullptr),
		_left(nullptr)
	{
	}
	K _key;
	BSTreeNode<K>* _right;
	BSTreeNode<K>* _left;
};

template<class K>
class BSTree 
{
	typedef BSTreeNode<K> Node;
public:
	//告诉编译器强制生成
	BSTree() = default;
	//自己写
	//BSTree()
	//{
	//}

	BSTree(const BSTree<K>& root)
	{
		_root = _copy(root._root);
	}

	~BSTree()
	{
		Destroy(_root);
	}
	
	bool insert(const K& key)
	{
		//如果BSTree还没有结点
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}

		//找到插入的合适位置，和其父亲结点
		//父亲结点得作用是，我们新插入得结点要和父亲结点连接，
		//简单来说就是，父亲结点要孩子指针，要指向我们新的结点。
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		//创建新节点
		cur = new Node(key);
		//判断新插入得结点是父亲得左孩子还是右孩子
		if (key > parent->_key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		return true;
	}

	Node* find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}

	bool erase(const K& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				//准备删除
				//待删除结点，左节点为空，将其右边结点交给父亲
				if (cur->_left == nullptr)
				{
					//此时如果删除的是根节点需要改变根节点指向
					if (cur == _root)
					{
						_root = _root->_right;
					}
					else
					{
						//判断待删除结点是父亲的左孩子还是右孩子
						if (cur == parent->_left)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
					}
					
					delete cur;
					return true;

				}//待删除结点，左节点为空，将其左边结点交给父亲
				else if (cur->_right == nullptr)
				{
					//此时如果删除的是根节点需要改变根节点指向
					if (cur == _root)
					{
						_root = _root->_left;
					}
					else
					{
						//判断待删除结点是父亲的左孩子还是右孩子
						if (cur == parent->_left)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
					delete cur;
					return true;

				}	
				else
				{
					//由于删除的结点左右都有孩子
					//需要找一个能代替删除结点的位置结点，即比左子树大比右子树小
					//最适合的结点就是，左子树的最右结点(最大节点)，右子树的最左节点(最小结点)
					Node* MinNode = cur->_right;
					Node* MinParent = cur;
					while (MinNode->_left)
					{
						MinParent = MinNode;
						MinNode = MinNode->_left;
					}
					//先将MinNode结点的孩子交给他的父亲
					//注意:不能因为是找的最左边结点就因为MinNode结点一定是MinParent的左孩子
					if (MinParent->_left == MinNode)
					{
						MinParent->_left = MinNode->_right;
					}
					else
					{
						MinParent->_right = MinNode->_right;
					}
					//将MinNode结点的值赋值给cur
					cur->_key = MinNode->_key;
					delete MinNode;
					return true;
				}
			}
		}
		return false;
	}

	bool Rerase(const K& key)
	{
		return _Rerase(_root,key);
	}

	Node* Rfind(const K& key)
	{
		return _Rfind(_root, key);
	}

	bool Rinsert(const K& key)
	{
		return _Rinsert(_root, key);
	}

	void InOrder()
	{
		_InOrder(_root);
	}

private:

	Node* _copy(const Node* root)
	{
		if (root == nullptr)
			return nullptr;

		Node* newnode = new Node(root->_key);
		newnode->_left = _copy(root->_left);
		newnode->_right = _copy(root->_right);
		return newnode;
	}

	void Destroy(Node* root)
	{
		if (root == nullptr)
			return;

		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}

	bool _Rerase(Node*& root, const K& key)
	{
		//空树、没有找到删除的结点
		if (root == nullptr)
		{
			return false;
		}

		if (key < root->_key)
		{
			//key比当前结点小，往左树删除
			return _Rerase(root->_left, key);
		}
		else if(key > root->_key)
		{
			//key比当前结点小，往左树删除
			return _Rerase(root->_right, key);
		}
		else
		{
			//找到，开始删除
			Node* cur = root;
			if (root->_left == nullptr)
			{
				//1.待删除结点，左孩子为空
				root = root->_right;
			}
			else if (root->_right == nullptr)
			{
				//2.待删除结点，右孩子为空
				root = root->_left;
			}
			else//待删除结点，左右孩子都不为空
			{
				//找到左树的最大结点
				Node* maxleft = root->_left;
				while (maxleft->_right)
				{
					maxleft = maxleft->_right;
				}
				//交换maxleft和待删除结点的Key值，
				//并再次转换成左树删除一个单孩子结点，复用上述情况一二的代码
				swap(maxleft->_key, root->_key);
				return _Rerase(root->_left, key);
			}
			delete cur;
		}

	}

	Node* _Rfind(Node*& root, const K& key)
	{
		if (root == nullptr)
		{
			return nullptr;
		}

		if (key < root->_key)
		{
			return _Rfind(root->_left, key);
		}
		else if (key > root->_key)
		{
			return _Rfind(root->_right, key);
		}
		else
		{
			return root;
		}
	}

	bool _Rinsert(Node*& root, const K& key)
	{
		//如果BSTree还没有结点
		if (root == nullptr)
		{
			root = new Node(key);
			return true;
		}
		//BSTree已经有结点
		if (key < root->_key)
		{
			//key比当前结点小，往左树插入
			return _Rinsert(root->_left, key);
		}
		else if (key > root->_key)
		{
		
			//key比当前结点大，往右树插入
			return _Rinsert(root->_right, key);
		}
		else
		{
			return false;
		}
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " " ;
		_InOrder(root->_right);
	}

	Node* _root = nullptr;
};
