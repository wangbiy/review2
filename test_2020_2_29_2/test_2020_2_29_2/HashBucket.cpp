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
class DFDef//ʵ�ַº���
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
		return BKDRHash(s.c_str());//ֱ�ӷ��ص�ַ
	}
};
//ʵ�ֵ�����
template <class T, class HF = DFDef<int>>//ͨ��KeyOfValueʵ��ͨ��key����ȡvalue
class HashBucket;
template <class T, class HF>//ͨ��KeyOfValueʵ��ͨ��key����ȡvalue
struct HBIterator
{
	typedef HBNode<T> Node;
	typedef HBIterator<T, HF> Self;
public:
	HBIterator(Node* pNode, HashBucket<T, HF>* ht)//���캯��
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
	//�������ƶ�������--����Ϊ��ϣͰ�Ľṹ�ǵ�����
	//�������ڵ�Ͱ����һ��Ͱ�����������ɺ��ٱ�����һ��Ͱ������
	Self& operator++()//ǰ��++
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
		return _pNode != s._pNode && _ht == s._ht;//ͬһ����ϣͰ�Ĳ�ͬ���
	}
	bool operator==(const Self& s)const
	{
		return !(*this != s);
	}
private:
	void Next()
	{
		if (_pNode->_pNext)//��Ϊ�գ���ǰ����û�д������
		{
			_pNode = _pNode->_pNext;
		}
		else//����һ�����ڵ�Ͱ
		{
			size_t bucketNo = _ht->HashFunc(_pNode->_data) + 1;//��ϣ�����ǹ�ϣͰ���˽�г�Ա��������Ҫʹ����Ԫ��
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
	HashBucket<T, HF>* _ht;//�����ϣͰָ�������ʹ�ϣͰ����
};
template <class T,class HF>//�������Ѿ���HFĬ������Ϊ������ʵ��
class HashBucket
{
	friend HBIterator<T, HF>;//�ǵ����������Ԫ
	typedef HashBucket<T, HF> Self;
public:
	//��������ȡ����
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
		size_t bucketNo = HashFunc(data);//����Ͱ��,����һ�����
		//����Ԫ���Ƿ���Ͱ��
		HBNode<T>* pCur = _table[bucketNo];
		while (pCur)
		{
			if (pCur->_data == data)
				return false;
			pCur = pCur->_pNext;
		}
		//����Ԫ��
		pCur = new HBNode<T>(data);
		//ͷ��,���ܱȽϸ�
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
			if (pCur->_data == data)//�ҵ������Ͱ
			{
				if (pCur == _table[bucketNo])//�ҵ���
				{
					_table[bucketNo] = pCur->_pNext;//ɾ�����ǵ�һ�����,Ҳ����ͷɾ
				}
				else//ɾ���Ĳ��ǵ�һ�����,��������λ��ɾ��
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
				//ͷɾ
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
	//��ϣ����
	size_t HashFunc(const T& data)
	{
		return HF()(data) % _table.capacity();//�º����ķ�ʽ
	}
	void CheckCapacity()
	{
		if (_size == _table.capacity())
		{
			HashBucket<T, HF> newHB(_size *2);
			for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
			{
				HBNode<T>* pCur = _table[bucketNo];
				////�������ַ�ʽ��̫�ã�Ч�ʱȽϵͣ���Ϊ�����´����˽��
				//while (pCur)
				//{
				//	newHB.Insert(pCur->_data);
				//	pCur = pCur->_pNext;
				//}
				while (pCur)
				{
					//1�����㵱ǰ������¹�ϣͰ�е���Ͱ��
					size_t newbucketNo = newHB.HashFunc(pCur->_data);
					//2�������ӹ�ϣ��Ĺ�ϣͰ�в�����
					_table[bucketNo] = pCur->_pNext;//��pCur�ó���
					//ͷ��
					pCur->_pNext = newHB._table[newbucketNo];
					newHB._table[newbucketNo] = pCur;
					pCur = _table[bucketNo];//��pCur��ԭ��ϣͰ����һ���ڵ�
				}
			}
			Swap(newHB);
		}
	}
private:
	vector<HBNode<T>*> _table;//��ϣ��
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

	//���Ե�����
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