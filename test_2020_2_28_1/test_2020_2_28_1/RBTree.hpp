#pragma once
#include <iostream>
using namespace std;
enum Color{ RED, BLACK };
template <class V>
struct RBTreeNode
{
	RBTreeNode(const V& val = V(), Color color = RED)
	:_pLeft(nullptr)
	, _pRight(nullptr)
	, _pParent(nullptr)
	, _val(val)
	, _color(color)
	{}
	RBTreeNode<V>* _pLeft;
	RBTreeNode<V>* _pRight;
	RBTreeNode<V>* _pParent;
	V _val;
	Color _color;
};
template <class V>
class RBTreeIterator
{
	typedef RBTreeNode<V> Node;
	typedef RBTreeIterator<V> Self;
public:
	RBTreeIterator(Node* pNode = nullptr)
		:_pNode(pNode)
	{}
	//让迭代器具有指针的功能
	V& operator*()
	{
		return _pNode->_val;
	}
	V* operator->()
	{
		return &(operator*());
	}
	//比较
	bool operator!=(const Self& s)const
	{
		return _pNode != s._pNode;
	}
	bool operator==(const Self& s)const
	{
		return _pNode == s._pNode;
	}
	//移动
	Self& operator++()//前置++
	{
		Increament();
		return *this;
	}
	Self& operator++(int)//后置++
	{
		Self tmp(*this);//先保存一份
		Increament();
		return tmp;
	}
	Self& operator--()
	{
		Decreament();
		return *this;
	}
	Self& operator--(int)
	{
		Self tmp(*this);
		Decreament();
		return tmp;
	}
	void Increament()//++
	{
		//按照树的中序遍历来往后走，所以根结点的下一个就是他的右子树的最左边的结点
		if (_pNode->_pRight)//右子树不为空
		{
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
			{
				_pNode = _pNode->_pLeft;
			}
		}
		else//右子树为空，按照中序遍历，如果此时_pNode在左子树的最右边，这时他的下一个是根结点，那么要使用_pNode的双亲节点，一直往上走
		{
			Node* pParent = _pNode->_pParent;
			while (_pNode == pParent->_pRight)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			if (_pNode->_pRight != pParent)
				_pNode = pParent;//最终放在双亲的位置
		}
	}
	void Decreament()//--
	{
		//_pNode在end()的位置，end--取到最大元素的位置
		if (_pNode->_pParent->_pParent == _pNode)//如果根结点的双亲（头结点）的双亲是根结点，说明
		{
			_pNode = _pNode->_pRight;
		}
		else if (_pNode->_pLeft)//如果它的左子树存在，找到左子树最右的结点
		{
			_pNode = _pNode->_pLeft;
			while (_pNode->_pRight)
			{
				_pNode = _pNode->_pRight;
			}
		}
		else
		{
			Node* pParent = _pNode->_pParent;
			while (_pNode == pParent->_pLeft)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			_pNode = pParent;
		}
	}
private:
	Node* _pNode;
};
//如果是set，这里V就代表key，但是如果是map，就代表<key,value>的键值对
//因此定义一个类型KeyofValue,表示通过value来获取key的仿函数类
//K是key的类型
template <class V, class K, class KeyofValue>
class RBTree
{
	typedef RBTreeNode<V> Node;
public:
	typedef RBTreeIterator<V> iterator;//实现迭代器第二步
public:
	RBTree()
		:_pHead(new Node)
		, _size(0)
	{
		//将头结点创建好
		_pHead->_pParent = nullptr;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}
	~RBTree()
	{
		Clear();
		delete _pHead;
		_pHead = nullptr;
	}
	iterator Begin()
	{
		return iterator(_pHead->_pLeft);
	}
	iterator End()
	{
		return iterator(_pHead);
	}
	pair<iterator, bool> Insert(const V& data)//插入，如果是map的话，这里的val就是键值对
	{
		Node* pNewNode = nullptr;
		Node*& pRoot = GetRoot();//获得根结点
		if (nullptr == pRoot)
		{
			pNewNode = pRoot = new Node(data, BLACK);//根结点是黑色的，标记一下
			pRoot->_pParent = _pHead;
		}
		else
		{
			//按照二叉搜索树的性质插入新的结点
			//1、找待插入结点在二叉搜索树中的位置
			Node* pCur = pRoot;
			Node* pParent = _pHead;
			while (pCur)
			{
				pParent = pCur;
				if (KeyofValue()(data) <KeyofValue()(pCur->_val))//如果是map，键值对不能直接比较,将key拿出来比较
				{
					pCur = pCur->_pLeft;
				}
				else if (KeyofValue()(data)>KeyofValue()(pCur->_val))
				{
					pCur = pCur->_pRight;
				}
				else
					return make_pair(iterator(pCur), false);
			}
			//插入新结点
			pNewNode = pCur = new Node(data);//标记一下
			if (KeyofValue()(data) <KeyofValue()(pParent->_val))
			{
				pParent->_pLeft = pCur;
			}
			else
			{
				pParent->_pRight = pCur;
			}
			pCur->_pParent = pParent;//更新插入结点的双亲


			//如果pParent是红色的，插入的新结点默认颜色也是红色的，违反了红黑树的性质
			while (pParent != _pHead &&pParent->_color == RED)//要考虑双亲到达根结点的情况，如果是这样，就不需要调整了，因此加上第一个条件
			{
				//分情况讨论
				Node* GrandFather = pParent->_pParent;//先找到祖父结点，这个祖父节点不需要判空，因为双亲节点是红色，而根据红黑树的性质，根结点一定是黑色，因此双亲一定有双亲
				if (pParent == GrandFather->_pLeft)//双亲是祖父的左孩子（左半边）
				{
					Node* uncle = GrandFather->_pRight;
					//情况1：叔叔结点存在且为红色
					if (uncle&&uncle->_color == RED)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						GrandFather->_color = RED;
						pCur = GrandFather;
						pParent = pCur->_pParent;
					}
					else//剩下情况2和情况3
					{
						//先处理情况3（pCur是双亲的右孩子，叔叔结点可能不存在||存在且为黑色）
						if (pCur = pParent->_pRight)
						{//情况3与情况2的区别在于将情况3以双亲为根结点的子树进行左单旋，然后交换双亲和pCur的位置交换就得到了情况1
							RotateL(pParent);
							swap(pParent, pCur);
						}
						//情况2
						GrandFather->_color = RED;
						pParent->_color = BLACK;
						RotateR(GrandFather);//右单旋完成之后就不需要再继续向上更新了，因为上面是红色或者黑色已经不重要了
					}
				}
				else//双亲是祖父的右孩子（右半边）
				{
					Node* uncle = GrandFather->_pLeft;//定义叔叔结点
					//情况1
					if (uncle && uncle->_color == RED)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						GrandFather->_color = RED;
						pCur = GrandFather;
						pParent = pCur->_pParent;
					}
					else//剩下情况2和情况3
					{
						//先处理情况3,转换为情况2
						if (pCur == pParent->_pLeft)
						{
							RotateR(pParent);
							swap(pCur, pParent);
						}
						//情况2
						GrandFather->_color = RED;
						pParent->_color = BLACK;
						RotateL(GrandFather);
					}
				}
			}

		}
		_pHead->_pLeft = LeftMost();//头结点的_pLeft域指向最小的结点
		_pHead->_pRight = RightMost();//头结点的_pRight域指向最大的节点
		pRoot->_color = BLACK;//将根结点的颜色设置为黑色，因为有可能根节点颜色会改变
		++_size;
		return pair<iterator, bool>(iterator(pNewNode), true);//这里不能直接用pCur来实例化iterator，因为在处理那3种情况的情况1时，pCur已经改变了位置，因此在前面要将新创建的新结点用PNewNode标记一下
	}
	bool Empty()const
	{
		return nullptr == GetRoot();
	}
	size_t Size()const
	{
		return _size;
	}
	void Swap(RBTree<V, K, KeyofValue>& t)
	{
		swap(_pHead->_pParent, t._pHead->_pParent);//将两个头结点的双亲交换一下即可
	}
	void Clear()
	{
		_Destroy(GetRoot());//从根开始销毁
		_size = 0;
	}

	//红黑树的验证
	void Inorder()//中序遍历
	{
		return _Inorder(GetRoot());
	}
	bool IsValidRBTree()//验证红黑树的性质
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return true;
		//判断根结点是否是黑色
		if (BLACK != pRoot->_color)
		{
			cout << "违反红黑树性质2：根结点不是黑色" << endl;
			return false;
		}
		//性质4和性质3
		//获取一条路径中黑色结点的个数
		Node* pCur = pRoot;
		size_t BlackCount = 0;
		while (pCur)
		{
			if (pCur->_color == BLACK)
				++BlackCount;
			pCur = pCur->_pLeft;
		}
		size_t pathCount = 0;
		return _IsValidRBTree(GetRoot(), BlackCount, pathCount);//封装性质3、4
	}
	iterator Find(const K& key)
	{
		Node* cur = GetRoot();
		while (cur)
		{
			if (key == KeyofValue()(cur->_val))//map要通过KeyofValue这个类型用value来获取仿函数类
				return iterator(cur);
			else if (key < KeyofValue()(key->_val))
			{
				cur = cur->_pLeft;
			}
			else
			{
				cur = cur->_pRight;
			}
		}
		return iterator(end());//没有找到就返回头结点的迭代器即可
	}
	Node* LeftMost()//获取红黑树的最左边的结点
	{
		Node* pCur = GetRoot();//从根结点开始找
		if (nullptr == pCur)
			return _pHead;
		while (pCur->_pLeft)//找最左侧结点
			pCur = pCur->_pLeft;
		return pCur;
	}
	Node* RightMost()//获取红黑树最右边的结点
	{
		Node* pCur = GetRoot();
		if (pCur == nullptr)
			return _pHead;
		while (pCur->_pRight)
			pCur = pCur->_pRight;
		return pCur;
	}

