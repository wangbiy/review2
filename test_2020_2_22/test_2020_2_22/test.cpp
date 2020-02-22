#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#if 0
//ǳ��������
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
	//ǳ��������
	return 0;
}
#endif
#if 0
//���ǳ�������ⷽ��1
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
		//�����һ�ִ�ͳд��������ʵʵ���ռ䣬������Դ
		string(const string& s)
			:_str(new char[strlen(s._str) + 1])
		{
			strcpy(_str, s._str);
		}
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				//�ȿ�����ʱ�ռ䣬Ȼ�����ݿ�����ȥ���ͷŵ�ǰ����Ŀռ䣬Ȼ������ָ����ʱ�ռ伴��
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
//����ִ�д�������ñ��˿�����֮���ٻ�����
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
			string pTemp(s._str);//�������������Դ�������쵽��ʱ������
			swap(_str, pTemp._str);
		}
		string& operator=(const string& s)
		{
			string pTemp(s);//����������ʱ����
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
//���ǳ�����ĵڶ��ַ���������+дʱ����
//���ʹ����ͨ�ĳ�Ա��������Ϊ����������������ͬһ���ڴ�ռ䣬
//���ͷ���Դʱ��ֻ��һ������ļ��������ı䣬��һ�������ܷ����ı䣬
//��˲���ʹ�����ַ�ʽʹ�ü������ֿ��ǵ�ʹ��static���εĳ�Ա����
//������������еģ�����һ�����µ��ù��캯����������ֱ�ӱ����1
//������⣬�������Ҫʹ��ָ��
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
		string(const string& s)//�������캯��
			:_str(s._str)
			, _pcount(s._pcount)
		{
			++(*_pcount);
		}
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				Release();//���ͷŵ���ǰ��������ݺͼ���
				//���и�ֵ
				_str = s._str;
				_pcount = s._pcount;
				//����������ͬһ���ڴ�ռ䣬�������+1
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