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
	//�õ���������ָ��Ĺ���
	V& operator*()
	{
		return _pNode->_val;
	}
	V* operator->()
	{
		return &(operator*());
	}
	//�Ƚ�
	bool operator!=(const Self& s)const
	{
		return _pNode != s._pNode;
	}
	bool operator==(const Self& s)const
	{
		return _pNode == s._pNode;
	}
	//�ƶ�
	Self& operator++()//ǰ��++
	{
		Increament();
		return *this;
	}
	Self& operator++(int)//����++
	{
		Self tmp(*this);//�ȱ���һ��
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
		//����������������������ߣ����Ը�������һ����������������������ߵĽ��
		if (_pNode->_pRight)//��������Ϊ��
		{
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
			{
				_pNode = _pNode->_pLeft;
			}
		}
		else//������Ϊ�գ�������������������ʱ_pNode�������������ұߣ���ʱ������һ���Ǹ���㣬��ôҪʹ��_pNode��˫�׽ڵ㣬һֱ������
		{
			Node* pParent = _pNode->_pParent;
			while (_pNode == pParent->_pRight)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			if (_pNode->_pRight != pParent)
				_pNode = pParent;//���շ���˫�׵�λ��
		}
	}
	void Decreament()//--
	{
		//_pNode��end()��λ�ã�end--ȡ�����Ԫ�ص�λ��
		if (_pNode->_pParent->_pParent == _pNode)//���������˫�ף�ͷ��㣩��˫���Ǹ���㣬˵��
		{
			_pNode = _pNode->_pRight;
		}
		else if (_pNode->_pLeft)//����������������ڣ��ҵ����������ҵĽ��
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
//�����set������V�ʹ���key�����������map���ʹ���<key,value>�ļ�ֵ��
//��˶���һ������KeyofValue,��ʾͨ��value����ȡkey�ķº�����
//K��key������
template <class V, class K, class KeyofValue>
class RBTree
{
	typedef RBTreeNode<V> Node;
public:
	typedef RBTreeIterator<V> iterator;//ʵ�ֵ������ڶ���
public:
	RBTree()
		:_pHead(new Node)
		, _size(0)
	{
		//��ͷ��㴴����
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
	pair<iterator, bool> Insert(const V& data)//���룬�����map�Ļ��������val���Ǽ�ֵ��
	{
		Node* pNewNode = nullptr;
		Node*& pRoot = GetRoot();//��ø����
		if (nullptr == pRoot)
		{
			pNewNode = pRoot = new Node(data, BLACK);//������Ǻ�ɫ�ģ����һ��
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
				if (KeyofValue()(data) <KeyofValue()(pCur->_val))//�����map����ֵ�Բ���ֱ�ӱȽ�,��key�ó����Ƚ�
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
			//�����½��
			pNewNode = pCur = new Node(data);//���һ��
			if (KeyofValue()(data) <KeyofValue()(pParent->_val))
			{
				pParent->_pLeft = pCur;
			}
			else
			{
				pParent->_pRight = pCur;
			}
			pCur->_pParent = pParent;//���²������˫��


			//���pParent�Ǻ�ɫ�ģ�������½��Ĭ����ɫҲ�Ǻ�ɫ�ģ�Υ���˺����������
			while (pParent != _pHead &&pParent->_color == RED)//Ҫ����˫�׵�������������������������Ͳ���Ҫ�����ˣ���˼��ϵ�һ������
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
						//�ȴ������3��pCur��˫�׵��Һ��ӣ���������ܲ�����||������Ϊ��ɫ��
						if (pCur = pParent->_pRight)
						{//���3�����2���������ڽ����3��˫��Ϊ��������������������Ȼ�󽻻�˫�׺�pCur��λ�ý����͵õ������1
							RotateL(pParent);
							swap(pParent, pCur);
						}
						//���2
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
						//�ȴ������3,ת��Ϊ���2
						if (pCur == pParent->_pLeft)
						{
							RotateR(pParent);
							swap(pCur, pParent);
						}
						//���2
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
		++_size;
		return pair<iterator, bool>(iterator(pNewNode), true);//���ﲻ��ֱ����pCur��ʵ����iterator����Ϊ�ڴ�����3����������1ʱ��pCur�Ѿ��ı���λ�ã������ǰ��Ҫ���´������½����PNewNode���һ��
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
		swap(_pHead->_pParent, t._pHead->_pParent);//������ͷ����˫�׽���һ�¼���
	}
	void Clear()
	{
		_Destroy(GetRoot());//�Ӹ���ʼ����
		_size = 0;
	}

	//���������֤
	void Inorder()//�������
	{
		return _Inorder(GetRoot());
	}
	bool IsValidRBTree()//��֤�����������
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
		//����4������3
		//��ȡһ��·���к�ɫ���ĸ���
		Node* pCur = pRoot;
		size_t BlackCount = 0;
		while (pCur)
		{
			if (pCur->_color == BLACK)
				++BlackCount;
			pCur = pCur->_pLeft;
		}
		size_t pathCount = 0;
		return _IsValidRBTree(GetRoot(), BlackCount, pathCount);//��װ����3��4
	}
	iterator Find(const K& key)
	{
		Node* cur = GetRoot();
		while (cur)
		{
			if (key == KeyofValue()(cur->_val))//mapҪͨ��KeyofValue���������value����ȡ�º�����
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
		return iterator(end());//û���ҵ��ͷ���ͷ���ĵ���������
	}
	Node* LeftMost()//��ȡ�����������ߵĽ��
	{
		Node* pCur = GetRoot();//�Ӹ���㿪ʼ��
		if (nullptr == pCur)
			return _pHead;
		while (pCur->_pLeft)//���������
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
	void _Destroy(Node*& pRoot)//��Ϊ��Ҫ�ı�PRootָ��ָ������Ҫ��������
	{
		if (nullptr != pRoot)
		{
			//���պ������������
			_Destroy(pRoot->_pLeft);
			_Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}
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
	Node* _pHead;//��¼ͷ��㼴��
	size_t _size;
};