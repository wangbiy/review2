#include<iostream>
using namespace std;
template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _pLeft;
	AVLTreeNode<K, V>* _pRight;
	AVLTreeNode<K, V>* _pParent;
	pair<K, V> _data;
	int _bf;
	AVLTreeNode(const pair<K, V>& data)
		: _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
		, _data(data)
		, _bf(0)
	{}
};
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		: _pRoot(NULL)
	{}
	bool Insert(const pair<K, V>& data)
	{
		if (NULL == _pRoot)
		{
			_pRoot = new Node(data);
			return true;
		}
		Node* pCur = _pRoot;
		Node* pParent = NULL;
		while (pCur)
		{
			if (data.first < pCur->_data.first){
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else if (data.first > pCur->_data.first){
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else
				return false;
		}
		pCur = new Node(data);
		if (data.first < pParent->_data.first)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		pCur->_pParent = pParent;

		while (pParent)
		{
			if (pParent->_pLeft == pCur)//如果结点插在了双亲的左子树，双亲的平衡因子--，（平衡因子这里是右子树高度-左子树高度）
				pParent->_bf--;
			else
				pParent->_bf++;//如果结点插在了双亲的右子树，双亲的平衡因子++

			if (0 == pParent->_bf)//如果双亲的平衡因子在插入之后平衡因子成为了0，这时以双亲为根结点的子树的高度没有变，跳出
				return true;
			else if (-1 == pParent->_bf || 1 == pParent->_bf)//双亲的平衡因子是1或者-1，说明在更新之前双亲的平衡因子是0，在插入之后，以双亲为根结点的子树的高度增加了
			{
				pCur = pParent;//平衡因子继续向上更新，直到双亲是空，说明更新完了，因此要有一个循环
				pParent = pCur->_pParent;
			}
			else//要不就是双亲的平衡因子是2或者-2
			{
				if (2 == pParent->_bf)//此时以双亲为根结点的右子树高度高
				{
					if (1 == pCur->_bf)//说明此时插入的结点在右子树的外侧
						RotatoL(pParent);
					else//插入的结点在右子树的里侧
						RotatoRL(pParent);
				}
				else//此时以双亲为根结点的左子树高
				{
					if (-1 == pCur->_bf)//插入的结点在左子树的最外侧
						RotatoR(pParent);
					else//插入的结点在左子树的里侧
						RotatoLR(pParent);
				}
				break;
			}
		}
		return true;
	}
	void InOrder()
	{
		cout << "InOrder:";
		_InOrder(_pRoot);
		cout << endl;
	}
private:
	//右单旋
	void RotatoR(Node* pParent)
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
		if (NULL == pPParent){
			_pRoot = pSubL;
			pSubL->_pParent = NULL;
		}
		else{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
		pParent->_bf = pSubL->_bf = 0;
	}
	//左单旋
	void RotatoL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubR;
		pSubR->_pParent = pPParent;
		if (NULL == pPParent){
			_pRoot = pSubR;
			pSubR->_pParent = NULL;
		}
		else{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
		pParent->_bf = pSubR->_bf = 0;
	}
	//左右双旋转
	void RotatoLR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		int bf = pSubLR->_bf;
		RotatoL(pParent->_pLeft);
		RotatoR(pParent);
		if (1 == bf)
			pSubL->_bf = -1;
		else if (-1 == bf)
			pParent->_bf = 1;

	}
	//右左双旋转
	void RotatoRL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		int bf = pSubRL->_bf;
		RotatoR(pParent->_pRight);
		RotatoL(pParent);
		if (1 == bf)
			pParent->_bf = -1;
		else if (-1 == bf)
			pSubR->_bf = 1;
	}
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data.first << " ";
			_InOrder(pRoot->_pRight);
		}
	}
private:
	Node* _pRoot;
};
void testAVLTree()
{
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	AVLTree<int, int> t;
	for (auto e : arr)
		t.Insert(make_pair(e, e));
	t.InOrder();
}
int main()
{
	testAVLTree();
	return 0;
}