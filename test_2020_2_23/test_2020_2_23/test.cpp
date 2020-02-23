#include <iostream>
using namespace std;
#if 0
//迭代器失效问题
#include <vector>
int main()
{
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8 };
	auto it = v.begin();
	v.push_back(9);
	//给迭代器重新赋值，因为失效了
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
		it = v.erase(it);//erase的返回值就是it的下一个位置，所以赋给it=	
	}
	cout << endl;

	return 0;
}
#endif
#if 0
//在线OJ面试题
//1.找到只出现一次的数字
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
//杨辉三角
vector<vector<int>> generate(int numsRows)
{
	vector<vector<int>> arr;
	arr.resize(numsRows);//先分配空间
	for (int i = 0; i < numsRows; ++i)
	{
		//给每一行分配空间，第0行是一个空间，第1行是两个，第2行是三个
		arr[i].resize(i + 1);
		arr[i][0] = arr[i][i] = 1;//每一行的第一列和对角线都为1
	}
	for (int i = 2; i < numsRows; ++i)//每一行
	{
		for (int j = 1; j < i; ++j)//每一列，列是随行变化的，行有几行，列就有几列
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
//vector的模拟实现
#include <assert.h>
namespace Daisy
{
	template<class T>
	class vector
	{
		typedef T* iterator;
	private:
		iterator _start;//起始位置指针，可以相当于_arr
		iterator _finish;//最后一个元素的下一个
		iterator _endofStorage;
	public:
		vector()//无参构造函数
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
		vector(T* first, T* last)//范围来构造
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
		vector(const vector<T>& v)//拷贝构造函数
		{
			size_t size = v.size();
			_start = new T[size];
			for (size_t i = 0; i < size; ++i)
			{
				_start[i] = v[i];
			}
			_finish = _endofStorage = _start + size;
		}
		vector<T>& operator=(const vector<T>& v)//赋值运算符重载
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
			if (newsize <= oldsize)//应该缩小
			{
				_finish = _start + newsize;
			}
			else
			{
				size_t oldcapacity = capacity();
				if (newsize >= oldcapacity)//如果新元素个数大于当前容量
				{
					//扩容
					reserve(newsize);
				}
				//将data追加进去
				for (size_t i = oldcapacity; i < newsize; ++i)
				{
					*_finish++ = data;
				}
			}
		}
		void reserve(size_t newcapacity)
		{
			size_t oldcapacity = capacity();
			if (oldcapacity < newcapacity)//扩容
			{
				T* temp = new T[newcapacity];
				if (_start)
				{
					size_t oldsize = size();
					//先将原有的元素拷入新空间
					for (size_t i = 0; i < oldsize; ++i)
					{
						temp[i] = _start[i];
					}
					//销毁原有空间，让它指向新空间
					delete[]_start;
					_start = temp;
					_finish = _start + oldsize;//有效元素个数
					_endofStorage = _start + newcapacity;//改变容量
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
		//增删查改
		void push_back(const T& data)
		{
			if (_finish == _endofStorage)//扩容
			{
				reserve(capacity() * 2);
			}
			(*_finish) = data;
			_finish++;
		}
		void pop_back()
		{
			if (_finish == _start)//说明为空
				return;
			--_finish;
		}
		iterator insert(iterator pos, const T& data=T())
		{
			assert(pos <= _finish);
			if (_finish == _endofStorage)//扩容
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

	v.resize(20, 6);//需要扩容
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

