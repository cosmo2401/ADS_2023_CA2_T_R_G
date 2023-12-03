// CA2_XML_to_Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Stack.h"
#include "Tree.h"
#include "TreeIterator.h"

using namespace std;

bool valdiateXML(string data) {
	Stack<string>* xmlStack = new Stack<string>;

	int i = 0;

	while (i < data.length()) {

		if (data[i] == '<') {
			i++;

			if (data[i] == '/') { //Check the closing tag name and compare if it is valid
				i++;

				string tagName;

				for (; data[i] != '>'; i++) tagName += data[i];

				if (xmlStack->isEmpty() || xmlStack->top() != tagName) {
					cout << "-" << xmlStack->top()<< "-" << endl;
					cout << "-" << tagName << "-" <<endl;
					cout << xmlStack->count()  << endl;
					cout << "tags do not match" << endl;
					return false;
				} 
				
				xmlStack->pop();
			}
			else { //´Check the opening tag name and push it on the stack
				string tagName;

				for(; data[i] != '>';i++) tagName += data[i];

				xmlStack->push(tagName);
			}
		}

		i++;
	}

	// If we reach this point everything worked so far now we check if the stack is empty
	// If stack is empty that means that there were not enough closing tags
	if (xmlStack->isEmpty()) return true;
	return false;
}

void createTree(string data) {
}

void nrOfItems() {
}
/*
template <class T>
void printDFS(TreeIterator<T> iter) //Pre order traversel
{
	DListIterator<Tree<T>*> iter = iter;

	cout << iter.item() << " ";
	while (iter.childValid()) {
		TreeIterator<T> iter2(iter);
		iter2.down();
		printDFS(iter2);
		iter.childForth();
	}
}

template <class T>
void calcMemoryForFolder(TreeIterator<T> iter)
{
	queue<Tree<T>*> q;
	q.push(&tree);
	while (!q.empty()) {
		cout << q.front()->getData() << " ";
		DListIterator<Tree<T>*> iter = q.front()->children->getIterator();
		while (iter.isValid()) {
			q.push(iter.item());
			iter.advance();
		}
		q.pop();
	}
}
*/

int main()
{
	string xml = R"(<dir>
        <name> ADS_Single_LinkedList_Exercises</name>
        <dir>
        <name>.git</name>
        <file>
        <name>config</name>
        <length>353 b</length>
        <type>config</type>
        </file>
        <file>
        <name>description</name>
        <length>73 b</length>
        <type>description</type>
        </file>
        <file>
        <name>HEAD</name>
        <length>23 b</length>
        <type>HEAD</type>
        </file>
        </dir>
        <dir>
        <name>.vs</name>
        <dir>
        <name>ADS_Single_LinkedList_Exercises</name>
        <dir>
        <name>v17</name>
        </dir>
        </dir>
        </dir>
        <dir>
        <name>Debug</name>
        <file>
        <name>SinglyLinkedList.pdb</name>
        <length>978944 b</length>
        <type>pdb</type>
        </file>
        <file>
        <name>TestSinglyLinkedList.exp</name>
        <length>41528 b</length>
        <type>exp</type>
        </file>
        <file>
        <name>TestSinglyLinkedList.pdb</name>
        <length>1945600 b</length>
        <type>pdb</type>
        </file>
        </dir>
        </dir>)";

	Stack<string>* newStack = new Stack<string>;

	newStack->push("testing");

	cout << newStack->top() << endl;
	cout << "Length of the xml string " << xml.length() << endl;

	if (newStack->top() == "test") {
		cout << " its the same";
	}

	// Testing purposes
	if (valdiateXML(xml)) {
		cout << "This is a valid xml" << endl;
	}

	//std::cout << xml;
}