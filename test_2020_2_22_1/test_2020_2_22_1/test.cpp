#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <assert.h>
namespace Daisy
{
	class string
	{
	public:
		//构造函数
		string(const char* str = "")
		{
			if (str == nullptr)
				str = "";
			_str = new char[strlen(str) + 1];
			_capacity = strlen(str);
			_size = _capacity;
			strcpy(_str, str);
		}
		//构造函数
		string(size_t n,char c)
			:_str(new char[n+1])
			, _capacity(n)
			, _size(n)
		{
			memset(_str, c, _size);
			_str[_size] = '\0';
		}
		//构造函数
		string(const char* ptr, size_t n)
		{
			size_t len = strlen(ptr);
			_size = len > n ? n : len;
			//如果传入的内容长度比要求的长度长，就按照要求的长度，否则，按照传入的内容的长度
			_capacity = _size;
			_str = new char[_capacity + 1];//分配比容量多一位的空间用来放'\0'
			for (size_t i = 0; i < _size; ++i)
			{
				_str[i] = ptr[i];
			}
			_str[_size] = '\0';
		}
		//拷贝构造函数,深拷贝
		string(const string& s)
			:_str(new char[strlen(s._str) + 1])
		{
			strcpy(_str, s._str);
			_size = s._size;
			_capacity = s._capacity;
		}
		//赋值运算符重载
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				//开辟一个临时空间，将赋值对象的内容拷贝进去，销毁当前对象，让它指向临时空间即可
				char* ptr = new char[strlen(s._str) + 1];
				strcpy(ptr, s._str);
				delete[]_str;
				_str = ptr;
				_size = s._size;
				_capacity = s._capacity;
			}
			return *this;
		}
		size_t capacity()const
		{
			return _capacity;
		}
		//增删查改
		void Reserve(size_t newcapacity)//实现扩容
		{
			if (newcapacity >capacity())
			{
				char* ptr = new char[newcapacity + 1];//开辟新空间
				strcpy(ptr, _str);//将内容拷贝进去
				delete[]_str;//销毁旧空间
				_str = ptr;//指向新空间
				_capacity = newcapacity;
			}
		}
		//尾插一个字符
		void push_back(char c)
		{
			if (_size == _capacity)
			{
				Reserve(_capacity * 2);//扩容
			}
			_str[_size++] = c;
			_str[_size] = '\0';
		}
		//尾插一个字符串
		void push_back(char* str)
		{
			int len = strlen(str);
			if (len + _size == _capacity)
			{
				_capacity = len + _capacity + 1;
				Reserve(_capacity);
			}
			while (*str != '\0')
			{
				_str[_size++] = *str++;
			}
			_str[_size] = '\0';
		}
		//头插一个字符
		void push_front(char c)
		{
			if (_size == _capacity)
			{
				Reserve(_capacity * 2);
			}
			for (size_t i = _size; i >= 0; --i)
			{
				_str[i] = _str[i - 1];
			}
			_str[0] = c;
			_size += 1;
			_str[_size] = '\0';
		}
		//头插一个字符串
		void push_front(char* str)
		{
			int len = strlen(str);
			if (len + _size == _capacity)
			{
				_capacity = _capacity + len + 1;
				Reserve(_capacity);
			}
			size_t pre = _size;
			size_t last = _size + len - 1;
			while (pre)
			{
				_str[last--] = _str[--pre];
			}
			while (*str != '\0')
			{
				_str[pre++] = *str++;
			}
			_size += len;
			_str[_size] = '\0';	
		}

		//在指定位置插入字符
		void insert(size_t pos, char c)
		{
			if (_size == _capacity)
			{
				Reserve(_capacity * 2);
			}
			for (size_t i = _size; i >= pos; --i)
			{
				_str[i] = _str[i - 1];
			}
			_str[pos] = c;
			_size++;
			_str[_size] = '\0';
		}
		//在指定位置插入字符串
		void insert(size_t pos, char* str)
		{
			int len = strlen(str);
			if (len + _size == _capacity)
			{
				_capacity = _capacity + len + 1;
				Reserve(_capacity);
			}
			size_t end = strlen(_str);
			while (end >= pos)
			{
				_str[end + len] = _str[end];
				end--;
			}
			while (*str != '\0')
			{
				_str[pos++] = *str++;
			}
			_size += len;
			_str[_size] = '\0';
		}
		//尾删一个字符
		void pop_back()
		{
			if (_size == 0)
				return;
			_size--;
			_str[_size] = '\0';
		}
		//头删一个字符
		void pop_front()
		{
			if (_size == 0)
				return;
			for (size_t i = 0; i < _size; ++i)
			{
				_str[i] = _str[i + 1];
			}
			_size--;
			_str[_size] = '\0';
		}
		//指定位置之后删除指定长度的字符
		void erase(size_t pos, size_t n)
		{
			assert(pos <= _size - 1);
			while (_str[pos + n - 1])
			{
				_str[pos - 1] = _str[pos + n - 1];
				pos++;
			}
			_size -= n;
			_str[_size] = '\0';
		}
		//[]运算符的重载
		const size_t size()const
		{
			return _size;
		}
		char& operator[](size_t index)
		{
			assert(index < size());
			return _str[index];
		}
		const char& operator[](size_t index)const
		{
			assert(index < size());
			return _str[index];
		}
		//查找一个字符
		size_t find(char c)
		{
			for (size_t i = 0; i < _size; ++i)
			{
				if (c == _str[i])
					return i;
			}
			return -1;
		}
		//查找一个字符串
		size_t find(const char* str)
		{
			size_t i = 0;//指向_str
			while (_str[i] != '\0')
			{
				if (_str[i] == *str)//继续往后走看后面的字符是否与想要找的str相同
				{
					size_t j = i;
					size_t k = 0;//指向str
					while (1)
					{
						if (str[k] == '\0')//说明遍历完了str,在_str中i指的就是找到的字符串的下标
						{
							return i;
						}
						if (_str[j] != str[k])//说明j当前所指的字符串不是要找的字符串str
							break;
						//否则
						j++;
						k++;
					}

				}
				//否则向后走一步
				++i;
			}
			return -1;
		}
		//+运算符重载,不用返回当前对象，当前对象不变
		string operator+(char ch)//加一个字符
		{
			string pTmp(_str);
			pTmp.insert(_size, ch);
			return pTmp;
		}
		string operator+(char* str)
		{
			string pTmp(_str);
			pTmp.insert(_size, str);
			return pTmp;
		}
		//+=运算符重载，要返回当前对象，当前对象发生变化
		string& operator+=(char ch)
		{
			insert(_size, ch);
			return *this;
		}
		string& operator+=(const string& str)
		{
			size_t leftlen = _capacity - _size;//剩余多少空间
			size_t str_size = str.size();//添加的字符串需要多少空间
			if (str_size > leftlen)//说明需要扩容
			{
				Reserve(_size + str_size);
			}
			strcpy(_str+_size, str._str);//意思是拼接到_str后面
			_size += str_size;
			return *this;
		}
		//>运算符重载
		bool operator>(const string& s)
		{
			char* p1 = _str;
			char* p2 = s._str;
			while (*p1 == *p2)
			{
				p1++;
				p2++;
			}
			if (*p1 > *p2)
				return true;
			else
				return false;
		}
		//==运算符重载
		bool operator==(const string& s)
		{
			char* p1 = _str;
			char* p2 = s._str;
			while (*p1 == *p2 && (*p1 != '\0' || *p2 != '\0'))
			{
				p1++;
				p2++;
			}
			if (*p1 == *p2)
				return true;
			else
				return false;
		}
		//>=运算符重载
		bool operator>=(const string& s)
		{
			if (*this > s || *this == s)
			{
				return true;
			}
			return false;
		}
		//<运算符重载
		bool operator<(const string& s)
		{
			if (!(*this >= s))
				return true;
			return false;
		}
		//<=运算符重载
		bool operator<=(const string& s)
		{
			if (*this < s || *this == s)
				return true;
			return false;
		}
		//!=运算符重载
		bool operator!=(const string& s)
		{
			if (*this == s)
				return false;
			return true;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}
int main()
{
	Daisy::string s1("hello");
	Daisy::string s2(5, 'a');
	Daisy::string s3("world", 3);
	Daisy::string s4(s3);
	Daisy::string s5(nullptr);
	s5 = s3;
	s1.push_back('a');
	s1.pop_back();
	s1.push_back("world");
	s1.push_front("b");
	s1.pop_front();
	s1.push_front("ggg");
	s1.insert(5, 'h');
	s1.erase(5, 1);
	s1.insert(8, "ff");
	s1.erase(8, 2);
	size_t index = s1.find("hl");
	cout << index << endl;

	if (s5 == s3)
		cout << ":)" << endl;
	else
		cout << ":(" << endl;
	if (s1 > s3)
		cout << ":)" << endl;
	else if (s1 == s3)
		cout << "::>" << endl;
	else
		cout << ":(" << endl;

	return 0;
}