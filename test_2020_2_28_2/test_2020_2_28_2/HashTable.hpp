#pragma once
#include <iostream>
using namespace std;
#include <vector>
enum State{ EXIST, EMPTY,DELETE};
template <class T>
struct Elem
{
	T _val;
	State _state;//元素状态
};
template <class T>
class HashTable
{
private:
	std::vector<Elem<T>> _ht;
	size_t _size;
public:
	HashTable(size_t capacity = 10)
		:_ht(capacity)
		, _size(0)
	{
		//先将表中每个位置的状态设为EMPTY
		for (auto& e : _ht)//要改变e的内容，因此使用引用
			e._state = EMPTY;
	}
#if 0
	bool insert(const T& data)
	{
		CheckCapacity();//检测是否需要扩容
		//设置哈希函数，就算哈希地址
		int Hashaddr = HashFunc(data);
		//先检测该位置是否可以插入元素，如果发生哈希冲突，采用线性探测方式来解决
		while (_ht[Hashaddr]._state != EMPTY)//根据哈希函数计算出来的哈希地址已经存在元素了或者是上一个删除元素的位置
		{
			if (EXIST == _ht[Hashaddr]._state && data == _ht[Hashaddr]._val)
			{
				//说明哈希冲突，没有保证唯一性
				return false;//不用插入
			}
			//使用线性探测往后找，直到找到空位
			++Hashaddr;
			if (Hashaddr == _ht.capacity())//说明找到最后一个都没有找到空位，从头开始
				Hashaddr = 0;
		}
		//走到这里说明找到空的位置，插入
		_ht[Hashaddr]._val = data;
		_ht[Hashaddr]._state = EXIST;
		++_size;
		return true;
	}
	//查找
	int Find(const T& data)
	{
		size_t Hashaddr = HashFunc(data);
		while (_ht[Hashaddr]._state != EMPTY)
		{
			if (_ht[Hashaddr]._state == EXIST && _ht[Hashaddr]._val == data)
			{
				return Hashaddr;
			}
			//这个位置是删除或者不是要找的值，就继续往后走
			Hashaddr++;
			if (Hashaddr == _ht.capacity())
				Hashaddr = 0;
		}
		return -1;
	}
#endif
	//将线性探测与二次探测结合实现插入和查找
	bool insert(const T& data)
	{
		CheckCapacity();//检测是否需要扩容
		size_t HashAddr = HashFunc(data);
		int i = 0;//在二次探测时表示第几次检测
		while (_ht[HashAddr]._state != EMPTY)
		{
			if (EXIST == _ht[HashAddr]._state && data == _ht[HashAddr]._val)
			{
				return false;
			}
			i++;//检测
			if (isLine)//使用线性检测
			{
				HashAddr++;
				if (HashAddr == _ht.capacity())
				{
					HashAddr = 0;
				}
			}
			else
				//使用二次探测
			{
				HashAddr = HashAddr + 2i + 1;//Hi+1=H0+(i+1)^2
				HashAddr %= _ht.capacity();//使用这种方式来解决越界不会造成死循环
			}
		}
		_ht[HashAddr]._val = data;
		_ht[HashAddr]._state = EXIST;
		_size++;
		return true;
	}
	int find(const T& data)
	{
		size_t HashAddr = HashFunc(data);
		int i = 0;//表示二次检测第i次检测
		while (_ht[HashAddr]._state != EMPTY)
		{
			if (EXIST == _ht[HashAddr]._state && data == _ht[HashAddr]._val)
			{
				return HashAddr;
			}
			i++;
			if (isLine)//线性检测
			{
				HashAddr++;
				if (HashAddr == _ht.capacity())
				{
					HashAddr = 0;
				}
			}
			else//二次检测
			{
				HashAddr = HashAddr + 2 * i + 1;
				HashAddr %= _ht.capacity();//解决越界
			}
		}
		return -1;
	}
	//但是二次检测如果哈希表中的空余位置比较少，找空位置可能比较浪费时间
	//删除
	bool Erase(const T& data)
	{
		int index = Find(data);//先找到要删除的元素的位置
		if (index != -1)
		{
			_ht[index]._state = DELETE;
			_size--;
			return true;
		}
		return false;
	}
	//交换两个哈希表
	void Swap(HashTable<T>& ht)
	{
		_ht.swap(ht._ht);//先交换内容
		swap(_size, ht._size);
	}
private:
	size_t HashFunc(const T& data)
	{
		return data%_ht.capacity();
	}
	void CheckCapacity()
	{
		//由于有效元素与容量的比率称为负载因子，因此_size/_ht.capacity()永远是0，因此可以_size*10/_ht.capacity>=7即可
		if (_size * 10 / _ht.capacity() >= 7)
		{
			//构造新的哈希表，将容量给成新容量
			HashTable<T> newHT(_ht.capacity() * 2);
			//将原哈希表中状态为存在的元素插入到新哈希表中
			for (size_t i = 0; i < _ht.capacity(); ++i)
			{
				if (_ht[i]._state == EXIST)
					newHT.insert(_ht[i]._val);
			}
			//交换两个哈希表
			Swap(newHT);
		}
	}
};
void TestHashTable()
{
	HashTable<int> ht;
	ht.insert(4);
	ht.insert(7);
	ht.insert(8);
	ht.insert(27);

	ht.Erase(2);
	HashTable<int> ht2;
	ht2.insert(1);
	ht2.insert(3);
	ht2.insert(7);
	ht2.Swap(ht);
}
int main()
{
	TestHashTable();
	return 0;
}