#pragma once
#include <iostream>
using namespace std;
#include <vector>
enum State{ EXIST, EMPTY,DELETE};
template <class T>
struct Elem
{
	T _val;
	State _state;//Ԫ��״̬
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
		//�Ƚ�����ÿ��λ�õ�״̬��ΪEMPTY
		for (auto& e : _ht)//Ҫ�ı�e�����ݣ����ʹ������
			e._state = EMPTY;
	}
#if 0
	bool insert(const T& data)
	{
		CheckCapacity();//����Ƿ���Ҫ����
		//���ù�ϣ�����������ϣ��ַ
		int Hashaddr = HashFunc(data);
		//�ȼ���λ���Ƿ���Բ���Ԫ�أ����������ϣ��ͻ����������̽�ⷽʽ�����
		while (_ht[Hashaddr]._state != EMPTY)//���ݹ�ϣ������������Ĺ�ϣ��ַ�Ѿ�����Ԫ���˻�������һ��ɾ��Ԫ�ص�λ��
		{
			if (EXIST == _ht[Hashaddr]._state && data == _ht[Hashaddr]._val)
			{
				//˵����ϣ��ͻ��û�б�֤Ψһ��
				return false;//���ò���
			}
			//ʹ������̽�������ң�ֱ���ҵ���λ
			++Hashaddr;
			if (Hashaddr == _ht.capacity())//˵���ҵ����һ����û���ҵ���λ����ͷ��ʼ
				Hashaddr = 0;
		}
		//�ߵ�����˵���ҵ��յ�λ�ã�����
		_ht[Hashaddr]._val = data;
		_ht[Hashaddr]._state = EXIST;
		++_size;
		return true;
	}
	//����
	int Find(const T& data)
	{
		size_t Hashaddr = HashFunc(data);
		while (_ht[Hashaddr]._state != EMPTY)
		{
			if (_ht[Hashaddr]._state == EXIST && _ht[Hashaddr]._val == data)
			{
				return Hashaddr;
			}
			//���λ����ɾ�����߲���Ҫ�ҵ�ֵ���ͼ���������
			Hashaddr++;
			if (Hashaddr == _ht.capacity())
				Hashaddr = 0;
		}
		return -1;
	}
#endif
	//������̽�������̽����ʵ�ֲ���Ͳ���
	bool insert(const T& data)
	{
		CheckCapacity();//����Ƿ���Ҫ����
		size_t HashAddr = HashFunc(data);
		int i = 0;//�ڶ���̽��ʱ��ʾ�ڼ��μ��
		while (_ht[HashAddr]._state != EMPTY)
		{
			if (EXIST == _ht[HashAddr]._state && data == _ht[HashAddr]._val)
			{
				return false;
			}
			i++;//���
			if (isLine)//ʹ�����Լ��
			{
				HashAddr++;
				if (HashAddr == _ht.capacity())
				{
					HashAddr = 0;
				}
			}
			else
				//ʹ�ö���̽��
			{
				HashAddr = HashAddr + 2i + 1;//Hi+1=H0+(i+1)^2
				HashAddr %= _ht.capacity();//ʹ�����ַ�ʽ�����Խ�粻�������ѭ��
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
		int i = 0;//��ʾ���μ���i�μ��
		while (_ht[HashAddr]._state != EMPTY)
		{
			if (EXIST == _ht[HashAddr]._state && data == _ht[HashAddr]._val)
			{
				return HashAddr;
			}
			i++;
			if (isLine)//���Լ��
			{
				HashAddr++;
				if (HashAddr == _ht.capacity())
				{
					HashAddr = 0;
				}
			}
			else//���μ��
			{
				HashAddr = HashAddr + 2 * i + 1;
				HashAddr %= _ht.capacity();//���Խ��
			}
		}
		return -1;
	}
	//���Ƕ��μ�������ϣ���еĿ���λ�ñȽ��٣��ҿ�λ�ÿ��ܱȽ��˷�ʱ��
	//ɾ��
	bool Erase(const T& data)
	{
		int index = Find(data);//���ҵ�Ҫɾ����Ԫ�ص�λ��
		if (index != -1)
		{
			_ht[index]._state = DELETE;
			_size--;
			return true;
		}
		return false;
	}
	//����������ϣ��
	void Swap(HashTable<T>& ht)
	{
		_ht.swap(ht._ht);//�Ƚ�������
		swap(_size, ht._size);
	}
private:
	size_t HashFunc(const T& data)
	{
		return data%_ht.capacity();
	}
	void CheckCapacity()
	{
		//������ЧԪ���������ı��ʳ�Ϊ�������ӣ����_size/_ht.capacity()��Զ��0����˿���_size*10/_ht.capacity>=7����
		if (_size * 10 / _ht.capacity() >= 7)
		{
			//�����µĹ�ϣ������������������
			HashTable<T> newHT(_ht.capacity() * 2);
			//��ԭ��ϣ����״̬Ϊ���ڵ�Ԫ�ز��뵽�¹�ϣ����
			for (size_t i = 0; i < _ht.capacity(); ++i)
			{
				if (_ht[i]._state == EXIST)
					newHT.insert(_ht[i]._val);
			}
			//����������ϣ��
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