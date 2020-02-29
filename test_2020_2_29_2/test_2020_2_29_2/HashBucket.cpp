#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <string>
template <class T>
struct HBNode
{
	HBNode<T>* _pNext;
	T _data;
	HBNode(const T& data)
		:_data(data)
		, _pNext(nullptr)
	{}
};
template <class T>
class DFDef//实现仿函数
{
public:
	T operator()(const T& data)
	{
		return data;
	}
};
//T--->string
size_t BKDRHash(const char* str)
{
	register size_t hash = 0;
	while (size_t ch = (size_t)*str++)
	{
		hash = hash * 131 + ch;
	}
	return hash;
}
class StringToINT
{
public:
	size_t operator()(const string& s)
	{
		return BKDRHash(s.c_str());//直接返回地址
	}
};
//实现迭代器
template <class T, class HF = DFDef<int>>//通过KeyOfValue实现通过key来获取value
class HashBucket;
template <class T, class HF>//通过KeyOfValue实现通过key来获取value
struct HBIterator
{
	typedef HBNode<T> Node;
	typedef HBIterator<T, HF> Self;
public:
	HBIterator(Node* pNode, HashBucket<T, HF>* ht)//构造函数
		:_pNode(pNode)
		, _ht(ht)
	{}
	T& operator*()
	{
		return _pNode->_data;
	}
	T* operator->()
	{
		return &(operator*());
	}
	//迭代器移动，不能--，因为哈希桶的结构是单链表
	//遍历存在的桶，将一个桶的链表遍历完成后再遍历下一个桶的链表
	Self& operator++()//前置++
	{
		Next();
		return *this;
	}
	Self& operator++(int)
	{
		Self tmp(*this);
		Next();
		return tmp;
	}
	bool operator!=(const Self& s)const
	{
		return _pNode != s._pNode && _ht == s._ht;//同一个哈希桶的不同结点
	}
	bool operator==(const Self& s)const
	{
		return !(*this != s);
	}
private:
	void Next()
	{
		if (_pNode->_pNext)//不为空，当前链表还没有处理完成
		{
			_pNode = _pNode->_pNext;
		}
		else//找下一个存在的桶
		{
			size_t bucketNo = _ht->HashFunc(_pNode->_data) + 1;//哈希函数是哈希桶类的私有成员函数，需要使用友元类
			for (; bucketNo < _ht->BucketCount(); ++bucketNo)
			{
				if (_ht->_table[bucketNo])
				{
					_pNode = _ht->_table[bucketNo];
					return;
				}
			}
			_pNode = nullptr;
		}
	}
private:
	Node* _pNode;
	HashBucket<T, HF>* _ht;//定义哈希桶指针来访问哈希桶内容
};
template <class T,class HF>//声明中已经将HF默认设置为整形来实现
class HashBucket
{
	friend HBIterator<T, HF>;//是迭代器类的友元
	typedef HashBucket<T, HF> Self;
public:
	//给迭代器取别名
	typedef HBIterator<T, HF> iterator;
public:
	HashBucket(size_t capacity = 10)
		:_table(capacity, nullptr)
		, _size(0)
	{}
	~HashBucket()
	{
		clear();
	}
	iterator begin()
	{
		for (size_t bucketNo = 0; bucketNo < BucketCount(); ++bucketNo)
		{
			if (_table[bucketNo])
				return iterator(_table[bucketNo], this);
		}
		return end();
	}
	iterator end()
	{
		return iterator(nullptr, this);
	}
	bool Insert(const T& data)
	{
		CheckCapacity();
		size_t bucketNo = HashFunc(data);//计算桶号,即第一个结点
		//检测该元素是否在桶中
		HBNode<T>* pCur = _table[bucketNo];
		while (pCur)
		{
			if (pCur->_data == data)
				return false;
			pCur = pCur->_pNext;
		}
		//插入元素
		pCur = new HBNode<T>(data);
		//头插,性能比较高
		pCur->_pNext = _table[bucketNo];
		_table[bucketNo] = pCur;
		++_size;
		return true;
	}
	HBNode<T>* Find(const T& data)
	{
		size_t bucketNo = HashFunc(data);
		HBNode<T>* pCur = _table[bucketNo];
		while (pCur)
		{
			if (pCur->_data == data)
				return pCur;
			pCur = pCur->_pNext;
		}
		return nullptr;
	}
	bool Erase(const T& data)
	{
		size_t bucketNo = HashFunc(data);
		HBNode<T>* pCur = _table[bucketNo];
		HBNode<T>* pPre = nullptr;
		while (pCur)
		{
			if (pCur->_data == data)//找到了这个桶
			{
				if (pCur == _table[bucketNo])//找到了
				{
					_table[bucketNo] = pCur->_pNext;//删除的是第一个结点,也就是头删
				}
				else//删除的不是第一个结点,就是任意位置删除
				{
					pPre->_pNext = pCur->_pNext;
				}
				delete pCur;
				--_size;
				return true;
			}
			pPre = pCur;
			pCur = pCur->_pNext;
		}
		return false;
	}
	size_t Size()const
	{
		return _size;
	}
	void Swap(HashBucket<T, HF>& hb)
	{
		_table.swap(hb._table);
		swap(_size, hb._size);
	}
	void clear()
	{
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
		{
			HBNode<T>* pCur = _table[bucketNo];
			while (pCur)
			{
				//头删
				_table[bucketNo] = pCur->_pNext;
				delete pCur;
				pCur = _table[bucketNo];
			}
		}
		_size = 0;
	}
	void Print()
	{
		for (size_t i = 0; i < _table.capacity(); ++i)
		{
			cout << "H[" << i << "]" << ":";
			HBNode<T>* pCur = _table[i];
			while (pCur)
			{
				cout << pCur->_data << "----->";
				pCur = pCur->_pNext;
			}
			cout << "NULL" << endl;
		}
	}
	size_t BucketCount()
	{
		return _table.capacity();
	}
private:
	//哈希函数
	size_t HashFunc(const T& data)
	{
		return HF()(data) % _table.capacity();//仿函数的方式
	}
	void CheckCapacity()
	{
		if (_size == _table.capacity())
		{
			HashBucket<T, HF> newHB(_size *2);
			for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
			{
				HBNode<T>* pCur = _table[bucketNo];
				////但是这种方式不太好，效率比较低，因为又重新创建了结点
				//while (pCur)
				//{
				//	newHB.Insert(pCur->_data);
				//	pCur = pCur->_pNext;
				//}
				while (pCur)
				{
					//1、计算当前结点在新哈希桶中的新桶号
					size_t newbucketNo = newHB.HashFunc(pCur->_data);
					//2、将结点从哈希表的哈希桶中拆下来
					_table[bucketNo] = pCur->_pNext;//将pCur拿出来
					//头插
					pCur->_pNext = newHB._table[newbucketNo];
					newHB._table[newbucketNo] = pCur;
					pCur = _table[bucketNo];//让pCur到原哈希桶的下一个节点
				}
			}
			Swap(newHB);
		}
	}
private:
	vector<HBNode<T>*> _table;//哈希表
	size_t _size;
};
void TestHashBucket1()
{
	HashBucket<int> ht(10);
	ht.Insert(3);
	ht.Insert(8);
	ht.Insert(4);
	ht.Insert(0);
	ht.Insert(7);
	ht.Insert(13);
	ht.Insert(33);
	cout << ht.Size() << endl;
	ht.Print();

	ht.Erase(13);
	ht.Print();

	ht.Erase(3);
	if (nullptr == ht.Find(3))
		cout << "3 is not in" << endl;
	else
		cout << "3 is in" << endl;
	ht.clear();
	cout << ht.Size() << endl;

	//测试迭代器
	auto it = ht.begin();
	while (it != ht.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
void TestHashBucket2()
{
	HashBucket<string, StringToINT> ht;
	ht.Insert("hello");
	ht.Insert("CCP");
	ht.Insert("I");
	ht.Insert("Love");
	ht.Insert("You");
	ht.Print();
	cout << ht.Size() << endl;

	ht.Erase("I");
	ht.Print();

	ht.Erase("hello");
	if (nullptr == ht.Find("hello"))
	{
		cout << "hello is not in" << endl;
	}
	else
		cout << "hello is in" << endl;
	cout << ht.Size() << endl;
}
int main()
{
	TestHashBucket1();
	TestHashBucket2();
	return 0;
}