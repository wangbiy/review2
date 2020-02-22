#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <assert.h>
namespace Daisy
{
	class string
	{
	public:
		//���캯��
		string(const char* str = "")
		{
			if (str == nullptr)
				str = "";
			_str = new char[strlen(str) + 1];
			_capacity = strlen(str);
			_size = _capacity;
			strcpy(_str, str);
		}
		//���캯��
		string(size_t n,char c)
			:_str(new char[n+1])
			, _capacity(n)
			, _size(n)
		{
			memset(_str, c, _size);
			_str[_size] = '\0';
		}
		//���캯��
		string(const char* ptr, size_t n)
		{
			size_t len = strlen(ptr);
			_size = len > n ? n : len;
			//�����������ݳ��ȱ�Ҫ��ĳ��ȳ����Ͱ���Ҫ��ĳ��ȣ����򣬰��մ�������ݵĳ���
			_capacity = _size;
			_str = new char[_capacity + 1];//�����������һλ�Ŀռ�������'\0'
			for (size_t i = 0; i < _size; ++i)
			{
				_str[i] = ptr[i];
			}
			_str[_size] = '\0';
		}
		//�������캯��,���
		string(const string& s)
			:_str(new char[strlen(s._str) + 1])
		{
			strcpy(_str, s._str);
			_size = s._size;
			_capacity = s._capacity;
		}
		//��ֵ���������
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				//����һ����ʱ�ռ䣬����ֵ��������ݿ�����ȥ�����ٵ�ǰ��������ָ����ʱ�ռ伴��
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
		//��ɾ���
		void Reserve(size_t newcapacity)//ʵ������
		{
			if (newcapacity >capacity())
			{
				char* ptr = new char[newcapacity + 1];//�����¿ռ�
				strcpy(ptr, _str);//�����ݿ�����ȥ
				delete[]_str;//���پɿռ�
				_str = ptr;//ָ���¿ռ�
				_capacity = newcapacity;
			}
		}
		//β��һ���ַ�
		void push_back(char c)
		{
			if (_size == _capacity)
			{
				Reserve(_capacity * 2);//����
			}
			_str[_size++] = c;
			_str[_size] = '\0';
		}
		//β��һ���ַ���
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
		//ͷ��һ���ַ�
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
		//ͷ��һ���ַ���
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

		//��ָ��λ�ò����ַ�
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
		//��ָ��λ�ò����ַ���
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
		//βɾһ���ַ�
		void pop_back()
		{
			if (_size == 0)
				return;
			_size--;
			_str[_size] = '\0';
		}
		//ͷɾһ���ַ�
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
		//ָ��λ��֮��ɾ��ָ�����ȵ��ַ�
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
		//[]�����������
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
		//����һ���ַ�
		size_t find(char c)
		{
			for (size_t i = 0; i < _size; ++i)
			{
				if (c == _str[i])
					return i;
			}
			return -1;
		}
		//����һ���ַ���
		size_t find(const char* str)
		{
			size_t i = 0;//ָ��_str
			while (_str[i] != '\0')
			{
				if (_str[i] == *str)//���������߿�������ַ��Ƿ�����Ҫ�ҵ�str��ͬ
				{
					size_t j = i;
					size_t k = 0;//ָ��str
					while (1)
					{
						if (str[k] == '\0')//˵����������str,��_str��iָ�ľ����ҵ����ַ������±�
						{
							return i;
						}
						if (_str[j] != str[k])//˵��j��ǰ��ָ���ַ�������Ҫ�ҵ��ַ���str
							break;
						//����
						j++;
						k++;
					}

				}
				//���������һ��
				++i;
			}
			return -1;
		}
		//+���������,���÷��ص�ǰ���󣬵�ǰ���󲻱�
		string operator+(char ch)//��һ���ַ�
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
		//+=��������أ�Ҫ���ص�ǰ���󣬵�ǰ�������仯
		string& operator+=(char ch)
		{
			insert(_size, ch);
			return *this;
		}
		string& operator+=(const string& str)
		{
			size_t leftlen = _capacity - _size;//ʣ����ٿռ�
			size_t str_size = str.size();//��ӵ��ַ�����Ҫ���ٿռ�
			if (str_size > leftlen)//˵����Ҫ����
			{
				Reserve(_size + str_size);
			}
			strcpy(_str+_size, str._str);//��˼��ƴ�ӵ�_str����
			_size += str_size;
			return *this;
		}
		//>���������
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
		//==���������
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
		//>=���������
		bool operator>=(const string& s)
		{
			if (*this > s || *this == s)
			{
				return true;
			}
			return false;
		}
		//<���������
		bool operator<(const string& s)
		{
			if (!(*this >= s))
				return true;
			return false;
		}
		//<=���������
		bool operator<=(const string& s)
		{
			if (*this < s || *this == s)
				return true;
			return false;
		}
		//!=���������
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