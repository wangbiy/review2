#include "RBTree.hpp"
namespace Daisy
{
	template <class K>//set只有key,相当于红黑树中的value
	class set
	{
		typedef K ValueType;
		struct KeyOfValue
		{
			const K& operator()(const ValueType& val)//将value当成key即可
			{
				return val;
			}
		};
		typedef RBTree<ValueType, K, KeyOfValue> RBT;
	private:
		RBT _t;
	public:
		typename typedef RBT::iterator iterator;
		set()
			:_t()
		{}
		iterator begin()
		{
			return _t.Begin();
		}

		iterator end()
		{
			return _t.End();
		}

		bool empty()const
		{
			return _t.Empty();
		}
		size_t size()const
		{
			return _t.Size();
		}
		pair<iterator, bool> insert(const ValueType& val)
		{
			return _t.Insert(val);
		}
		void clear()
		{
			_t.Clear();
		}
		iterator find(const K& key)
		{
			return _t.Find(key);
		}
	};
}