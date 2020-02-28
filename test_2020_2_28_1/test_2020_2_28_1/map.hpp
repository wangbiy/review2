#pragma once
#include "RBTree.hpp"
namespace Daisy
{
	template <class K, class V>//map的结构是键值对,map中的键值对就相当于红黑树的Value
	class map
	{
		typedef pair<K, V> DataType;
		struct KeyofValue//仿函数,利用键值对得到key
		{
			const K& operator()(const DataType& val)//val是键值对
			{
				return val.first;//获得键值对中的key
			}
		};
		typedef RBTree<DataType, K, KeyofValue> RBT;

	public:
		typename typedef RBT::iterator iterator;//由于编译器可能会把RBT::iterator当做类中的静态成员变量，所以要使用typename
		map()
			:_t()
		{}
		iterator begin()
		{
			return _t.Begin();//返回红黑树中的起始位置
		}
		iterator end()
		{
			return _t.End();
		}
		//容量相关
		size_t size()const
		{
			return _t.Size();
		}
		bool empty()const
		{
			return _t.Empty();
		}
		//access
		V& operator[](const K& key)
		{
			return (*(_t.Insert(pair<K, V>(key, V())).first)).second;
			//红黑树中插入的结点是pair<iterator,bool>，先得到这个键值对的
			//firstiterator，然后解引用得到iterator指向的键值对，然后取这个键值对的
			//second就是value
		}
		//modify
		pair<iterator, bool> insert(const DataType& val)//val是一个键值对
		{
			return _t.Insert(val);
		}
		void swap(map<K, V>& m)
		{
			_t.Swap(m._t);
		}
		void clear()
		{
			_t.Clear();
		}
		iterator find(const K& key)
		{
			return _t.Find(key);
		}
	private:
		RBT _t;
	};
}