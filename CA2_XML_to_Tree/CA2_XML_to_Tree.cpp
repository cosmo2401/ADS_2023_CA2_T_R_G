// CA2_XML_to_Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Stack.h"
#include "Tree.h"
#include "TreeIterator.h"

using namespace std;

struct xmlData
{
	string nameType;
	string name;
	int length = 0;
	string type = "";
};

bool valdiateXML(string data) {
	Stack<string>* xmlStack = new Stack<string>;
	int i = 0;
	while (i < data.length()) {
		if (data[i] == '<') { // See if current char is a opening tag
			i++;

			if (data[i] == '/') { // Check the closing tag name and compare if it is valid
				i++;

				string tagName;

				for (; data[i] != '>'; i++) tagName += data[i];

				if (xmlStack->isEmpty() || xmlStack->top() != tagName) return false;

				xmlStack->pop();
			}
			else { // Check the opening tag name and push it on the stack
				string tagName;

				for (; data[i] != '>'; i++) tagName += data[i];

				xmlStack->push(tagName);
			}
		}
		else i++;
	}

	// If we reach this point everything worked so far now we check if the stack is empty
	// If stack is empty that means that there were not enough closing tags
	if (xmlStack->isEmpty()) return true;
	return false;
}

Tree<xmlData>* createTree(string data) {
	xmlData root;

	int i = 4;

	for (; data[i] != '<'; i++) root.name += data[i];

	root.nameType = "dir";

	Tree<xmlData>* tree = new Tree<xmlData>(root);
	TreeIterator<xmlData> treeIter(tree);

	while (i < data.length()) {
		if (data[i] == '<') { // See if current char is a opening tag
			i++;

			if (data[i] != '/') { // Check the closing tag name and compare if it is valid
				string tagName;

				for (; data[i] != '>'; i++) tagName += data[i];

				if (tagName == "file") { // Check if current tag is a file
					xmlData newXML;
					newXML.nameType = tagName;

					for (int j = 0; j < 3; j++) {
						while (data[i] != '<') i++;
						i++;

						tagName = "";
						string content = "";

						for (; data[i] != '>'; i++) tagName += data[i];
						i++;

						if (tagName == "name") {
							for (; data[i] != '<'; i++) content += data[i];
							newXML.name = content;
						}
						else if (tagName == "length") {
							for (; data[i] != '<'; i++) content += data[i];
							newXML.length = stoi(content);
						}
						else if (tagName == "type") {
							for (; data[i] != '<'; i++) content += data[i];
							newXML.type = content;
						}
					}
					treeIter.appendChild(newXML);
				}
				else if (tagName == "dir") { // Check if current tag is a dir
					xmlData newXML;
					newXML.nameType = tagName;

					while (data[i] != '<') i++;
					i++;

					tagName = "";
					string content = "";

					for (; data[i] != '>'; i++) tagName += data[i];
					i++;

					if (tagName == "name") {
						for (; data[i] != '<'; i++) content += data[i];
						newXML.name = content;
					}

					treeIter.appendChild(newXML);
					treeIter.down();
				}
			}
		}
		else i++;
	}
	return tree;
}

void nrOfItems() {
}

/*
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
*/

template <class T>
void displayTree(TreeIterator<T> iter, string indent)
{
	cout << indent << iter.item().name;
	bool hasB = false;

	if (iter.childValid()) {
		cout << "{";
		hasB = true;
	}

	cout << endl;

	while (iter.childValid()) {
		TreeIterator<T> iter2(iter);
		iter2.down();
		displayTree(iter2, indent + "\t");
		iter.childForth();
	}
	if (hasB) {
		cout << indent << "}" << endl;
	}
}

int main()
{
	// Step 1 Read in a XML file
	string xml = R"(
		<dir>
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

	string x = "<dir><name>test</name></dir>";

	// Step 2 validate the XML File
	if (valdiateXML(xml)) {
		cout << "This is a valid xml" << endl;
	}
	else {
		cout << "String is invalid!" << endl;
	}

	// Step 3 Put the XML file structure into a tree

	Tree<xmlData>* xmlTree = createTree(xml);
	TreeIterator<xmlData> treeIter(xmlTree);

	// Step 4 Determine the number of files and folders in a given dir

	// Step 5 Determine the memory used of a given dir

	// Step 6 Remove empty folder

	// Step 7 Find a particular folder given a filename and generate a path

	// Step 8 Display a given dir

	displayTree(treeIter, "");

	//std::cout << xml;
}