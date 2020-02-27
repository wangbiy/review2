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
	RBTreeNode(const V val = V(), Color color = RED)//Ĭ�Ͻ��Ϊ��ɫ,������캯����ȫȱʡ�ģ�������ȷ����
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _val(val)
		, _color(color)
	{}
};
//ʵ�ֵ�����
template <class V>
class RBTreeIterator
{
	typedef RBTreeNode<V> Node;
	typedef RBTreeIterator<V> Self;
private:
	Node* _pNode;//���������ָ��Ľ��
public:
	//��һ��������
	RBTreeIterator(Node* pNode = nullptr)
		:_pNode(pNode)
	{}
	//�ڶ���������operator->()��operator*()
	V& operator*()
	{
		return _pNode->_val;
	}
	V* operator->()
	{
		return &(operator*());
	}
	//������������operator!=()��operator==()
	bool operator!=(const Self& s)const
	{
		return _pNode != s._pNode;
	}
	bool operator==(const Self& s)const
	{
		return _pNode == s._pNode;
	}
	//���Ĳ�������operator++(int)/operator++()��operator--(int)/operator--()
	Self& operator++()//ǰ��++
	{
		increament();
		return *this;
	}
	Self& operator++(int)//����++
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
		//��Ϊ�������
		//���һ��_pNode��ǰָ��ǰ���ĸ������������������++�����ߵ�������������ߵĽ��
		if (_pNode->_pRight)
		{
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
			{
				_pNode = _pNode->_pLeft;
			}
		}
		else//û������������ʱ_pNode��ָ��ǰ���ĸ���㣬
			//����ָ�������������ұߵĽ�㣬++��͵����˸����
			//��ô�����_pNode�������㣬ֻҪ��������˫�׽�㣬���ϸ���
			//ֱ��_pNode����˫�׽ڵ���Һ��ӽ�_pNode�ߵ�˫�׵�λ�ü���
			//���Ǵ�ʱ��Ҫ�жϣ������ʱ�����3��Ҳ����_pNodeָ������
			//����˫����ͷ��㣬���ߵ�ͷ���λ�ã�ͷ����ߵ��Լ���˫�׸���㣬���һ��ѭ��
			//�Ͳ�������++�����ԣ���˱�������ж�����
		{
			Node* pParent = _pNode->_pParent;
			while (_pNode == pParent->_pRight)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			//�ж��Ƿ�Ҫ��pNode�ߵ�pParentλ��
			if (_pNode->_pRight != pParent)
				_pNode = pParent;
		}
	}
	void decreament()
	{
		//ͬ�������������
		//���һ��_pNodeָ�������Ҿ�����������--���ߵ������������ұߵĽ��
		if (_pNode->_pLeft)
		{
			_pNode = _pNode->_pLeft;
			while (_pNode->_pRight)
			{
				_pNode = _pNode->_pRight;
			}
		}
		else//������������
			//�����û������������ʱ_pNodeָ�����������������ߵĽ�㣬
			//--�����ߵ�����㣬��ô��������ߵ�����㣬��������˫�ף����ߵ�˫�׵�λ��
			//˫�����ϸ��£�ֱ��������˫�׵����ӣ������ߵ�˫�׵�λ�ü���
			//��ʱ��Ҫ�жϣ�Ҳ��������������_pNodeָ�����㣬����˫����ͷ���
			//���ߵ�˫��ͷ����λ�ã�˫���ߵ��Լ���˫�׵�λ�ã���������λ�ã�
			//�ͳ�Ϊ��һ��ѭ�����������⣬�����Ҫ�ж��Ƿ���_pNode�ߵ�˫�׵�λ��
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
	//�������ں������ʵ�ֵ�����
	//��һ����
	typedef RBTreeIterator<V> iterator;
public:
	RBTree()
		:_pHead(new Node)
	{
		//��ͷ��㴴����
		_pHead->_pParent = nullptr;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}
	//ʵ��begin+end����
	iterator begin()
	{
		return iterator(_pHead->_pLeft);
	}
	iterator end()
	{
		return iterator(_pHead);//���һ��Ԫ�ص���һ��
	}
	//������Ĳ���
	bool Insert(const V& data)
	{
		Node*& pRoot = GetRoot();//ʵ��һ����ø����ĺ���
		if (nullptr == pRoot)
		{
			//ֱ�Ӳ���
			pRoot = new Node(data, BLACK);//������Ǻ�ɫ��
			pRoot->_pParent = _pHead;
		}
		else
		{
			//���ն��������������ʲ����µĽ��
			//1���Ҵ��������ڶ����������е�λ��
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
			//�����½��
			pCur = new Node(data);
			if (data < pParent->_val)
			{
				pParent->_pLeft = pCur;
			}
			else
			{
				pParent->_pRight = pCur;
			}
			pCur->_pParent = pParent;//���²������˫��


			//���pParent�Ǻ�ɫ�ģ�������½��Ĭ����ɫҲ�Ǻ�ɫ�ģ�Υ���˺����������
			while (pParent != _pHead &&pParent->_color == RED)//Ҫ����˫�׵���ͷ���������������������Ͳ���Ҫ�����ˣ���˼��ϵ�һ������
			{
				//���������
				Node* GrandFather = pParent->_pParent;//���ҵ��游��㣬����游�ڵ㲻��Ҫ�пգ���Ϊ˫�׽ڵ��Ǻ�ɫ�������ݺ���������ʣ������һ���Ǻ�ɫ�����˫��һ����˫��
				if (pParent == GrandFather->_pLeft)//˫�����游�����ӣ����ߣ�
				{
					Node* uncle = GrandFather->_pRight;
					//���1�������������Ϊ��ɫ
					if (uncle&&uncle->_color == RED)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						GrandFather->_color = RED;
						pCur = GrandFather;
						pParent = pCur->_pParent;
					}
					else//ʣ�����2�����3
					{
						//�ȴ������2��pCur��˫�׵��Һ��ӣ���������ܲ�����||������Ϊ��ɫ��
						if (pCur = pParent->_pRight)
						{//���2�����3���������ڽ����2��˫��Ϊ��������������������Ȼ�󽻻�˫�׺�pCur��λ�ý����͵õ������3
							RotateL(pParent);
							swap(pParent, pCur);
						}
						//���3
						GrandFather->_color = RED;
						pParent->_color = BLACK;
						RotateR(GrandFather);//�ҵ������֮��Ͳ���Ҫ�ټ������ϸ����ˣ���Ϊ�����Ǻ�ɫ���ߺ�ɫ�Ѿ�����Ҫ��
					}
				}
				else//˫�����游���Һ��ӣ��Ұ�ߣ�
				{
					Node* uncle = GrandFather->_pLeft;//����������
					//���1
					if (uncle && uncle->_color == RED)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						GrandFather->_color = RED;
						pCur = GrandFather;
						pParent = pCur->_pParent;
					}
					else//ʣ�����2�����3
					{
						//�ȴ������2,ת��Ϊ���3
						if (pCur == pParent->_pLeft)
						{
							RotateR(pParent);
							swap(pCur, pParent);
						}
						//���3
						GrandFather->_color = RED;
						pParent->_color = BLACK;
						RotateL(GrandFather);
					}
				}
			}

		}
		_pHead->_pLeft = LeftMost();//ͷ����_pLeft��ָ����С�Ľ��
		_pHead->_pRight = RightMost();//ͷ����_pRight��ָ�����Ľڵ�
		pRoot->_color = BLACK;//����������ɫ����Ϊ��ɫ����Ϊ�п��ܸ��ڵ���ɫ��ı�
		return true;
	}
	//���������֤
	//��һ������֤�Ƿ��Ƕ���������
	void Inorder()
	{
		return _Inorder(GetRoot());
	}
	//�ڶ�������֤�����������
	bool IsValidRBTree()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return true;
		//�жϸ�����Ƿ��Ǻ�ɫ
		if (BLACK != pRoot->_color)
		{
			cout << "Υ�����������2������㲻�Ǻ�ɫ" << endl;
			return false;
		}
		//����4������3����ʹ�õݹ�ķ���ʵ��
		//��ȡһ��·���к�ɫ���ĸ���
		Node* pCur = pRoot;
		size_t BlackCount = 0;
		//�Ȼ��һ��·���ĺ�ɫ��������������бȽϼ���
		while (pCur)
		{
			if (pCur->_color == BLACK)
				++BlackCount;
			pCur = pCur->_pLeft;
		}
		size_t pathCount = 0;
		return _IsValidRBTree(GetRoot(), BlackCount, pathCount);//��װ����3��4
	}
	Node* LeftMost()//��ȡ�����������ߵĽ��
	{
		Node* pCur = GetRoot();
		if (nullptr == pCur)
			return _pHead;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;
		return pCur;
	}
	Node* RightMost()//��ȡ��������ұߵĽ��
	{
		Node* pCur = GetRoot();
		if (pCur == nullptr)
			return _pHead;
		while (pCur->_pRight)
			pCur = pCur->_pRight;
		return pCur;
	}
