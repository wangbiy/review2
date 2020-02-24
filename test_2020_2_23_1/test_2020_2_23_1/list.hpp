//list模拟实现

#pragma once
#include <iostream>
using namespace std;
//listNode不是具体的类，是编译器生成存放具体数据类型的模具
template <class T>
struct ListNode//生成代码的一个工具
{
	ListNode(const T& data = T())//构造结点
	:_pNext(nullptr)
	, _pPre(nullptr)
	, _data(data)
	{}
	ListNode<T>* _pNext;
	ListNode<T>* _pPre;
	T _data;
};
namespace Daisy
{
	template<class T>
	struct list_iterator//重新给出迭代器，封装
	{
		typedef T ValueType;
		typedef ListNode<T> Node;
		typedef Node* pNode;
		typedef list_iterator<T> Self;
		list_iterator(pNode pNode = nullptr)//将这个节点给过来
			:_pNode(pNode)
		{}
		list_iterator(const Self& s)//用一个迭代器拷贝构造另一个迭代器
			:_pNode(s._pNode)
		{}
		//这个迭代器无法直接解引用取出节点中的值，可以进行重载
		T& operator*()
		{
			return _pNode->_data;
		}
		T* operator->()
		{
			return &(_pNode->_data);
		}
		Self& operator++()//前置++
		{
			_pNode = _pNode->_pNext;
			return *this;
		}
		Self& operator++(int)//后置++
		{
			Self Temp(*this);
			_pNode = _pNode->_pNext;
			return Temp;
		}
		Self& operator--()//前置--
		{
			_pNode = _pNode->_pPre;
			return *this;
		}
		Self& operator--(int)//后置--
		{
			Self Temp(*this);
			_pNode = _pNode->_pPre;
			return Temp;
		}
		bool operator!=(const Self& s)const
		{
			return _pNode != s._pNode;//两个迭代器的比较，看在没在同一个位置
		}
		bool operator==(const Self& s)const
		{
			return _pNode == s._pNode;
		}
		pNode _pNode;

	};
	template<class Iterator>//实现反向迭代器
	struct list_ReverseIterator
	{
		Iterator _it;//定义迭代器
		typedef list_ReverseIterator<Iterator> Self;
		typename typedef Iterator::ValueType T;
		//Iterator是一个类型，中间内嵌ValueType
		//如果不加typename,那么Iterator包括的ValueType可能不是一种类型
		//而是静态成员变量，应该加上typename
		list_ReverseIterator(Iterator it)
			:_it(it)
		{}
		list_ReverseIterator(const Self& L)
			:_it(L._it)
		{}
		T& operator*()//反向迭代器的解引用不是直接对迭代器所指解引用,因为打印的是迭代器的下一个元素，如果直接解引用，最终会缺一个元素
		{
			Iterator temp(_it);
			--temp;
			return *temp;
		}
		T* operator->()
		{
			return &(operator*());
		}

