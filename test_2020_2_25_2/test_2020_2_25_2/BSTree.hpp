#pragma once
#include <iostream>
using namespace std;
template <class T>
struct BSNode
{
	BSNode(const T& data = T())
	:_pLeft(nullptr)
	, _pRight(nullptr)
	, _data(data)
	{}
	BSNode<T>* _pLeft;
	BSNode<T>* _pRight;
	T _data;
};
template <class T>
class BSTree
{
	typedef BSNode<T> Node;
private:
	Node* _pRoot;
public:
	BSTree()
		:_pRoot(nullptr)
	{}
	//查找
	Node* find(const T& data)
	{
		Node* pCur = _pRoot;
		while (pCur)
		{
			if (pCur->_data == data)
				return pCur;
			else if (pCur->_data > data)
			{
				pCur = pCur->_pLeft;
			}
			else
				pCur = pCur->_pRight;
		}
		return nullptr;
	}
	//插入
	bool insert(const T& data)
	{
		//如果二叉搜索树为空，直接插入
		if (_pRoot == nullptr)
		{
			_pRoot = new Node(data);
			return true;
		}
		//先找到要插入的位置，对二叉搜索树进行遍历，按照他的性质得到应该插在哪里
		//由于要知道插在哪儿，必须要知道插入结点的双亲是在哪里,进行循环，每一次
		//让双亲走到上一次遍历的位置，最后一次双亲就走到了待插入结点的位置
		Node* pParent = nullptr;
		Node* pCur = _pRoot;
		while (pCur)
		{
			pParent = pCur;
			if (data < pCur->_data)
			{
				pCur = pCur->_pLeft;
			}
			else if (data>pCur->_data)
			{
				pCur = pCur->_pRight;
			}
			else
				//说明此时二叉搜索树中已经有想插入的结点
				return false;
		}
		//走到这里说明找到了要插入的位置
		pCur = new Node(data);
		if (data < pParent->_data)//说明待插入结点要作为双亲节点的左孩子
		{
			pParent->_pLeft = pCur;
		}
		else
			pParent->_pRight = pCur;
		return true;
	}
	//删除
	bool erase(const T& data)
	{
		if (_pRoot == nullptr)
			return false;
		Node* pCur = _pRoot;
		Node* pParent = nullptr;
		//先找到待删除结点的位置
		while (pCur)
		{
			//这里不能像插入一样先将pParent=pCur，因为如果data==pCur->_data
			//此时进入删除操作，此时就不是待删除结点的双亲节点了，因为此时指向待删除结点
			if (data == pCur->_data)//已经找到要删除的结点
			{
				break;//跳出进行删除操作
			}
			else if (data < pCur->_data)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
		}
		//说明已经找到了要删除的结点的位置，开始删除
		//此时分为四种情况：
		//情况一：待删除结点只有右孩子，此时判断它是双亲的
		//左孩子还是右孩子，改变双亲的左右孩子指向它的右孩子即可，如果待删除结点只有右孩子
		//并且是根结点，只要让根结点指向它的右孩子即可
		//情况二：待删除结点只有左孩子，与情况一类似
		//情况三：如果待删除结点是叶子结点，可以与情况1或者情况2放在一起讨论
		//情况四：如果待删除节点具有左右孩子，此时不能直接删除，而是要在待删除节点的
		//左子树中找到最大的作为他的替代结点或者在右子树中找到最小的作为替代结点，改变指针即可
		if (pCur->_pLeft == nullptr)//情况一
		{
			//将情况一和情况三一起
			if (_pRoot == pCur)//如果此时待删除结点没有左孩子且是根结点，则直接让根结点指向它的右孩子即可
				_pRoot = pCur->_pRight;
			else
			{
				//如果待删除结点是待删除结点的双亲的右孩子
				if (pCur == pParent->_pRight)
				{
					pParent->_pRight = pCur->_pRight;
				}
				//如果待删除结点是待删除结点的双亲的左孩子
				else
				{
					pParent->_pLeft = pCur->_pRight;
				}
			}
		}
		//情况一解决完成，解决情况2
		else if (nullptr == pCur->_pRight)
		{
			//也要考虑情况三
			if (_pRoot == pCur)
				_pRoot = pCur->_pLeft;
			else
			{
				if (pCur == pParent->_pRight)
					pParent->_pRight = pCur->_pLeft;
				else
					pParent->_pLeft = pCur->_pLeft;
			}
		}
		//情况1,2,3都完成，开始情况四
		else
		{//我这里是在待删除结点的右子树中找最小的当做替代结点,也就是右子树中最左的结点
			Node* First = pCur->_pRight;//定义替代结点
			pParent = pCur;//让双亲结点走到待删除结点这里，方便后面继续遍历作为替代结点的双亲
			while (First->_pLeft)//找到最左的结点
			{
				//待删除结点的双亲节点之前已经到达了，但是我们这里要找替代结点，所以他必须走到替代结点的双亲位置
				pParent = First;
				First = First->_pLeft;
			}
			//已经到达最左了，此时First是找到的替代结点
			//将替代结点的值赋给待删除结点，然后删除替代结点
			pCur->_data = First->_data;
			if (First == pParent->_pLeft)//如果此时替代结点是它的双亲的左孩子
				pParent->_pLeft = First->_pRight;
			else//如果此时替代结点是它的双亲的右孩子，比如待删除结点就是替代结点的双亲，替代结点没有左孩子
				pParent->_pRight = First->_pRight;
			pCur = First;//此时让待删除结点指向替代结点，因为要让替代结点作为待删除结点被删除掉
		}
		//删除掉待删除结点
		delete pCur;
		pCur = nullptr;
		return true;
	}
	Node* LeftMost()//找最左的
	{
		if (_pRoot == nullptr)
			return nullptr;
		Node* pCur = _pRoot;
		while (pCur ->_pLeft)
		{
			pCur = pCur->_pLeft;
		}
		return pCur;
	}
	Node* RightMost()//找最右的
	{
		if (_pRoot == nullptr)
			return nullptr;
		Node* pCur = _pRoot;
		while (pCur->_pRight)
		{
			pCur = pCur->_pRight;
		}
		return pCur;
	}
	void Inorder()
	{
		_Inorder(_pRoot);
	}
	private:
		void _Inorder(Node* pRoot)
		{
			if (pRoot)
			{
				_Inorder(pRoot->_pLeft);
				cout << pRoot->_data << " ";
				_Inorder(pRoot->_pRight);
			}
		}
};
void TestBSTree()
{
	int array[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int> t;
	for (auto e : array)
	{
		t.insert(e);
	}
	cout << t.LeftMost()->_data<< endl;
	cout << t.RightMost()->_data << endl;
	BSNode<int>* pCur = t.find(2);
	if (pCur)
		cout << "2 is in BSTree" << endl;
	else
		cout << "2 is not in BSTree" << endl;
	t.Inorder();
	cout << endl;
	//只有右孩子---其双亲的右孩子
	t.erase(8);
	t.Inorder();
	cout << endl;
	//只有右孩子===其双亲的左孩子
	t.erase(1);
	t.Inorder();
	cout << endl;

	//左右孩子都存在
	t.erase(5);
	t.Inorder();
	cout << endl;
}
int main()
{
	TestBSTree();
	return 0;
}