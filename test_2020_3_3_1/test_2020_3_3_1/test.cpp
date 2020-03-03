#define _CRT_SECURE_NO_WARNINGS 1
//�쳣
#include <iostream>
using namespace std;
#if 0
void func1()
{
	FILE* pf = fopen("111.txt", "rb");

	if (pf == nullptr)
	{
		throw 1;//��int���͵Ķ��쳣
	}
	fclose(pf);
}
void func2()
{
	int* p = (int*)malloc(0x7fffffff);
	if (nullptr == p)
	{
		throw '1';//���ַ����͵��쳣
	}
}
int main()
{
	try
	{
		func2();
		func1();
	}
	catch (int err)//һ��catchֻ�ܲ�׽һ�����͵��쳣
	{
		cout << err << endl;
	}
	catch (char err)
	{
		cout << err << endl;
	}
	return 0;
}
#endif
#if 0
//��ѡ�еĴ�������ǵ���������ö�������ƥ�������׳��쳣λ���������һ��
void func1()
{
	FILE* pf = fopen("111.txt", "rb");
	if (nullptr == pf)
	{
		throw 1;
	}
	fclose(pf);
}
void func2()
{
	int* p = (int*)malloc(0x7fffffff);
	if (nullptr == p)
	{
		throw '1';
	}
	try
	{
		func1();
	}
	catch (int err)
	{
		cout << err << endl;
	}
	free(p);
}
int main()
{
	try
	{
		func2();
	}
	catch (int err)
	{
		cout << err << endl;
	}
	catch (char err)
	{
		cout << err << endl;
	}
	return 0;
}
#endif
#if 0
//catch(...)���÷�
void func1()
{
	FILE* pf = fopen("111.txt", "rb");
	if (nullptr == pf)
	{
		throw 1;
	}
	fclose(pf);
}
void func2()
{
	int* p = (int*)malloc(0x7fffffff);
	if (nullptr == p)
	{
		throw '1';
	}
	try
	{
		func1();
	}
	catch (...)
	{
		free(p);
		throw;
	}
}
int main()
{
	try
	{
		func2();
	}
	catch (int err)
	{
		cout << err << endl;
	}
	catch (char err)
	{
		cout << err << endl;
	}
	return 0;
}
#endif
#if 0
void func()throw(int)
{
	throw 1.0;
	//�������쳣�淶,�����������throw������ʾ�ú��������쳣
	//�����쳣�ӿ���������˺������������κ����͵��쳣
}
int main()
{
	func();
	return 0;
}
#endif

