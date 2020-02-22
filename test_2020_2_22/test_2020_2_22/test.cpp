#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#if 0
//浅拷贝问题
namespace Daisy
{
	class string
	{
	public:
		string(const char* str = "")
		{
			if (str == nullptr)
				str = "";
			_str = new char[strlen(str) + 1];
			strcpy(_str, str);
		}
		~string()
		{
			delete[]_str;
			_str = nullptr;
		}
	private:
		char* _str;
	};
}
int main()
{
	Daisy::string s1("hello");
	Daisy::string s2(s1);
	//浅拷贝问题
	return 0;
}
#endif
#if 0
//解决浅拷贝问题方法1
namespace Daisy
{
	class string
	{
	public:
		string(const char* str = "")
		{
			if (nullptr == str)
				str = "";
			_str = new char[strlen(str) + 1];
			strcpy(_str, str);
		}
		~string()
		{
			if (_str)
			{
				delete[]_str;
				_str = nullptr;
			}
		}
		//深拷贝第一种传统写法，老老实实开空间，拷贝资源
		string(const string& s)
			:_str(new char[strlen(s._str) + 1])
		{
			strcpy(_str, s._str);
		}
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				//先开辟临时空间，然后将内容拷贝进去，释放当前对象的空间，然后让它指向临时空间即可
				char* ptr = new char[strlen(s._str) + 1];
				strcpy(ptr, s._str);
				delete[]_str;
				_str = ptr;
			}
			return *this;
		}
	private:
		char* _str;
	};
}
int main()
{
	Daisy::string s1("hello");
	Daisy::string s2(nullptr);
	Daisy::string s3(s1);
	s2 = s1;
	return 0;
}
#endif
#if 0
//深拷贝现代写法，先让别人拷贝好之后，再换回来
namespace Daisy
{
	class string
	{
	private:
		char* _str;
	public:
		string(const char* str = "")
		{
			if (str == nullptr)
				str = "";
			_str = new char[strlen(str) + 1];
			strcpy(_str, str);
		}
		~string()
		{
			if (_str)
			{
				delete[]_str;
				_str = nullptr;
			}
		}
		string(const string& s)
		{
			string pTemp(s._str);//将拷贝对象的资源拷贝构造到临时对象中
			swap(_str, pTemp._str);
		}
		string& operator=(const string& s)
		{
			string pTemp(s);//拷贝构造临时对象
			swap(_str, pTemp._str);
			return *this;
		}
	};
}
int main()
{
	Daisy::string s1("hello");
	Daisy::string s2(nullptr);
	Daisy::string s3(s1);
	s2 = s1;
	return 0;
}
#endif
//解决浅拷贝的第二种方法：计数+写时拷贝
//如果使用普通的成员变量来作为计数，两个对象共用同一块内存空间，
//在释放资源时，只有一个对象的计数发生改变，另一个并不能发生改变，
//因此不能使用这种方式使用计数，又考虑到使用static修饰的成员变量
//是所有类对象共有的，但是一旦重新调用构造函数，计数就直接变成了1
//造成问题，因此我们要使用指针
namespace Daisy
{
	class string
	{
	public:
		string(const char* str = "")
		{
			if (str == nullptr)
				str = "";
			_str = new char[strlen(str) + 1];
			strcpy(_str, str);
			_pcount = new int(1);
		}
		~string()
		{
			Release();
		}
		string(const string& s)//拷贝构造函数
			:_str(s._str)
			, _pcount(s._pcount)
		{
			++(*_pcount);
		}
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				Release();//先释放掉当前对象的内容和计数
				//进行赋值
				_str = s._str;
				_pcount = s._pcount;
				//两个对象共用同一块内存空间，对象计数+1
				++(*_pcount);
			}
			return *this;
		}
		char& operator[](size_t index)
		{
			return _str[index];
		}
		const char& operator[](size_t index)const
		{
			return _str[index];
		}

	private:
		void Release()
		{
			if (_str && 0 == --(*_pcount))
			{
				delete[]_str;
				_str = nullptr;
				delete[]_pcount;
				_pcount = nullptr;
			}
		}
	private:
		char*  _str;
		int* _pcount;
	};
}
int main()
{
	Daisy::string s1("hello");
	Daisy::string s2(s1);
	Daisy::string s3("world");
	Daisy::string s4(s3);
	s1 = s3;
	s2 = s4;
	return 0;
}