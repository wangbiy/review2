#include <iostream>
using namespace std;
#if 0
//map��Ӧ��
#include <map>
#include <string>
int main()
{
	map<string, string> m;
	m.insert(pair<string, string>("apple", "ƻ��"));
	m.insert(make_pair("orange", "����"));
	m.insert(make_pair("banana", "�㽶"));
	m.insert(make_pair("watermelon", "����"));
	m.insert(make_pair("apple", "pingguo"));//��ͬkeyֵ���޷�����
	cout << m["apple"] << endl;

	cout << m.size() << endl;
	for (auto e : m)
	{
		cout << e.first << " " << e.second << endl;
	}
	m.erase("watermelon");

	if (m.find("watermelon") != m.end())
	{
		cout << "����" << endl;
	}
	else
		cout << "������" << endl;

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
//multimap��Ӧ��
#include <map>
#include <string>
int main()
{
	multimap<string, string> m;
	m.insert(pair<string, string>("apple", "ƻ��"));
	m.insert(make_pair("orange", "����"));
	m.insert(make_pair("watermelon", "����"));
	m.insert(make_pair("banana", "�㽶"));
	m.insert(make_pair("apple", "pingguo"));//���Բ����ظ���keyֵ
	//cout << m["apple"] << endl;//�޷����ʣ���Ϊ���ظ���keyֵ
	for (auto e : m)
	{
		cout << e.first << "--->" << e.second << endl;
	}
	cout << m.size() << endl;

	m.erase("apple");//�Ὣ����keiyֵΪapple��ɾ����
	multimap<string, string>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "--->" << it->second << endl;
		it++;
	}
	cout << endl;
	if (m.find("apple") != m.end())
		cout << "����" << endl;
	else
		cout << "������" << endl;
	return 0;
}
#endif
//set��Ӧ��
#include <set>
int main()
{
	set<int> s;
	int arr[] = { 4, 4, 4, 3, 3, 3, 2, 2, 5, 5, 6, 6, 6, 6, 8, 0 };
	for (auto e : arr)
		s.insert(e);//ȥ���ظ�����������
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
