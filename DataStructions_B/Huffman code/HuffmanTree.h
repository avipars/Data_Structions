#pragma once
#include <string>
#include <queue>
#include <iostream>
#include <map>
using namespace std;

// clas to repesent a nide in the Huffman tree
class HuffmanNode
{


public:

	char ch;
	int freq;
	HuffmanNode* left;
	HuffmanNode* right;
	friend class compareNode;
};

// class to comper between two node baised on there freqency
class compareNode {
public:
	bool operator()(HuffmanNode* const& n1, HuffmanNode* const& n2)
	{
		return n1->freq > n2->freq;
	}
};

class HuffmanTree
{
private:
	string treeStructure;
	int countChar;
	string OrderOfLetters;

public:

	// Create a priority queue to store live nodes of
	// Huffman tree;
	priority_queue <HuffmanNode*, vector<HuffmanNode*>, compareNode> pQueue;


	//ctors
	HuffmanTree(string treeStructure1, int countChar1, string OrderOfLetters1, string theEncoding1);
	HuffmanTree(string s);


	void  encodeWord(string text);
	void printStruct(HuffmanNode* root);

	void decodeWord(string letters, string encStrc, string encTxt);

	// traverse the Huffman Tree and decode the encoded string
	void decode(HuffmanNode* root, int& index, string str);
private:
	// Function to allocate a new tree node
	HuffmanNode* getNode(char ch, int freq, HuffmanNode* left, HuffmanNode* right);

	// traverse the Huffman Tree and store Huffman Codes
	// in a map.
	void encode(HuffmanNode* root, string str,
		map<char, string>& huffmanCode);

	void creatTree(HuffmanNode* root, string encStrc, int& index1, string letters, int& index2);

	string encodingOfEachChar[26]; // Save the encoding for each character.
	void fillArray_EncodingOfEachChar(HuffmanNode* p, string encoding);
	int indexOfChar(char c) /*Return the index of char in array 'encodingOfEachChar'*/ { return (int)c - 97; }
	string fillTheText(string encoding);
	int searchIfHaveThisEncoding(string enco);
	void printLetters(HuffmanNode* root);

};

