#define _CRT_SECURE_NO_WARNINGS 1
//异常
#include <iostream>
using namespace std;
#if 0
void func1()
{
	FILE* pf = fopen("111.txt", "rb");

	if (pf == nullptr)
	{
		throw 1;//抛int类型的额异常
	}
	fclose(pf);
}
void func2()
{
	int* p = (int*)malloc(0x7fffffff);
	if (nullptr == p)
	{
		throw '1';//抛字符类型的异常
	}
}
int main()
{
	try
	{
		func2();
		func1();
	}
	catch (int err)//一个catch只能捕捉一种类型的异常
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
//被选中的处理代码是调用链中与该对象类型匹配且离抛出异常位置最近的那一个
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
//catch(...)的用法
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
	//忽略了异常规范,函数后面加上throw（）表示该函数不抛异常
	//若无异常接口声明，则此函数可以抛掷任何类型的异常
}
int main()
{
	func();
	return 0;
}
#endif