private:
	void _Destroy(Node*& pRoot)//因为还要改变PRoot指针指向，所以要加上引用
	{
		if (nullptr != pRoot)
		{
			//按照后序遍历来销毁
			_Destroy(pRoot->_pLeft);
			_Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}
	Node*& GetRoot()//获取根结点
	{
		return _pHead->_pParent;
	}
	bool _IsValidRBTree(Node* pRoot, size_t BlackCount, size_t pathCount)//遍历一条路径上的黑色结点,pathCount代表当前路径有几个黑色结点
		//这里pathCount前面不能加引用，因为如果加了引用，这个统计的就不是一条路径上黑色结点的个数，而是整个红黑树黑色结点的个数，因为如果函数体中对这个pathCount形参修改了，他一条路径上的结果就会带出去，遗留数据
	{
		if (nullptr == pRoot)
		{
			return true;
		}
		if (BLACK == pRoot->_color)
		{
			pathCount++;
		}
		Node* pParent = pRoot->_pParent;
		if (pParent != _pHead&&pParent->_color == RED&&pRoot->_color == RED)
		{
			cout << "违反性质3：不能存在连在一起的红色结点" << endl;
			return false;
		}
		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)//到达叶子结点
		{
			if (pathCount != BlackCount)
			{
				cout << "不符合性质4：每条路径黑色节点的个数不相同" << endl;
				return false;
			}

		}
		return _IsValidRBTree(pRoot->_pLeft, BlackCount, pathCount) && _IsValidRBTree(pRoot->_pRight, BlackCount, pathCount);
	}
	void RotateL(Node* pParent)//左单旋
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;
		Node* pPParent = pParent->_pParent;
		pSubR->_pParent = pPParent;
		pParent->_pParent = pSubR;

		if (pPParent == _pHead)
			_pHead->_pParent = pSubR;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
		//红黑树没有必要更新平衡因子
	}
	void RotateR(Node* pParent)//右单旋
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;

		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;

		if (pPParent == _pHead)
			_pHead->_pParent = pSubL;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}
	void _Inorder(Node* pRoot)
	{
		if (pRoot)
		{
			_Inorder(pRoot->_pLeft);
			cout << pRoot->_val << " ";
			_Inorder(pRoot->_pRight);
		}
	}
private:
	Node* _pHead;//记录头结点即可
	size_t _size;
};