
#pragma once
#include <iostream>
#include <list>
#include <string>
#include "Node.h"
#include "Answer.h"
using namespace std;

class Node;

//Tree: the Decision Tree
class Tree
{
	Node* root;
	Node* search(Node* p, string val, Node*& parent);// done
	//returns node t where the string equals val. If t has a prent, the pointer parent will contain its address. 

	bool searchAndPrint(Node* p, string val); //Search a node and print the path
	void print(Node* p, int level = 0); //print all the tree
	void process(Node* p);// run the Decision Tree
public:
	Tree() { root = NULL; } //constructor
	~Tree() //destructor
	{
		deleteAllSubTree(root);
		root = 0;
	}
	void deleteAllSubTree(Node* t); 
	void addRoot(string newval);
	bool addSon(string fatherquestion, string newanswer, string newval); //adding a new son
	void searchAndPrint(string val) //search and print the path
	{
		if (!searchAndPrint(root, val))
			cout << "Value not found" << endl;
	}
	void searchAndPrintArea(string val)
	{
		Node* parent;
		Node* area = search(root, val, parent);
		if (area) print(root);
	}
	void printAllTree() { print(root); }
	string printToString(Node* p);
	string printToString() { return printToString(root); }
	void deleteSubTree(string val);
	void process() { process(root); }
};