private:
	Node*& GetRoot()//��ȡ�����
	{
		return _pHead->_pParent;
	}
	bool _IsValidRBTree(Node* pRoot, size_t BlackCount, size_t pathCount)//����һ��·���ϵĺ�ɫ���,pathCount����ǰ·���м�����ɫ���
		//����pathCountǰ�治�ܼ����ã���Ϊ����������ã����ͳ�ƵľͲ���һ��·���Ϻ�ɫ���ĸ��������������������ɫ���ĸ�������Ϊ����������ж����pathCount�β��޸��ˣ���һ��·���ϵĽ���ͻ����ȥ����������
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
			cout << "Υ������3�����ܴ�������һ��ĺ�ɫ���" << endl;
			return false;
		}
		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)//����Ҷ�ӽ��
		{
			if (pathCount != BlackCount)
			{
				cout << "����������4��ÿ��·����ɫ�ڵ�ĸ�������ͬ" << endl;
				return false;
			}
		}
		return _IsValidRBTree(pRoot->_pLeft, BlackCount, pathCount) && _IsValidRBTree(pRoot->_pRight, BlackCount, pathCount);
	}
	void RotateL(Node* pParent)//����
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
		//�����û�б�Ҫ����ƽ������
	}
	void RotateR(Node* pParent)//�ҵ���
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
	Node* _pHead;//��¼ͷ���
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
	//���Ե�����
	RBTree<int>::iterator it = t.begin();//���õ��������б���
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