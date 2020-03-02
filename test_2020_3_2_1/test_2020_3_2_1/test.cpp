#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
//C++11
#if 0
//列表初始化
//多个对象的列表初始化
#include <initializer_list>
namespace Daisy
{
	template <class T>
	class vector
	{
		typedef T* iterator;
	private:
		iterator _start;
		iterator _end;
		iterator _endofstorage;
	public:
		vector()
		{
			_start = _end = _endofstorage;
		}
		//提供带有initializer_list参数的构造函数
		vector(const initializer_list<T>& il)
			:_start(new T[il.size()])
		{
			auto it = il.begin();
			_finish = _start;
			while (it != il.end())
			{
				*_finish++ = *it;
				it++;
			}
		}
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
	};
}
int main()
{
	Daisy::vector<int> v1;
	Daisy::vector<int> v2{ 1, 2, 3, 4, 5 };//可以进行列表初始化
	return 0;
}
#endif
//变量类型推导
#if 0
#include <map>
#include <string>
int main()
{
	short a = 32670;
	short b = 32670;
	short c = a + b;//无法得到想要的结果
	map<string, string> m{ { "apple", "苹果" }, { "banana", "香蕉" } };//这种迭代器太过繁琐
	map<string, string>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << " " << it->second;
		it++;
	}
	cout << endl;
	return 0;
}
#endif
#if 0
//上述无法推导出c的类型，而且迭代器类型太繁琐，因此使用auto关键字
#include <map>
#include <string>
int main()
{
	auto a = 32670;
	auto b = 32670;
	auto c = a + b;
	map<string, string> m{ { "apple", "苹果" }, { "banana", "香蕉" } };
	auto it = m.begin();
	while (it != m.end())
	{
		cout << it->first << " " << it->second;
		it++;
	}
	cout << endl;
	return 0;
}
#endif
#if 0
//但是auto在有些情况下无法使用，例如
template <class T1,class T2>
auto Add(const T1& left, const T2& right)//不知道该返回T1还是T2
{
	return left + right;
}
int main()
{
	return 0;
}
#endif
//此时编译器无法推导出auto的类型，因此需要decltype关键字
#if 0
//1.推演表达式类型作为变量的实际类型
int main()
{
	short a = 32670;
	short b = 32670;
	decltype(a + b)c;
	cout << typeid(c).name() << endl;
	return 0;
}
#endif
#if 0
//返回值类型追踪
template <class T1,class T2>
auto Add(const T1& left, const T2& right)->decltype(left + right)
{
	return left + right;
}
int main()
{
	cout << typeid(Add(1, 2.0)).name() << endl;
	return 0;
}
#endif
//默认函数控制
#if 0
//显式缺省函数，利用=default来控制
class Date
{
public:
	Date() = default;
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d;
	return 0;
}
#endif
#if 0
//删除默认函数
class Date
{
public:
	Date() = delete;
};
int main()
{
	Date d;//显示尝试引用已删除的函数
	return 0;
}
#endif
//lambde表达式
#if 0
//首先利用仿函数实现自定义类型的排序
#include <algorithm>
struct Goods
{
	string _name;
	double _price;
};
struct com
{
	bool operator()(const Goods& g1, const Goods& g2)
	{
		return g1._price <= g2._price;
	}
};
int main()
{
	Goods gd[] = { { "苹果", 3.1 }, { "香蕉", 2.5 }, { "橘子", 4.0 } };
	sort(gd, gd + sizeof(gd) / sizeof(gd[0]),com());
	return 0;
}
#endif
#if 0
//利用函数指针实现排序
#include <algorithm>
struct Goods
{
	string _name;
	double _price;
};
bool Compare(const Goods& g1, const Goods& g2)
{
	return g1._price <= g2._price;
}
int main()
{
	Goods gd[] = { { "苹果", 3.1 }, { "香蕉", 2.5 }, { "橘子", 4.0 } };
	sort(gd, gd + sizeof(gd) / sizeof(gd[0]), Compare);
	return 0;
}
#endif
//lambda表达式
#if 0
#include <algorithm>
struct Goods
{
	string _name;
	double _price;
};
int main()
{
	Goods gd[] = { { "苹果", 3.1 }, { "香蕉", 2.5 }, { "橘子", 4.0 } };
	sort(gd, gd + sizeof(gd) / sizeof(gd[0]),
		[](const Goods& g1, const Goods& g2)->bool
	{
		return g1._price <= g2._price;
	});
	return 0;
}
#endif
//捕获列表说明
#if 0
int main()
{
	int a = 10;
	int b = 20;
	int c = 0;
	cout << &c << endl;
	auto add = [c](const int left, const int right)mutable
	{
		cout << &c << endl;//前后地址不同
		c=left + right;
	};
	add(1, 2);//c值没有发生变化，因为是值传递
	return 0;
}
#endif
#if 0
int main()
{
	int a = 10;
	int b = 20;
	int c = 0;
	cout << &c << endl;
	auto add = [&c](const int left, const int right)mutable
	{
		cout << &c << endl;//前后地址相同
		c = left + right;
	};
	add(1, 2);//c值发生变化，因为是址传递
	return 0;
}
#endif
#if 0
int main()
{
	int a = 10;
	int b = 20;
	int c = 0;
	cout << &a << endl;
	cout << &b << endl;
	cout << &c << endl;
	auto add = [=](const int& left,const int& right)mutable
	{
		cout << &a << endl;
		cout << &b << endl;
		cout << &c << endl;//a b c前后地址不同，因为是按照值传递的方式捕获父作用域所有变量
		c = left + right;
	};
	add(1, 2);//c没有发生变化
	return 0;
}
#endif
#if 0
int main()
{
	int a = 10;
	int b = 20;
	int c = 0;
	cout << &a << endl;
	cout << &b << endl;
	cout << &c << endl;
	auto add = [&](const int& left, const int& right)mutable
	{
		cout << &a << endl;
		cout << &b << endl;
		cout << &c << endl;//a b c前后地址相同，因为是按照引用传递的方式捕获父作用域所有变量
		c = left + right;
	};
	add(1, 2);//c变成3
	return 0;
}
#endif
#if 0
//lambda表达式底层实现原理
class Rate
{
public:
	Rate(double rate)
		:_rate(rate)
	{}
	double operator()(double money, int year)
	{
		return money*_rate*year;
	}
private:
	double _rate;
};
int main()
{
	double rate = 0.49;
	Rate r1(rate);
	r1(1000, 3);//仿函数方式调用
	//lambda表达式
	auto r2 = [=](double money, int year)->double
	{
		return money*rate*year;
	};
	r2(1000, 2);
	return 0;
}
//发现lambda表达式底层是按照函数对象的方式实现的，
//lambda表达式会自动生成一个类，捕获列表相当于类的成员变量
//参数列表、返回值类型、函数实现体相当于operator()
#endif
//移动语义
#if 0
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
		string(const string& s)//拷贝构造
			:_str(new char[strlen(s._str)+1])
		{
			strcpy(_str, s._str);
		}
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				char* ptr = new char[strlen(s._str) + 1];
				strcpy(ptr, s._str);
				delete[]_str;
				_str = ptr;//直接改变指针指向临时空间即可
			}
			return *this;
		}
		string operator+(const string& s)
		{
			char* ptr = new char[strlen(_str) + strlen(s._str) + 1];
			strcpy(ptr, _str);
			strcpy(ptr, s._str);
			string ret(ptr);
			return ret;
		}
	};
}
void Teststring()
{
	Daisy::string s1("hello");
	Daisy::string s2("world");
	Daisy::string s3;
	s3 = s1 + s2;
	//s3对象的内容是s1和s2相加得来，进行了+运算符重载，不能改变左右操作数
	//因此我们返回的不是当前对象，也不能返回参数s，返回一个结果，返回值是以值的形式返回，
	//我们创建对象ret，由于我们构造的ret在栈上，它包含的指针指向的内容“hello world”在堆上，
	//我们以值的形式返回，在返回时也创建了一个临时对象，也包含了指针，指向的内容“hello world”在堆上，
	//也就是s3=ret；我们可以发现ret与临时对象以及s3的指针所指向的内容是一样的，产生了一个资源释放又申请的问题，
	//效率不高并且浪费空间，ret相对于临时对象是一个将亡值，临时对象相当于s3是一个将亡值，因此我们可以解决一个空间释放完又申请一个的问题，
	//采用资源转移，也就是移动语义，有效缓解效率比较低浪费资源的问题，（即先将ret中的指针转移给临时对象，再将临时对象的指针转移给s3）
}
int main()
{
	Teststring();
	return 0;
}
#endif
#if 0
//因此可以将代码改为
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
		string(const string& s)
			:_str(new char[strlen(s._str) + 1])
		{
			strcpy(_str, s._str);
		}
		//移动构造
		string(string&& s)//由于s中的内容会发生改变，因此两个&&
			:_str(s._str)//将s中的资源转移给_str
		{
			s._str = nullptr;//转移完成之后就可以置空
		}
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				char* str = new char[strlen(s._str) + 1];
				strcpy(str, s._str);
				delete[] _str;
				_str = str;
			}
			return *this;
		}
		//移动赋值
		string& operator=(string&& s)
		{
			if (this != &s)
			{
				delete[]_str;
				_str = s._str;//将资源转移给_str
				s._str = nullptr;//资源转移完成之后置空
			}
			return *this;
		}
		~string()
		{
			if (_str)
			{
				delete[]_str;
				_str = nullptr;
			}
		}
		string operator+(const string& s)
		{
			char* ptr = new char[strlen(_str) + strlen(s._str) + 1];
			strcpy(ptr, _str);
			strcpy(ptr, s._str);
			string strRet(ptr);
			return strRet;
		}
	};
}
int main()
{
	Daisy::string s1("hello");
	Daisy::string s2("world");
	Daisy::string s3;
	s3 = s1 + s2;
	return 0;
}
#endif
#if 0
//移动构造move的使用
class Person
{
private:
	char* _name;
	char* _sex;
	int _age;
public:
	Person(char* name, char* sex, int age)
		:_name(name)
		, _sex(sex)
		, _age(age)
	{}
	//移动构造
	Person(Person&& p)
		: _name(move(p._name))
		, _sex(move(p._sex))
		, _age(p._age)
	{}
	Person(const Person& p)
		:_name(p._name)
		, _sex(p._sex)
		, _age(p._age)
	{}
};
Person GetTempPerson()
{
	Person p("peter", "male", 20);
	return p;
	//此时构造一个p对象，再销毁，再构造一个临时对象，应该调用移动构造，但是
	//peter/male/20都是左值，应该利用move转为右值
}
int main()
{
	Person p(GetTempPerson());
	return 0;
}
#endif
//完美转发
#if 0
void func(int& x)
{
	cout << "左值引用" << endl;
}
void func(int&& x)
{
	cout << "右值引用" << endl;
}
void func(const int& x)
{
	cout << "const 左值引用" << endl;
}
void func(const int&& x)
{
	cout << "const 右值引用" << endl;
}
template <class T>
void PerfectForward(T &&t)
{
	func(t);
}
int main()
{
	PerfectForward(10);//调用右值引用
	int a;
	PerfectForward(a); //应该调用左值引用
	PerfectForward(std::move(a)); //应该调用右值引用

	const int b = 8;
	PerfectForward(b);//应该调用const类型的左值引用 
	PerfectForward(std::move(b)); //应该调用const类型的右值引用
	//但是发现并没有按照我们期待的进行完美转发，C++11中需要用forward实现完美转发
	return 0;
}
#endif
#if 0
void Fun(int &x)//左值引用
{
	cout << "lvalue ref" << endl;
}
void Fun(int &&x)//右值引用
{
	cout << "rvalue ref" << endl;
}
void Fun(const int &x)//const类型的左值引用
{
	cout << "const lvalue ref" << endl;
}
void Fun(const int &&x)//const类型的右值引用
{
	cout << "const rvalue ref" << endl;
}
template<class T>
void PerfectForward(T &&t)
{
	Fun(std::forward<T>(t));
}
int main()
{
	PerfectForward(10);//应该调用右值引用 

	int a;
	PerfectForward(a); //应该调用左值引用
	PerfectForward(std::move(a)); //应该调用右值引用

	const int b = 8;
	PerfectForward(b);//应该调用const类型的左值引用 
	PerfectForward(std::move(b)); //应该调用const类型的右值引用

	return 0;
}
#endif
//线程库
//创建线程的方法：函数指针、函数对象（仿函数）、lambda表达式
#include <thread>
void threadfunc(int a)//函数指针
{
	cout << "thread1" << a << endl;
}
class TF//仿函数
{
public:
	void operator()()
	{
		cout << "thread2" << endl;
	}
};
int main()
{
	thread t1(threadfunc, 10);//函数指针

	TF t;
	thread t2(t);//仿函数

	thread t3([]()
	{
		cout << "thread3" << endl;
	});
	t1.join();
	t2.join();
	t3.join();
	cout << "Main thread end" << endl;
	return 0;
}



