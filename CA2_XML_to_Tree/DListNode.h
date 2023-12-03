#pragma once

template <class T>
class DListNode
{
public:
	T data;
	/*
	string tName;
	int size;
	string type;
	*/

	DListNode<T>* next;
	DListNode<T>* previous;


	DListNode(T item);
	//DListNode(T item,string tn,int s, string t);
	DListNode(DListNode<T>& item);
	void insertBefore(T item);
	void insertAfter(T item);

	~DListNode()
	{
		//next = nullptr;
		//previous = nullptr;
	}
};


template <class T>
DListNode<T>::DListNode(DListNode<T>& node)
{
	this->data = new DListNode(node->data);
}

template <class T>
DListNode<T>::DListNode(T item)
{
	data = item;
	/*
	typeName = "none";
	size = 0;
	type = "none";
	*/
	next = previous = nullptr;
}


/*
template <class T>
DListNode<T>::DListNode(T item, string tn, int s, string t)
{
	data = item;
	typeName = tn;
	size = s;
	type = t;
	next = previous = nullptr;
}
*/

template <class T>
void DListNode<T>::insertAfter(T item)
{
	DListNode<T>* temp = new DListNode<T>(item);

	temp->next = this->next;
	temp->previous = this;

	if (this->next != nullptr) {
		this->next->previous = temp;
	}
	this->next = temp;

}

template <class T>
void DListNode<T>::insertBefore(T item)
{
	DListNode<T>* temp = new DListNode<T>(item);
	temp->next = this;
	temp->previous = this->previous;

	if (this->previous != nullptr) {
		this->previous->next = temp;
	}
	this->previous = temp;
}
