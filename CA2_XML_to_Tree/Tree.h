#pragma once
#include "DList.h"

template<class T>
class Tree
{
public:
	T data;
	Tree<T>* parent;
	DList<Tree<T>*>* children;
	Tree(T item);
	int count();
	T getData();
};
template <class T>
T Tree<T>::getData()
{
	return data;
}
template <class T>
Tree<T>::Tree(T item)
{
	data = item;
	parent = nullptr;
	children = new DList<Tree<T>*>();
}

template <class T>
int Tree<T>::count()
{
	int c = 1;
	DListIterator<Tree<T>*> iter = children->getIterator();
	while (iter.isValid()) {
		c += iter.item()->count();
		iter.advance();
	}
	return c;
}
