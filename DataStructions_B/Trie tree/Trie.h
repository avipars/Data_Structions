
#pragma once
#include <iostream>
using namespace std;

class Trie
{
protected:

	//// Trie node
	class TrieNode
	{
	public:
		TrieNode* children[26] = { 0 };
		TrieNode* father;
		char letter;

	// isEndOfWord is true if the node represents
	// end of a word
		bool isEndWord = false;

		TrieNode() {
			for (int i = 0; i < 26; i++)
			{
				children[i] = NULL;
			}
			father = nullptr;
			letter = '\0';
		}; //ctor
	};

	TrieNode* root;

public:
	Trie() { root = new TrieNode; }; //ctor
	void insert(string wrd);
	bool del(string wrd);
	bool search(string wrd);
	int printAutoSuggestions(string wrd);

	//help-functions
private:
	TrieNode* getNode(string str);
	void PrintLexical(TrieNode* current, string prefix, string suffix);
};

