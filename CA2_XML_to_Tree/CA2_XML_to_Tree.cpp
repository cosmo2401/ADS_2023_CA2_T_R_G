// CA2_XML_to_Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Stack.h"
#include "Tree.h"
#include "TreeIterator.h"

using namespace std;


int main()
{

    string xml = R"(<dir>
        < name > ADS_Single_LinkedList_Exercises< / name>
        <dir>
        <name>.git< / name>
        <file>
        <name>config< / name>
        < length>353 b< / length>
        <type>config< / type>
        < / file>
        <file>
        <name>description< / name>
        < length>73 b< / length>
        <type>description< / type>
        < / file>
        <file>
        <name>HEAD< / name>
        < length>23 b< / length>
        <type>HEAD< / type>
        < / file>
        < / dir>
        <dir>
        <name>.vs< / name>
        <dir>
        <name>ADS_Single_LinkedList_Exercises< / name>
        <dir>
        <name>v17< / name>
        < / dir>
        < / dir>
        < / dir>
        <dir>
        <name>Debug< / name>
        <file>
        <name>SinglyLinkedList.pdb< / name>
        < length>978944 b< / length>
        <type>pdb< / type>
        < / file>
        <file>
        <name>TestSinglyLinkedList.exp< / name>
        < length>41528 b< / length>
        <type>exp< / type>
        < / file>
        <file>
        <name>TestSinglyLinkedList.pdb< / name>
        < length>1945600 b< / length>
        <type>pdb< / type>
        < / file>
        < / dir>
        < / dir>)";

    Stack<string>* newStack = new Stack<string>;

    newStack->Push("testing");

    cout << newStack->Top();

    if (newStack->Top() == "test") {
        cout << " its the same";
    }

    //std::cout << xml;



}

void valdiateXML(string data) {

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