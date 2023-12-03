using namespace std;

#pragma once
template <class T>
class Stack
{
	T* data;
	int capacity;
	int topNum;
public:
	Stack(int i = 50);
	bool push(T item);
	T top();
	void pop();
	int count();
	bool isEmpty();
	void clear();
	void print();
	~Stack();
};

template <class T>
void Stack<T>::print()
{
	for (int i = 0; i < topNum; i++)
	{
		if (i != 0)
		{
			cout << ", ";
		}
		cout << data[i];
	}
	cout << endl;
}
template <class T>
Stack<T>::Stack(int i)
{
	data = new T[i];
	capacity = i;
	topNum = 0;
}

template <class T>
Stack<T>::~Stack()
{
	topNum = 0;
	capacity = 0;
	delete[] data;
}

template <class T>
void Stack<T>::clear()
{
	topNum = 0;
}

template <class T>
bool Stack<T>::push(T item)
{
	if (topNum != capacity)
	{
		data[topNum] = item;
		topNum++;
		return true;
	}
	return false;
}

template <class  T>
T  Stack<T>::top()
{
	if (topNum > 0)
	{
		return data[topNum - 1];
	}
	return 0;
}

template <class  T>
void  Stack<T>::pop()
{
	if (topNum > 0)
	{
		topNum--;
	}
}

template <class T>
int Stack<T>::count()
{
	return topNum;
}

template <class T>
bool Stack<T>::isEmpty()
{
	return topNum == 0;
}