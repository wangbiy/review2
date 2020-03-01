#include <iostream>
using namespace std;
#include <bitset>
namespace Daisy
{
	template < size_t N,class T,
	class HF1,class HF2,class HF3,class HF4,class HF5>
	class BloomFilter
	{
	private:
		bitset<N> _bs;
		size_t _size;
	public:
		BloomFilter()
			:_size(0)
		{}
		//����
		bool insert(const T& data)
		{
			size_t index1 = HF1()(data) % N;
			size_t index2 = HF2()(data) % N;
			size_t index3 = HF3()(data) % N;
			size_t index4 = HF4()(data) % N;
			size_t index5 = HF5()(data) % N;
			_bs.set(index1);
			_bs.set(index2);
			_bs.set(index3);
			_bs.set(index4);
			_bs.set(index5);
			++_size;
			return true;
		}
		//����Ƿ����
		bool Isin(const T& data)
		{
			size_t index = HF1()(data) % N;
			if (_bs.test(index))//������bitλ��0��������ݲ���
				return false;
			index = HF2()(data) % N;
			if (_bs.test(index))//������bitλ��0��������ݲ���
				return false;
			index = HF3()(data) % N;
			if (_bs.test(index))//������bitλ��0��������ݲ���
				return false;
			index = HF4()(data) % N;
			if (_bs.test(index))//������bitλ��0��������ݲ���
				return false;
			index = HF5()(data) % N;
			if (_bs.test(index))//������bitλ��0��������ݲ���
				return false;
			return true;//������
			//��¡�������ڼ�ⲻ���ھ�һ�������ڣ��ڼ������ǿ��ܴ���
			//��Ϊ��ϣ�������ܴ���һ�������
		}
	};
}