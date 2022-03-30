
#pragma once
#include <string>
#include <iostream>
#include "Tree.h"
#include "Answer.h"
using namespace std;

class Answer;
//Node: each node in the decision tree
class Node
{
public:
	list<Answer*> answersList;
	string value;
	bool isLeaf;
	Node(string v) { isLeaf = true;  value = v; answersList.clear(); }

	friend class Tree;
};