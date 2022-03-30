
#pragma once
#include <string>
#include "Tree.h"
#include "Node.h"
#include <iostream>
using namespace std;
class Node;
//Answer: for each answer, the string, and the pointer to the node where to continue
class Answer
{
public:
	string ans;
	Node* son;
	Answer(string s, Node* p) { ans = s; son = p; }
};
