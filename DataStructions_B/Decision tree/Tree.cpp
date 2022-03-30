
#include "Tree.h"
#include <algorithm>
#include <list>

Node* Tree::search(Node* p, string val, Node*& parent)
{
	Node* found = NULL;
	if (p->value == val) //if the current node is searcher node
		return p;	
	if (p->isLeaf) //if the node is not equal the string and he has a leaf
			return found;
	if (p->answersList.empty())
		return found;

	//if he had a sons so search the node on them 
	for (auto it = p->answersList.begin(); it != p->answersList.end(); it++)
	{
		parent = p;
		found = search((*it)->son, val, parent);
	
		if (!found)
			parent = NULL;
		if (found)
			return found;
	}
	return found;
}

//delete the the recived sub tree
void Tree::deleteAllSubTree(Node* t)
{
	if (t == NULL)
		return;
	if (t->isLeaf)
	{
		delete t;
		t = NULL;
		return;
	}

	//a loop to delete the sons
	for (auto it = t->answersList.begin(); it != t->answersList.end(); it++)
	{
		if ((*it))
		{
			deleteAllSubTree((*it)->son);
			delete (*it);
			(*it) = NULL;
		}
	}
	delete t;
	t = NULL;
}

void Tree::addRoot(string newval)
{
	Node* tmp=new Node(newval);
	root = tmp;
}

bool Tree::addSon(string fatherquestion, string newanswer, string newval)
{
	Node* parent;
	Node* found = search(root, fatherquestion, parent);
	if(!found)
		return false;
	Node* son = new Node(newval);
	Answer* ans = new Answer(newanswer, son);
	found->answersList.push_back(ans);
	found->isLeaf = false;
	return true;
}

void Tree::deleteSubTree(string val)
{
	Node* parent = NULL;
	Answer* temp = NULL;
	Node* found = search(root,val,parent);
	if (!found)
		throw "The value not exist";
	if (parent)
	{
		for (auto it = parent->answersList.begin(); it != parent->answersList.end(); it++)
		{
			if ((*it)->son->value == found->value)
				temp = (*it);
		}
	}
	deleteAllSubTree(found);
	if (parent)
	{
		if (temp)
			delete temp;
		if (parent->answersList.empty())
			parent->isLeaf = true;
	}
}

void Tree::process(Node* p)
{
	cout << p->value << endl;
	if (p->isLeaf)
		return;
	string newAns;
	cin >> newAns;
	for (auto it = p->answersList.begin(); it != p->answersList.end(); it++)
	{
		if ((*it)->ans == newAns)
		{
			process((*it)->son);
			break;
		}
	}
}

void Tree::print(Node* p, int level)
{
	if (p)
	{
		for (int i = 0; i < level; i++)
		{
			cout << "  ";
		}
		cout << p->value << endl;
	}
	if (p->isLeaf)
		return;
	for (auto it = p->answersList.begin(); it != p->answersList.end(); it++)
	{
		if ((*it))
		{
			for (int i = 0; i < level; i++)
			{
				cout << "  ";
			}
			cout << ": " << (*it)->ans << endl;
			print((*it)->son, ++level);
		}
		level--;
	}
}
bool Tree::searchAndPrint(Node* p, string val)
{
	bool flag = false;
	Node* parent = NULL;
	Node* found = search(p, val, parent);
	if (!found) //if the value not found
		return flag;
	
	cout << found->value; //if the value found so print it
	if (!parent) //if the parent is null
		return true;
	cout << "=>"; 
	flag = searchAndPrint(p, parent->value);
	return flag;
}
string Tree::printToString(Node* p) {}