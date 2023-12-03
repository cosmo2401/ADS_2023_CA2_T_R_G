#pragma once

#include "DList.h"

using namespace std;

template <class T>
class Stack
{
public:
	DList<T>* stackList;

	Stack();
	void Push(T item);
	void Pop();
	T Top();
	int Count();
};

template<class T>
Stack<T>::Stack()
{
	stackList = new DList<T>;
}

template<class T>
void Stack<T>::Push(T item)
{
	stackList->prepend(item);
}

template <class T>
void Stack<T>::Pop() {
	stackList->removeHead();
}

template <class T>
T Stack<T>::Top() {
	return stackList->head->data;
}

template <class T>
int Stack<T>::Count() {
	stackList->count;
}