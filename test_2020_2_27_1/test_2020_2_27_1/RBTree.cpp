#include <iostream>
using namespace std;
enum Color{RED,BLACK};
template <class V>
struct RBTreeNode
{
	RBTreeNode<V>* _pLeft;
	RBTreeNode<V>* _pRight;
	RBTreeNode<V>* _pParent;
	V _val;
	Color _color;
	RBTreeNode(const V val = V(), Color color = RED)//默认结点为红色,这个构造函数是全缺省的，才能明确调用
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _val(val)
		, _color(color)
	{}
};
//实现迭代器
template <class V>
class RBTreeIterator
{
	typedef RBTreeNode<V> Node;
	typedef RBTreeIterator<V> Self;
private:
	Node* _pNode;//定义迭代器指向的结点
public:
	//第一步：构造
	RBTreeIterator(Node* pNode = nullptr)
		:_pNode(pNode)
	{}
	//第二步：重载operator->()和operator*()
	V& operator*()
	{
		return _pNode->_val;
	}
	V* operator->()
	{
		return &(operator*());
	}
	//第三步：重载operator!=()和operator==()
	bool operator!=(const Self& s)const
	{
		return _pNode != s._pNode;
	}
	bool operator==(const Self& s)const
	{
		return _pNode == s._pNode;
	}
	//第四步：重载operator++(int)/operator++()和operator--(int)/operator--()
	Self& operator++()//前置++
	{
		increament();
		return *this;
	}
	Self& operator++(int)//后置++
	{
		Self Temp(*this);
		increament();
		return Temp;
	}
	Self& operator--()
	{
		decreament();
		return *this;
	}
	Self& operator--(int)
	{
		Self Temp(*this);
		decreament();
		return Temp;
	}
private:
	void increament()
	{
		//分为三种情况
		//情况一：_pNode当前指向当前树的根结点且有右子树，则++就是走到右子树的最左边的结点
		if (_pNode->_pRight)
		{
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
			{
				_pNode = _pNode->_pLeft;
			}
		}
		else//没有右子树，此时_pNode不指向当前树的根结点，
			//而是指向左子树的最右边的结点，++后就到达了根结点
			//那么如何让_pNode到达根结点，只要定义它的双亲结点，向上更新
			//直到_pNode不是双亲节点的右孩子将_pNode走到双亲的位置即可
			//但是此时需要判断，如果此时是情况3，也就是_pNode指向根结点
			//他的双亲是头结点，他走到头结点位置，头结点走到自己的双亲根结点，造成一个循环
			//就不能满足++的特性，因此必须具有判断条件
		{
			Node* pParent = _pNode->_pParent;
			while (_pNode == pParent->_pRight)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			//判断是否要将pNode走到pParent位置
			if (_pNode->_pRight != pParent)
				_pNode = pParent;
		}
	}
	void decreament()
	{
		//同样还是三种情况
		//情况一：_pNode指向根结点且具有左子树，--就走到了左子树最右边的结点
		if (_pNode->_pLeft)
		{
			_pNode = _pNode->_pLeft;
			while (_pNode->_pRight)
			{
				_pNode = _pNode->_pRight;
			}
		}
		else//情况二和情况三
			//根结点没有左子树，此时_pNode指向根结点的右子树最左边的结点，
			//--就是走到根结点，那么如何让它走到根结点，定义他的双亲，他走到双亲的位置
			//双亲向上更新，直到它不是双亲的左孩子，让它走到双亲的位置即可
			//此时需要判断，也就是情况三，如果_pNode指向根结点，它的双亲是头结点
			//他走到双亲头结点的位置，双亲走到自己的双亲的位置，即根结点的位置，
			//就成为了一个循环，出现问题，因此需要判断是否让_pNode走到双亲的位置
		{
			Node* pParent = _pNode->_pParent;
			while (_pNode == pParent->_pLeft)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			if (_pNode->_pParent->_pParent != _pNode)
			{
				_pNode = pParent;
			}
		}
	}
};
template <class V>
class RBTree
{
	typedef RBTreeNode<V> Node;
public:
	//接下来在红黑树中实现迭代器
	//第一步：
	typedef RBTreeIterator<V> iterator;
public:
	RBTree()
		:_pHead(new Node)
	{
		//将头结点创建好
		_pHead->_pParent = nullptr;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}
	//实现begin+end即可
	iterator begin()
	{
		return iterator(_pHead->_pLeft);
	}
	iterator end()
	{
		return iterator(_pHead);//最后一个元素的下一个
	}
	//红黑树的插入
	bool Insert(const V& data)
	{
		Node*& pRoot = GetRoot();//实现一个获得根结点的函数
		if (nullptr == pRoot)
		{
			//直接插入
			pRoot = new Node(data, BLACK);//根结点是黑色的
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
				if (data < pCur->_val)
				{
					pCur = pCur->_pLeft;
				}
				else if (data>pCur->_val)
				{
					pCur = pCur->_pRight;
				}
				else
					return false;
			}
			//插入新结点
			pCur = new Node(data);
			if (data < pParent->_val)
			{
				pParent->_pLeft = pCur;
			}
			else
			{
				pParent->_pRight = pCur;
			}
			pCur->_pParent = pParent;//更新插入结点的双亲


			//如果pParent是红色的，插入的新结点默认颜色也是红色的，违反了红黑树的性质
			while (pParent != _pHead &&pParent->_color == RED)//要考虑双亲到达头结点的情况，如果是这样，就不需要调整了，因此加上第一个条件
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
						//先处理情况2（pCur是双亲的右孩子，叔叔结点可能不存在||存在且为黑色）
						if (pCur = pParent->_pRight)
						{//情况2与情况3的区别在于将情况2以双亲为根结点的子树进行左单旋，然后交换双亲和pCur的位置交换就得到了情况3
							RotateL(pParent);
							swap(pParent, pCur);
						}
						//情况3
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
						//先处理情况2,转换为情况3
						if (pCur == pParent->_pLeft)
						{
							RotateR(pParent);
							swap(pCur, pParent);
						}
						//情况3
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
		return true;
	}
	//红黑树的验证
	//第一步：验证是否是二叉搜索树
	void Inorder()
	{
		return _Inorder(GetRoot());
	}
	//第二步：验证红黑树的性质
	bool IsValidRBTree()
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
		//性质4和性质3可以使用递归的方法实现
		//获取一条路径中黑色结点的个数
		Node* pCur = pRoot;
		size_t BlackCount = 0;
		//先获得一条路径的黑色结点个数，后面进行比较即可
		while (pCur)
		{
			if (pCur->_color == BLACK)
				++BlackCount;
			pCur = pCur->_pLeft;
		}
		size_t pathCount = 0;
		return _IsValidRBTree(GetRoot(), BlackCount, pathCount);//封装性质3、4
	}
	Node* LeftMost()//获取红黑树的最左边的结点
	{
		Node* pCur = GetRoot();
		if (nullptr == pCur)
			return _pHead;
		while (pCur->_pLeft)
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
	Node* _pHead;//记录头结点
};
void TestRBTree()
{
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	RBTree<int> t;
	for (auto e : arr)
		t.Insert(e);
	t.Inorder();
	cout << endl;
	cout << t.LeftMost()->_val << endl;
	cout << t.RightMost()->_val << endl;
	if (t.IsValidRBTree())
		cout << ":)" << endl;
	else
		cout << ":(" << endl;
	//测试迭代器
	RBTree<int>::iterator it = t.begin();//利用迭代器进行遍历
	while (it != t.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
int main()
{
	TestRBTree();
	return 0;
}