#include "map.hpp"
#include "set.hpp"
#include <string>
void TestMap()
{
	Daisy::map<string, string> m;
	m.insert(pair<string, string>("banana", "Ïã½¶"));
	m.insert(make_pair("orange", "éÙ×Ó"));
	m.insert(make_pair("apple", "Æ»¹û"));
	cout << m["orange"] << endl;
	cout << m["apple"] << endl;
	cout << m.size() << endl;
	cout << m["watermelon"] << endl;
	m["watermelon"] = "Î÷¹Ï";
	auto it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "---->" << it->second << endl;
		++it;
	}
	m.clear();
	cout << m.size() << endl;
}
void TestSet()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	Daisy::set<int> s;
	for (auto e : arr)
	{
		s.insert(e);
	}
	cout << s.size() << endl;
	for (auto e : s)
	{
		cout << e << endl;
	}
	cout << endl;
}
int main()
{
	//TestMap();
	TestSet();
	return 0;
}