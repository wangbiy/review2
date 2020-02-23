#include <iostream>
using namespace std;
#if 0
//������ʧЧ����
#include <vector>
int main()
{
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8 };
	auto it = v.begin();
	v.push_back(9);
	//�����������¸�ֵ����ΪʧЧ��
	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
	it = v.begin();
	while (it != v.end())
	{
		it = v.erase(it);//erase�ķ���ֵ����it����һ��λ�ã����Ը���it=	
	}
	cout << endl;

	return 0;
}
#endif
#if 0
//����OJ������
//1.�ҵ�ֻ����һ�ε�����
#include <vector>
int singleNumber(vector<int>& arr)
{
	int hashtable[256] = { 0 };
	for (int i = 0; i < arr.size(); ++i)
	{
		hashtable[arr[i]]++;		
	}
	for (int i = 0; i < arr.size(); ++i)
	{
		if (hashtable[arr[i]] == 1)
			return arr[i];
	}
	return 0;
}
//�������
vector<vector<int>> generate(int numsRows)
{
	vector<vector<int>> arr;
	arr.resize(numsRows);//�ȷ���ռ�
	for (int i = 0; i < numsRows; ++i)
	{
		//��ÿһ�з���ռ䣬��0����һ���ռ䣬��1������������2��������
		arr[i].resize(i + 1);
		arr[i][0] = arr[i][i] = 1;//ÿһ�еĵ�һ�кͶԽ��߶�Ϊ1
	}
	for (int i = 2; i < numsRows; ++i)//ÿһ��
	{
		for (int j = 1; j < i; ++j)//ÿһ�У��������б仯�ģ����м��У��о��м���
		{
			arr[i][j] = arr[i - 1][j] + arr[i - 1][j - 1];
		}
	}
	return arr;
}
int main()
{
	vector<int> arr{ 2, 1, 3, 3, 2, 4, 4, 1, 5, 6, 6, 7 };
	int result = singleNumber(arr);
	cout << result << endl;
	
	vector<vector<int>> ret = generate(5);
	return 0;
}
#endif
//vector��ģ��ʵ��
#include <assert.h>
namespace Daisy
{
	template<class T>
	class vector
	{
		typedef T* iterator;
	private:
		iterator _start;//��ʼλ��ָ�룬�����൱��_arr
		iterator _finish;//���һ��Ԫ�ص���һ��
		iterator _endofStorage;
	public:
		vector()//�޲ι��캯��
			:_start(nullptr)
			, _finish(nullptr)
			, _endofStorage(nullptr)
		{}
		vector(size_t n, const T& data = T())
			:_start(new T[n])
			, _finish(_start + n)
			, _endofStorage(_finish)
		{
			for (size_t i = 0; i < n; ++i)
			{
				_start[i] = data;
			}
		}
		vector(T* first, T* last)//��Χ������
		{
			size_t size = last - first;
			_start = new T[size];
			for (size_t i = 0; i < size; ++i)
			{
				_start[i] = first[i];
			}
			_finish = _endofStorage = size + _start;
		}
		~vector()
		{
			if (_start)
			{
				delete[]_start;
				_start = nullptr;
				_finish = nullptr;
				_endofStorage = nullptr;
			}
		}
		vector(const vector<T>& v)//�������캯��
		{
			size_t size = v.size();
			_start = new T[size];
			for (size_t i = 0; i < size; ++i)
			{
				_start[i] = v[i];
			}
			_finish = _endofStorage = _start + size;
		}
		vector<T>& operator=(const vector<T>& v)//��ֵ���������
		{
			Swap(v);
			return *this;
		}
		void Swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofStorage, v._endofStorage);
		}
		size_t size()const
		{
			return _finish - _start;
		}
		size_t capacity()const
		{
			return _endofStorage - _start;
		}
		bool empty()const
		{
			return _start == _finish;
		}
		void resize(size_t newsize, const T data = T())
		{
			size_t oldsize = size();
			if (newsize <= oldsize)//Ӧ����С
			{
				_finish = _start + newsize;
			}
			else
			{
				size_t oldcapacity = capacity();
				if (newsize >= oldcapacity)//�����Ԫ�ظ������ڵ�ǰ����
				{
					//����
					reserve(newsize);
				}
				//��data׷�ӽ�ȥ
				for (size_t i = oldcapacity; i < newsize; ++i)
				{
					*_finish++ = data;
				}
			}
		}
		void reserve(size_t newcapacity)
		{
			size_t oldcapacity = capacity();
			if (oldcapacity < newcapacity)//����
			{
				T* temp = new T[newcapacity];
				if (_start)
				{
					size_t oldsize = size();
					//�Ƚ�ԭ�е�Ԫ�ؿ����¿ռ�
					for (size_t i = 0; i < oldsize; ++i)
					{
						temp[i] = _start[i];
					}
					//����ԭ�пռ䣬����ָ���¿ռ�
					delete[]_start;
					_start = temp;
					_finish = _start + oldsize;//��ЧԪ�ظ���
					_endofStorage = _start + newcapacity;//�ı�����
				}
			}
		}
		T& operator[](size_t index)
		{
			assert(index <= size());
			return _start[index];
		}
		const T& operator[](size_t index)const
		{
			assert(index <= size());
			return _start[index];
		}
		T& front()
		{
			return _start[0];
		}
		const T& front()const
		{
			return _start[0];
		}
		T& back()
		{
			return *(_finish - 1);
		}
		const T& back()const
		{
			return *(_finish - 1);
		}
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		//��ɾ���
		void push_back(const T& data)
		{
			if (_finish == _endofStorage)//����
			{
				reserve(capacity() * 2);
			}
			(*_finish) = data;
			_finish++;
		}
		void pop_back()
		{
			if (_finish == _start)//˵��Ϊ��
				return;
			--_finish;
		}
		iterator insert(iterator pos, const T& data=T())
		{
			assert(pos <= _finish);
			if (_finish == _endofStorage)//����
			{
				reserve(capacity() * 2);
			}
			for (int i = size()-1; i >= pos-_start; --i)
			{
				_start[i + 1] = _start[i];
			}
			*pos = data;
			++ _finish;
			return pos;
		}
		iterator erase(iterator pos)
		{
			assert(pos <= _finish);
			iterator pCur = pos;
			iterator pCurNext = pos + 1;
			while (pCurNext != _finish)
			{
				*pCur++ = *pCurNext++;
			}
			_finish--;
			return pos;
		}
		void clear()
		{
			_finish = _start;
		}
	};
}
void Print(Daisy::vector<int>& v)
{
	auto it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
void Test1()
{
	Daisy::vector<int> v1;
	Daisy::vector<int> v2(10, 5);
	Print(v2);
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	Daisy::vector<int> v3(arr, arr + sizeof(arr) / sizeof(arr[0]));
	Print(v3);
	Daisy::vector<int> v4(v3);
	Print(v4);
}
void Test2()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	Daisy::vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));
	Print(v);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(3);
	Print(v);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(6, 6);
	Print(v);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(9);
	Print(v);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(20, 6);//��Ҫ����
	Print(v);
	cout << v.size() << endl;
	cout << v.capacity() << endl;
}
void Test3()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	Daisy::vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));
	Print(v);
	cout << v[6] << endl;
	cout << v.front() << endl;
	cout << v.back() << endl;

	v.insert(v.begin(), 0);
	Print(v);
	v.erase(v.begin());
	Print(v);
	v.push_back(8);
	Print(v);
	v.pop_back();
	Print(v);
}
int main()
{
	Test1();
	Test2();
	Test3();
	return 0;
}

