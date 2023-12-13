// CA2_XML_to_Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "TreeFunctions.h"

using namespace std;


int main()
{
	// Step 1 Read in a XML file

	string xml = readFile("../xml.xml");

	//cout << xml;

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

	treeIter.root();
	cout << "Number of Folders " << countFolders(treeIter) << endl;
	cout << "Number of Files " << countFiles(treeIter) << endl;
	cout << "Total number of items " << xmlTree->count() << endl;

	// Step 5 Determine the memory used of a given dir

	cout << "The files in this folder are using a total of " << calcMemoryUsed(*xmlTree) << " b" << endl;

	// Step 6 Remove empty folder - This one does not work

	//pruneTree(treeIter);

	// Step 7 Find a particular folder given a filename and generate a path

	findPartialString(treeIter, "SinglyLinkedList");

	// Step 8 Display a given dir

	displayTree(treeIter, "");

	//std::cout << xml;
}