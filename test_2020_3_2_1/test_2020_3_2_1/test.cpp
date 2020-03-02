#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
//C++11
#if 0
//�б��ʼ��
//���������б��ʼ��
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
		//�ṩ����initializer_list�����Ĺ��캯��
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
	Daisy::vector<int> v2{ 1, 2, 3, 4, 5 };//���Խ����б��ʼ��
	return 0;
}
#endif
//���������Ƶ�
#if 0
#include <map>
#include <string>
int main()
{
	short a = 32670;
	short b = 32670;
	short c = a + b;//�޷��õ���Ҫ�Ľ��
	map<string, string> m{ { "apple", "ƻ��" }, { "banana", "�㽶" } };//���ֵ�����̫������
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
//�����޷��Ƶ���c�����ͣ����ҵ���������̫���������ʹ��auto�ؼ���
#include <map>
#include <string>
int main()
{
	auto a = 32670;
	auto b = 32670;
	auto c = a + b;
	map<string, string> m{ { "apple", "ƻ��" }, { "banana", "�㽶" } };
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
//����auto����Щ������޷�ʹ�ã�����
template <class T1,class T2>
auto Add(const T1& left, const T2& right)//��֪���÷���T1����T2
{
	return left + right;
}
int main()
{
	return 0;
}
#endif
//��ʱ�������޷��Ƶ���auto�����ͣ������Ҫdecltype�ؼ���
#if 0
//1.���ݱ��ʽ������Ϊ������ʵ������
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
//����ֵ����׷��
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
//Ĭ�Ϻ�������
#if 0
//��ʽȱʡ����������=default������
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
//ɾ��Ĭ�Ϻ���
class Date
{
public:
	Date() = delete;
};
int main()
{
	Date d;//��ʾ����������ɾ���ĺ���
	return 0;
}
#endif
//lambde���ʽ
#if 0
//�������÷º���ʵ���Զ������͵�����
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
	Goods gd[] = { { "ƻ��", 3.1 }, { "�㽶", 2.5 }, { "����", 4.0 } };
	sort(gd, gd + sizeof(gd) / sizeof(gd[0]),com());
	return 0;
}
#endif
#if 0
//���ú���ָ��ʵ������
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
	Goods gd[] = { { "ƻ��", 3.1 }, { "�㽶", 2.5 }, { "����", 4.0 } };
	sort(gd, gd + sizeof(gd) / sizeof(gd[0]), Compare);
	return 0;
}
#endif
//lambda���ʽ
#if 0
#include <algorithm>
struct Goods
{
	string _name;
	double _price;
};
int main()
{
	Goods gd[] = { { "ƻ��", 3.1 }, { "�㽶", 2.5 }, { "����", 4.0 } };
	sort(gd, gd + sizeof(gd) / sizeof(gd[0]),
		[](const Goods& g1, const Goods& g2)->bool
	{
		return g1._price <= g2._price;
	});
	return 0;
}
#endif
//�����б�˵��
#if 0
int main()
{
	int a = 10;
	int b = 20;
	int c = 0;
	cout << &c << endl;
	auto add = [c](const int left, const int right)mutable
	{
		cout << &c << endl;//ǰ���ַ��ͬ
		c=left + right;
	};
	add(1, 2);//cֵû�з����仯����Ϊ��ֵ����
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
		cout << &c << endl;//ǰ���ַ��ͬ
		c = left + right;
	};
	add(1, 2);//cֵ�����仯����Ϊ��ַ����
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
		cout << &c << endl;//a b cǰ���ַ��ͬ����Ϊ�ǰ���ֵ���ݵķ�ʽ�������������б���
		c = left + right;
	};
	add(1, 2);//cû�з����仯
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
		cout << &c << endl;//a b cǰ���ַ��ͬ����Ϊ�ǰ������ô��ݵķ�ʽ�������������б���
		c = left + right;
	};
	add(1, 2);//c���3
	return 0;
}
#endif
#if 0
//lambda���ʽ�ײ�ʵ��ԭ��
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
	r1(1000, 3);//�º�����ʽ����
	//lambda���ʽ
	auto r2 = [=](double money, int year)->double
	{
		return money*rate*year;
	};
	r2(1000, 2);
	return 0;
}
//����lambda���ʽ�ײ��ǰ��պ�������ķ�ʽʵ�ֵģ�
//lambda���ʽ���Զ�����һ���࣬�����б��൱����ĳ�Ա����
//�����б�����ֵ���͡�����ʵ�����൱��operator()
#endif
//�ƶ�����
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
		string(const string& s)//��������
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
				_str = ptr;//ֱ�Ӹı�ָ��ָ����ʱ�ռ伴��
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
	//s3�����������s1��s2��ӵ�����������+��������أ����ܸı����Ҳ�����
	//������Ƿ��صĲ��ǵ�ǰ����Ҳ���ܷ��ز���s������һ�����������ֵ����ֵ����ʽ���أ�
	//���Ǵ�������ret���������ǹ����ret��ջ�ϣ���������ָ��ָ������ݡ�hello world���ڶ��ϣ�
	//������ֵ����ʽ���أ��ڷ���ʱҲ������һ����ʱ����Ҳ������ָ�룬ָ������ݡ�hello world���ڶ��ϣ�
	//Ҳ����s3=ret�����ǿ��Է���ret����ʱ�����Լ�s3��ָ����ָ���������һ���ģ�������һ����Դ�ͷ�����������⣬
	//Ч�ʲ��߲����˷ѿռ䣬ret�������ʱ������һ������ֵ����ʱ�����൱��s3��һ������ֵ��������ǿ��Խ��һ���ռ��ͷ���������һ�������⣬
	//������Դת�ƣ�Ҳ�����ƶ����壬��Ч����Ч�ʱȽϵ��˷���Դ�����⣬�����Ƚ�ret�е�ָ��ת�Ƹ���ʱ�����ٽ���ʱ�����ָ��ת�Ƹ�s3��
}
int main()
{
	Teststring();
	return 0;
}
#endif
#if 0
//��˿��Խ������Ϊ
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
		//�ƶ�����
		string(string&& s)//����s�е����ݻᷢ���ı䣬�������&&
			:_str(s._str)//��s�е���Դת�Ƹ�_str
		{
			s._str = nullptr;//ת�����֮��Ϳ����ÿ�
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
		//�ƶ���ֵ
		string& operator=(string&& s)
		{
			if (this != &s)
			{
				delete[]_str;
				_str = s._str;//����Դת�Ƹ�_str
				s._str = nullptr;//��Դת�����֮���ÿ�
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
//�ƶ�����move��ʹ��
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
	//�ƶ�����
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
	//��ʱ����һ��p���������٣��ٹ���һ����ʱ����Ӧ�õ����ƶ����죬����
	//peter/male/20������ֵ��Ӧ������moveתΪ��ֵ
}
int main()
{
	Person p(GetTempPerson());
	return 0;
}
#endif
//����ת��
#if 0
void func(int& x)
{
	cout << "��ֵ����" << endl;
}
void func(int&& x)
{
	cout << "��ֵ����" << endl;
}
void func(const int& x)
{
	cout << "const ��ֵ����" << endl;
}
void func(const int&& x)
{
	cout << "const ��ֵ����" << endl;
}
template <class T>
void PerfectForward(T &&t)
{
	func(t);
}
int main()
{
	PerfectForward(10);//������ֵ����
	int a;
	PerfectForward(a); //Ӧ�õ�����ֵ����
	PerfectForward(std::move(a)); //Ӧ�õ�����ֵ����

	const int b = 8;
	PerfectForward(b);//Ӧ�õ���const���͵���ֵ���� 
	PerfectForward(std::move(b)); //Ӧ�õ���const���͵���ֵ����
	//���Ƿ��ֲ�û�а��������ڴ��Ľ�������ת����C++11����Ҫ��forwardʵ������ת��
	return 0;
}
#endif
#if 0
void Fun(int &x)//��ֵ����
{
	cout << "lvalue ref" << endl;
}
void Fun(int &&x)//��ֵ����
{
	cout << "rvalue ref" << endl;
}
void Fun(const int &x)//const���͵���ֵ����
{
	cout << "const lvalue ref" << endl;
}
void Fun(const int &&x)//const���͵���ֵ����
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
	PerfectForward(10);//Ӧ�õ�����ֵ���� 

	int a;
	PerfectForward(a); //Ӧ�õ�����ֵ����
	PerfectForward(std::move(a)); //Ӧ�õ�����ֵ����

	const int b = 8;
	PerfectForward(b);//Ӧ�õ���const���͵���ֵ���� 
	PerfectForward(std::move(b)); //Ӧ�õ���const���͵���ֵ����

	return 0;
}
#endif
//�߳̿�
//�����̵߳ķ���������ָ�롢�������󣨷º�������lambda���ʽ
#include <thread>
void threadfunc(int a)//����ָ��
{
	cout << "thread1" << a << endl;
}
class TF//�º���
{
public:
	void operator()()
	{
		cout << "thread2" << endl;
	}
};
int main()
{
	thread t1(threadfunc, 10);//����ָ��

	TF t;
	thread t2(t);//�º���

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