		Self& operator++()
		{
			--_it;
			return *this;
		}
		Self& operator++(int)//后置++
		{
			Self Temp(*this);
			--_it;
			return Temp;
		}
		Self& operator--()
		{
			++_it;
			return *this;
		}
		Self& operator--(int)
		{
			Self& Temp(*this);
			++_it;
			return Temp;
		}
		bool operator!=(const Self& L)const
		{
			return _it != L._it;
		}
		bool operator==(const Self& L)const
		{
			return _it == L._it;
		}
		
	};
	template<class T>
	class list
	{
		typedef ListNode<T> Node;
		typedef Node* pNode;
	public:
		typedef list_iterator<T> iterator;
		typedef list_ReverseIterator<iterator> reverse_iterator;//反向迭代器
	public:
		list()
		{
			createHead();
		}
		list(size_t n, const T& data = T())
		{
			createHead();
			for (size_t i = 0; i < n; ++i)
			{
				push_back(data);
			}
		}
		list(T* first, T* last)
		{
			createHead();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		list(const list<T>& L)//拷贝构造
		{
			createHead();
			pNode pCur = L._pHead->_pNext;
			while (pCur != L._pHead)
			{
				push_back(pCur->_data);
				pCur = pCur->_pNext;
			}
		}
		~list()
		{
			clear();//清空有效结点
			delete _pHead;//释放头结点
			_pHead = nullptr;
		}
		list<T>& operator=(list<T>& L)
		{
			if (this != &L)
			{
				createHead();//构造头结点
				for (const auto& e : L)
				{
					push_back(e);
				}
			}
			return *this;
			/*swap(_pHead, L._pHead);
			return *this;*/
		}
		iterator begin()
		{
			return iterator(_pHead->_pNext);//构造迭代器的对象
		}
		iterator end()
		{
			return iterator(_pHead);
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		size_t size()const
		{
			size_t count = 0;
			pNode pCur = _pHead->_pNext;
			while (pCur != _pHead)
			{
				count++;
				pCur = pCur->_pNext;
			}
			return count;
		}
		bool empty()const
		{
			return _pHead->_pNext == _pHead;
		}
		void resize(size_t newsize, const T data = T())
		{
			size_t oldsize = size();
			if (oldsize < newsize)
			{
				for (size_t i = oldsize; i < newsize; ++i)
				{
					push_back(data);
				}
			}
			else
			{
				for (size_t i = newsize; i < oldsize; ++i)
				{
					pop_back();//移除
				}
			}
		}

		T& front()
		{
			return _pHead->_pNext->_data;
		}
		const T& front()const
		{
			return _pHead->_pNext->_data;
		}
		T& back()
		{
			return _pHead->_pPre->_data;
		}
		const T& back()const
		{
			return _pHead->_pPre->_data;
		}

		void push_back(const T& data)//尾插
		{
			pNode pNewNode = new Node(data);//先给一个结点
			//先不破坏链表的结构
			pNewNode->_pNext = _pHead;
			pNewNode->_pPre = _pHead->_pPre;

			_pHead->_pPre = pNewNode;
			pNewNode->_pPre->_pNext = pNewNode;
		}
		void pop_back()//尾删
		{
			pNode pDelNode = _pHead->_pPre;
			_pHead->_pPre = pDelNode->_pPre;
			pDelNode->_pPre->_pNext = _pHead;
			delete pDelNode;
		}
		void push_front(const T& data)
		{
			pNode pNewNode = new Node(data);
			pNewNode->_pNext = _pHead->_pNext;
			pNewNode->_pPre = _pHead;
			_pHead->_pNext = pNewNode;
			pNewNode->_pNext->_pPre = pNewNode;
		}
		void pop_front()
		{
			pNode pDelNode = _pHead->_pNext;
			_pHead->_pNext = pDelNode->_pNext;
			pDelNode->_pNext->_pPre = _pHead;
			delete pDelNode;
		}
		iterator insert(iterator pos, const T& data)
			//iterator不能只单单是T*,因为如果进行遍历操作，
			//++it的话按理来说要走到下一个节点，但是并不能
			//走到下一个节点，因为list指的是链表，
			//必须用pNext来走向下一个节点,所以必须重新给一个迭代器list_iterator
		{
			pNode pNewNode = new Node(data);
			pNode pCur = pos._pNode;
			pNewNode->_pPre = pCur->_pPre;
			pNewNode->_pNext = pCur;
			pNewNode->_pPre->_pNext = pNewNode;
			pCur->_pPre = pNewNode;
			return iterator(pNewNode);
		}
		iterator erase(iterator pos)
		{
			pNode pDelNode = pos._pNode;
			if (pDelNode == _pHead)
				return _pHead;
			pNode pRet = pDelNode->_pNext;
			pDelNode->_pPre->_pNext = pDelNode->_pNext;
			pDelNode->_pNext->_pPre = pDelNode->_pPre;
			delete pDelNode;
			return iterator(pRet);//迭代器指向所删除结点的下一个
		}
	private:
		void createHead()
		{
			_pHead = new Node;
			_pHead->_pNext = _pHead;
			_pHead->_pPre = _pHead;
		}
	private:
		void clear()//将有效结点清空
		{
			pNode pCur = _pHead->_pNext;
			while (pCur != _pHead)
			{
				_pHead->_pNext = pCur->_pNext;//拿出pCur
				delete pCur;
				pCur = _pHead->_pNext;
			}
			_pHead->_pNext = _pHead;
			_pHead->_pPre = _pHead;
		}
		pNode _pHead;
	};
}
template <class T>
void Print(Daisy::list<T>& L)
{
	auto it = L.begin();
	while (it != L.end())
	{
		cout << *it << "-->";
		++it;
	}
	cout << "nullptr";
	cout << endl;
}
template <class T>
void PrintReverse(Daisy::list<T>& L)
{
	auto it = L.rbegin();
	while (it != L.rend())
	{
		cout << *it << "-->";
		++it;
	}
	cout << "nullptr";
	cout << endl;
}
void Test1()
{
	Daisy::list<int> L1;
	Daisy::list<int> L2(10, 5);
	int array[] = { 1, 2, 3, 4, 5, 6, 7 };
	Daisy::list<int> L3(array, array + sizeof(array) / sizeof(array[0]));
	Print(L3);
	PrintReverse(L3);
	Daisy::list<int> L4(L3);
	Print(L4);
	PrintReverse(L4);
	L1 = L3;
	Print(L1);
	PrintReverse(L1);
}
void Test2()
{
	Daisy::list<int> L;
	L.push_back(1);
	L.push_back(2);
	L.push_back(3);
	L.push_back(4);
	L.push_back(5);
	Print(L);
	PrintReverse(L);

	L.pop_back();
	Print(L);
	PrintReverse(L);

	L.push_front(0);
	Print(L);
	PrintReverse(L);

	L.pop_front();
	Print(L);
	PrintReverse(L);

	L.insert(L.begin(), 0);
	Print(L);
	PrintReverse(L);

	L.erase(L.begin());
	Print(L);
	PrintReverse(L);

	cout << L.size() << endl;

	L.resize(6, 0);
	cout << L.size() << endl;
	Print(L);
	PrintReverse(L);

	L.resize(3);
	cout << L.size() << endl;
	Print(L);
	PrintReverse(L);
}
int main()
{
	Test1();
	Test2();
	return 0;
}