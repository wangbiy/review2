#include <iostream>
using namespace std;
#if 0
class Date
{
private:
	int _year;
	int _month;
	int _day;
public:
	Date(int year, int month, int day)
		:_year(year)
		, _month(month)
		, _day(day)
	{}
	bool operator<(const Date& d)const
	{
		if (_year < d._year || _year == d._year&& _month < d._month
			|| _year == d._year && _month == d._month &&_day < d._day)
			return true;
		return false;
	}
};
#include <queue>
int main()
{
	Date d1(2020, 2, 1);
	Date d2(2020, 2, 24);
	Date d3(2020, 2, 13);
	priority_queue<Date> p;//Ĭ���Ǵ��
	p.push(d1);
	p.push(d2);
	p.push(d3);
	return 0;
}
#endif
#if 0
//����������յ�ַ���бȽϣ����޷�ʹ�����ݱȽϣ��͵ò���������Ҫ�Ľ��������
class Date
{
private:
	int _year;
	int _month;
	int _day;
public:
	Date(int year, int month, int day)
		:_year(year)
		, _month(month)
		, _day(day)
	{}
	bool operator<(const Date& d)const
	{
		if (_year < d._year || _year == d._year&& _month < d._month
			|| _year == d._year && _month == d._month &&_day < d._day)
			return true;
		return false;
	}
};
#include <queue>
int main()
{
	Date d1(2020, 2, 1);
	Date d2(2020, 2, 24);
	Date d3(2020, 2, 13);
	priority_queue<Date*> p;//Ĭ���Ǵ��
	p.push(&d1);
	p.push(&d2);
	p.push(&d3);
	return 0;
}
#endif
//������ǿ��԰��պ���ָ����ʵ��
#if 0
class Date
{
private:
	int _year;
	int _month;
	int _day;
public:
	friend bool less(Date* pLeft, Date* pRight);//������Ԫ
	Date(int year, int month, int day)
		:_year(year)
		, _month(month)
		, _day(day)
	{}
};
bool less(Date* pLeft, Date* pRight)
{
	if (pLeft->_day < pRight->_day)
		return true;
	return false;
}
typedef bool(*Compare)(Date* pLeft, Date* pRight);//����ָ��
#include <queue>
int main()
{
	Date d1(2020, 2, 15);
	Date d2(2020, 2, 17);
	Date d3(2020, 2, 1);
	priority_queue<Date*, vector<Date*>, Compare> p(less);
	p.push(&d1);
	p.push(&d2);
	p.push(&d3);
	return 0;
}
#endif
//����ʹ�ú���ָ����鷳������������ʹ�÷º���
class Date
{
	friend class Less;//��Ԫ��
public:
	Date(int year = 1990, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{}
private:
	int _year;
	int _month;
	int _day;
};
class Less
{
public:
	bool operator()(Date* pLeft, Date* pRight)//����less�Ĺ��򣬽��������ʷ�����
	{
		if (pLeft->_day < pRight->_day)
			return true;
		return false;
	}
};
#include <queue>
int main()
{
	Date d1(2020, 2, 10);
	Date d2(2020, 2, 14);
	Date d3(2020, 2, 7);
	Less min;
	min(&d1, &d2);
	priority_queue<Date*, vector<Date*>, Less> q;//�����
	q.push(&d1);
	q.push(&d2);
	q.push(&d3);
	return 0;
}