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
	//����
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
	//����
	bool insert(const T& data)
	{
		//�������������Ϊ�գ�ֱ�Ӳ���
		if (_pRoot == nullptr)
		{
			_pRoot = new Node(data);
			return true;
		}
		//���ҵ�Ҫ�����λ�ã��Զ������������б����������������ʵõ�Ӧ�ò�������
		//����Ҫ֪�������Ķ�������Ҫ֪���������˫����������,����ѭ����ÿһ��
		//��˫���ߵ���һ�α�����λ�ã����һ��˫�׾��ߵ��˴��������λ��
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
				//˵����ʱ�������������Ѿ��������Ľ��
				return false;
		}
		//�ߵ�����˵���ҵ���Ҫ�����λ��
		pCur = new Node(data);
		if (data < pParent->_data)//˵����������Ҫ��Ϊ˫�׽ڵ������
		{
			pParent->_pLeft = pCur;
		}
		else
			pParent->_pRight = pCur;
		return true;
	}
	//ɾ��
	bool erase(const T& data)
	{
		if (_pRoot == nullptr)
			return false;
		Node* pCur = _pRoot;
		Node* pParent = nullptr;
		//���ҵ���ɾ������λ��
		while (pCur)
		{
			//���ﲻ�������һ���Ƚ�pParent=pCur����Ϊ���data==pCur->_data
			//��ʱ����ɾ����������ʱ�Ͳ��Ǵ�ɾ������˫�׽ڵ��ˣ���Ϊ��ʱָ���ɾ�����
			if (data == pCur->_data)//�Ѿ��ҵ�Ҫɾ���Ľ��
			{
				break;//��������ɾ������
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
		//˵���Ѿ��ҵ���Ҫɾ���Ľ���λ�ã���ʼɾ��
		//��ʱ��Ϊ���������
		//���һ����ɾ�����ֻ���Һ��ӣ���ʱ�ж�����˫�׵�
		//���ӻ����Һ��ӣ��ı�˫�׵����Һ���ָ�������Һ��Ӽ��ɣ������ɾ�����ֻ���Һ���
		//�����Ǹ���㣬ֻҪ�ø����ָ�������Һ��Ӽ���
		//���������ɾ�����ֻ�����ӣ������һ����
		//������������ɾ�������Ҷ�ӽ�㣬���������1�������2����һ������
		//����ģ������ɾ���ڵ�������Һ��ӣ���ʱ����ֱ��ɾ��������Ҫ�ڴ�ɾ���ڵ��
		//���������ҵ�������Ϊ������������������������ҵ���С����Ϊ�����㣬�ı�ָ�뼴��
		if (pCur->_pLeft == nullptr)//���һ
		{
			//�����һ�������һ��
			if (_pRoot == pCur)//�����ʱ��ɾ�����û���������Ǹ���㣬��ֱ���ø����ָ�������Һ��Ӽ���
				_pRoot = pCur->_pRight;
			else
			{
				//�����ɾ������Ǵ�ɾ������˫�׵��Һ���
				if (pCur == pParent->_pRight)
				{
					pParent->_pRight = pCur->_pRight;
				}
				//�����ɾ������Ǵ�ɾ������˫�׵�����
				else
				{
					pParent->_pLeft = pCur->_pRight;
				}
			}
		}
		//���һ�����ɣ�������2
		else if (nullptr == pCur->_pRight)
		{
			//ҲҪ���������
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
		//���1,2,3����ɣ���ʼ�����
		else
		{//���������ڴ�ɾ������������������С�ĵ���������,Ҳ����������������Ľ��
			Node* First = pCur->_pRight;//����������
			pParent = pCur;//��˫�׽���ߵ���ɾ������������������������Ϊ�������˫��
			while (First->_pLeft)//�ҵ�����Ľ��
			{
				//��ɾ������˫�׽ڵ�֮ǰ�Ѿ������ˣ�������������Ҫ�������㣬�����������ߵ��������˫��λ��
				pParent = First;
				First = First->_pLeft;
			}
			//�Ѿ����������ˣ���ʱFirst���ҵ���������
			//���������ֵ������ɾ����㣬Ȼ��ɾ��������
			pCur->_data = First->_data;
			if (First == pParent->_pLeft)//�����ʱ������������˫�׵�����
				pParent->_pLeft = First->_pRight;
			else//�����ʱ������������˫�׵��Һ��ӣ������ɾ���������������˫�ף�������û������
				pParent->_pRight = First->_pRight;
			pCur = First;//��ʱ�ô�ɾ�����ָ�������㣬��ΪҪ����������Ϊ��ɾ����㱻ɾ����
		}
		//ɾ������ɾ�����
		delete pCur;
		pCur = nullptr;
		return true;
	}
	Node* LeftMost()//�������
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
	Node* RightMost()//�����ҵ�
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
	//ֻ���Һ���---��˫�׵��Һ���
	t.erase(8);
	t.Inorder();
	cout << endl;
	//ֻ���Һ���===��˫�׵�����
	t.erase(1);
	t.Inorder();
	cout << endl;

	//���Һ��Ӷ�����
	t.erase(5);
	t.Inorder();
	cout << endl;
}
int main()
{
	TestBSTree();
	return 0;
}