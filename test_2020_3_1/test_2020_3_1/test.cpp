#include <iostream>
using namespace std;
#include <vector>
#include <assert.h>
namespace Daisy
{
	template <size_t N>//bitλ�ĸ���
	class bitset
	{
	private:
		vector<unsigned char> _bs;
	public:
		bitset()
		{
			_bs.resize((N >> 3) + 1);//�����ֽ���
		}
		//��num��bitλ��1
		bitset<N>& set(size_t num)
		{
			assert(num < N);
			size_t index = num >> 3;//�������ĸ��ֽ�
			size_t pos = num % 8;//�������ĸ�bitλ
			_bs[index] |= (1 << pos);//�����bitλ��1
			return *this;
		}
		//��num��bitλ��0
		bitset<N>& reset(size_t num)
		{
			assert(num < N);
			size_t index = num >> 3;
			size_t pos = num % 8;
			_bs[index] &= ~(1 << pos);
			return *this;
		}
		//���num�Ƿ����
		bool test(size_t num)const
		{
			assert(num < N);
			size_t index = num >> 3;
			size_t pos = num % 8;
			return 0 != (_bs[index] & (1 << pos));
		}
		size_t size()const
		{
			return N;
		}
		size_t count()const//�ܹ��ж��ٸ�bitλ��1
		{
			int bitCnttable[256] = {
				0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2,
				3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3,
				3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3,
				4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4,
				3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5,
				6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4,
				4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
				6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5,
				3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3,
				4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6,
				6, 7, 6, 7, 7, 8 };//��Ӧ��������0,1,2,3,4,5�Ķ�Ӧbitλ�м���,����0��0��bitλ��1��1������λ��2��1������λ
			size_t szcount = 0;
			for (auto e : _bs)
			{
				szcount += bitCnttable[e];
			}
			return szcount;
		}
	};
}
void Testbit()
{
	Daisy::bitset<100> bs;//һ��100��bitλ
	int array[] = { 1, 3, 7, 4, 12, 16, 19, 13, 22, 18 };
	for (auto e : array)
		bs.set(e);//������ӳ�䵽λͼ��
	cout << bs.count() << endl;//�����ж��ٸ�����
	cout << bs.size() << endl;//bitλ�ܸ���
	if (bs.test(13))//�������Ԫ���ڲ���λͼ��
		cout << "13 is in bitset" << endl;
	else
		cout << "13 is not in bitset" << endl;
	bs.reset(13);//�����bitλ��0
	if (bs.test(13))
		cout << "13 is in bitset" << endl;
	else
		cout << "13 is not in bitset" << endl;
}
int main()
{
	Testbit();
	return 0;
}