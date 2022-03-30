
#include "Trie.h"
#include <iostream>
using namespace std;

// Insert the word in the Trie.
// Check each character in the string 
// If none of the children of the current node contains the character, 
// create a new child of the current node for storing the character. 
void Trie::insert(string wrd)
{
	TrieNode* current = root;
	for (int i = 0; i < wrd.size(); i++)
	{
		if (current->children[wrd.at(i) - 'a'] == NULL) {
			current->children[wrd.at(i) - 'a'] = new TrieNode;
			current->children[wrd.at(i) - 'a']->father = current;
			current->children[wrd.at(i) - 'a']->letter = wrd.at(i);
		}
		current = current->children[wrd.at(i) - 'a'];
	}
	// mark last node as leaf
	current->isEndWord = true;

}

// Search the word in Trie
bool Trie::search(string wrd)
{
	TrieNode* node = getNode(wrd);
	if (node == NULL)
		return false;
	else if (node->isEndWord)
		return true;
	else
		return false;
}

// Print the words with the specified prefix in lexical order
int Trie::printAutoSuggestions(string wrd)
{
	TrieNode* node = getNode(wrd);
	if (node == NULL)
		return 0;

	bool flag = false;
	for (int i = 0; i < 26; i++)
	{
		if (node->children[i] != NULL)
		{
			flag = true;
			break;
		}
	}
	if (!flag)
	{
		cout << wrd << endl;

	}
	else
		PrintLexical(node, wrd, "");

	return 1;
}

//Help-function to print the words with the specified prefix in lexical order
void Trie::PrintLexical(TrieNode* current, string prefix, string suffix)
{

	if (current->isEndWord && suffix.size() != 0)
	{
		cout << prefix + suffix << endl;
	}
	for (int i = 0; i < 26; i++) {
		string temp = suffix;
		if (current->children[i] != nullptr) {
			temp += current->children[i]->letter;
			PrintLexical(current->children[i], prefix, temp);
		}
	}
}

bool Trie::del(string wrd)
{
	//If the word not found
	if (!search(wrd))
		return false;

	TrieNode* current = root;

	//get to the word
	for (int i = 0; i < wrd.size(); i++)
	{
		current = current->children[wrd.at(i) - 'a'];

	}

	for (int i = 0; i < 26; i++)
	{
		// If the word is prefix of any other word unmark it has a last node as a end of word
		if (current->children[i] != NULL)
		{
			current->isEndWord = false;
			return true;
		}
	}

	// If the word is not prefix of any other word
	//delete all the letter that they not prefix of any other word
	bool flag = true;
	while (flag)
	{
		char chr = current->letter;
		current = current->father;

		current->children[chr - 'a'] = NULL;

		for (int i = 0; i < 26; i++)
		{
			if (current->children[i])
			{
				flag = false;
				break;

			}
		}


	}


	return true;

}

//return node of the end of a spcific word 
Trie::TrieNode* Trie::getNode(string wrd)
{
	TrieNode* current = root;
	for (int i = 0; i < wrd.size(); i++) {
		for (int i = 0; i < wrd.size(); i++) {
			if (current->children[wrd.at(i) - 'a']) {
				current = current->children[wrd.at(i) - 'a'];
			}
			else {
				current = NULL;
				break;
			}
		}

		return current;
	}
}

