#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>

#include "Stack.h"
#include "Tree.h"
#include "TreeIterator.h"

struct xmlData
{
	string nameType;
	string name;
	int length = 0;
	string type = "";
};

string readFile(string path) {
	ifstream file(path);

	if (!file.is_open()) return "";

	stringstream stream;
	stream << file.rdbuf();

	file.close();

	return stream.str();
}

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

	int i = data.find("<dir>");
	if (i != 0) return nullptr;
	i = data.find("<name>");
	i += 6;

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
							int temp = stoi(content);
							newXML.length = temp;
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
			else if (data[i + 1] == 'd' && data[i + 2] == 'i' && data[i + 3] == 'r') {
				treeIter.up();
			}
		}
		else i++;
	}
	return tree;
}

template <class T>
int countFolders(TreeIterator<T> iter)
{
	int c = 0;
	if (iter.item().nameType == "dir") c++;

	while (iter.childValid()) {
		TreeIterator<T> iter2(iter);
		iter2.down();
		c += countFolders(iter2);
		iter.childForth();
	}
	return c;
}
template <class T>
int countFiles(TreeIterator<T> iter)
{
	int c = 0;
	if (iter.item().nameType == "file") c++;

	while (iter.childValid()) {
		TreeIterator<T> iter2(iter);
		iter2.down();
		c += countFiles(iter2);
		iter.childForth();
	}
	return c;
}

int calcMemoryUsed(Tree<xmlData> tree)
{
	queue<Tree<xmlData>> queue;
	queue.push(tree);
	int size = 0;
	while (!queue.empty())
	{
		DListIterator<Tree<xmlData>*> iter = queue.front().children->getIterator();
		while (iter.isValid())
		{
			queue.push(*iter.item());
			iter.advance();
		}

		size += queue.front().data.length;
		queue.pop();
	}
	return size;
}

void pruneTree(TreeIterator<xmlData> iter) { // I tried :c

	while (iter.childValid()){
		TreeIterator<xmlData> iter2(iter.childIter.currentNode->data);
		iter.childForth();
		pruneTree(iter2);
	}

	if (iter.item().nameType == "dir" && iter.node->children->count == 0) {
		TreeIterator<xmlData> iter2(iter.node->parent);
		while (iter2.childValid()){
			if (iter2.childIter.currentNode != nullptr && iter2.item().nameType == "dir" && iter2.childIter.currentNode->data->children->count == 0) {
				iter2.removeChild();
			}
			iter2.childForth();
		}
	}
}

void findPartialString(TreeIterator<xmlData> iter, string str)
{
	if (iter.item().name.find(str) != string::npos) {
		string s = iter.item().name;
		while (iter.node->parent != nullptr) {
			iter.up();
			s = iter.item().name + "/" + s;
		}
		cout << s << "/" << endl;
		return;
	}
	while (iter.childValid()){
		TreeIterator<xmlData> iter2(iter.childIter.currentNode->data);
		findPartialString(iter2, str);
		iter.childForth();
	}
}

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