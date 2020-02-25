#include <iostream>
using namespace std;
#if 0
//map的应用
#include <map>
#include <string>
int main()
{
	map<string, string> m;
	m.insert(pair<string, string>("apple", "苹果"));
	m.insert(make_pair("orange", "橘子"));
	m.insert(make_pair("banana", "香蕉"));
	m.insert(make_pair("watermelon", "西瓜"));
	m.insert(make_pair("apple", "pingguo"));//相同key值的无法插入
	cout << m["apple"] << endl;

	cout << m.size() << endl;
	for (auto e : m)
	{
		cout << e.first << " " << e.second << endl;
	}
	m.erase("watermelon");

	if (m.find("watermelon") != m.end())
	{
		cout << "存在" << endl;
	}
	else
		cout << "不存在" << endl;

	map<string, string>::iterator it1 = m.begin();
	while (it1 != m.end())
	{
		cout << it1->first << "--->" << it1->second << endl;
		++it1;
	}

	auto it2 = m.rbegin();
	while (it2 != m.rend())
	{
		cout << it2->first << "--->" << it2->second << endl;
		it2++;
	}
	cout << endl;
	return 0;
}
#endif
#if 0
//multimap的应用
#include <map>
#include <string>
int main()
{
	multimap<string, string> m;
	m.insert(pair<string, string>("apple", "苹果"));
	m.insert(make_pair("orange", "橘子"));
	m.insert(make_pair("watermelon", "西瓜"));
	m.insert(make_pair("banana", "香蕉"));
	m.insert(make_pair("apple", "pingguo"));//可以插入重复的key值
	//cout << m["apple"] << endl;//无法访问，因为有重复的key值
	for (auto e : m)
	{
		cout << e.first << "--->" << e.second << endl;
	}
	cout << m.size() << endl;

	m.erase("apple");//会将所有keiy值为apple的删除掉
	multimap<string, string>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "--->" << it->second << endl;
		it++;
	}
	cout << endl;
	if (m.find("apple") != m.end())
		cout << "存在" << endl;
	else
		cout << "不存在" << endl;
	return 0;
}
#endif
//set的应用
#include <set>
int main()
{
	set<int> s;
	int arr[] = { 4, 4, 4, 3, 3, 3, 2, 2, 5, 5, 6, 6, 6, 6, 8, 0 };
	for (auto e : arr)
		s.insert(e);//去除重复，并且排序
	set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
	cout << s.size() << endl;
	return 0;
}
