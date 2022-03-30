#include "HuffmanTree.h"
#include <iostream>
using namespace std;

HuffmanTree::HuffmanTree(string treeStructure1, int countChar1, string OrderOfLetters1, string theEncoding1)
{
	treeStructure = treeStructure1; // the tree structure with number: 1 is a leef , 0 is internal node.
	countChar = countChar1; // Count how many characters there are.
	OrderOfLetters = OrderOfLetters1; // Characters In the order in which they appear in the tree
	decodeWord(OrderOfLetters, treeStructure1, theEncoding1);


}

void HuffmanTree::encodeWord(string text)
{

	// root stores pointer to root of Huffman Tree
	HuffmanNode* root = pQueue.top();

	// traverse the Huffman Tree and store Huffman Codes
	// in a map. Also prints them
	map<char, string> huffmanCode;
	encode(root, "", huffmanCode);


	cout << "The encoded string is:" << endl;
	cout << huffmanCode.size() << endl;


	printLetters(root);
	cout << endl;

	printStruct(root);
	cout << endl;
	// print encoded string
	string str = "";
	char ch;
	for (int i = 0; i < text.length(); i++) {
		ch = text[i];
		str += huffmanCode[ch];
	}

	cout << str << '\n';


}

HuffmanNode* HuffmanTree::getNode(char ch, int freq, HuffmanNode* left, HuffmanNode* right)
{

	HuffmanNode* node = new HuffmanNode();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;



}

void HuffmanTree::encode(HuffmanNode* root, string str, map<char, string>& huffmanCode)
{

	if (root == NULL)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);


}

void HuffmanTree::decode(HuffmanNode* root, int& index, string str)
{
	{
		if (root == NULL) {
			return;
		}

		// found a leaf node
		if (!root->left && !root->right)
		{
			cout << root->ch;
			return;
		}

		index++;

		if (str[index] == '0')
			decode(root->left, index, str);
		else
			decode(root->right, index, str);
	}
}

HuffmanTree::HuffmanTree(string text)
{
	// count frequency of appearance of each character
	// and store it in a map
	map<char, int> freq;
	char ch;
	for (int i = 0; i < text.length(); i++) {
		ch = text[i];
		freq[ch]++;
	}


	// Create a leaf node for each character and add it
	// to the priority queue.
	for (map<char, int>::const_iterator it = freq.begin(); it != freq.end(); ++it) {
		pQueue.push(getNode(it->first, it->second, NULL, NULL));
	}

	// do till there is more than one node in the queue
	while (pQueue.size() != 1)
	{
		// Remove the two nodes of highest priority
		// (lowest frequency) from the queue
		HuffmanNode* left = pQueue.top();  pQueue.pop();
		HuffmanNode* right = pQueue.top();	 pQueue.pop();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.
		int sum = left->freq + right->freq;
		pQueue.push(getNode('\0', sum, left, right));
	}

}

//print the struct of the tree on bits
void HuffmanTree::printStruct(HuffmanNode* root)
{
	if (root == NULL)

		return;


	if (root->left == NULL && root->right == NULL)
		cout << '1';
	else
		cout << '0';

	/* then recur on left subtree */
	printStruct(root->left);

	/* now recur on right subtree */
	printStruct(root->right);

}

//decode the encoded string
void HuffmanTree::decodeWord(string letters, string encStrc, string encTxt)
{
	int index1 = 0;
	int index2 = 0;
	HuffmanNode* root = new HuffmanNode();
	creatTree(root, encStrc, index1, letters, index2);
	fillArray_EncodingOfEachChar(root, "");
	string theTxt = fillTheText(encTxt);
	cout << endl << "The decoded string is " << endl;
	cout << theTxt << endl;
}

// (string) Encoding of each char is Huffman's codding.
// Any recursion add to (string)encoding the new 'encoding', if left add '0' else add '1'. 
// (string) Encoding is holder the char's encoding.
// Fill the array 'encodingOfEachChar'.		
void HuffmanTree::fillArray_EncodingOfEachChar(HuffmanNode* p, string encoding)

{
	try
	{
		if (p->left != NULL) // we in internal juction.
		{
			fillArray_EncodingOfEachChar(p->left, encoding + '0');

			// If have san left of course have san right.
			fillArray_EncodingOfEachChar(p->right, encoding + '1');
		}
		else // we in a leef
		{
			encodingOfEachChar[indexOfChar(p->ch)] = encoding;
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}


}

// fill variable 'TheText'
string HuffmanTree::fillTheText(string encoding)
{
	string character = "";
	string theText;
	for (size_t i = 0; i < encoding.size(); i++)
	{
		character += encoding[i];
		int index = searchIfHaveThisEncoding(character);
		if (index != -1) // Have the 'character' in the array.
		{
			theText += (char)(index + 97);
			character = "";
		}
	}
	return theText;
}

//Return 'i' (index) if have the enco (encoding) in the array 'encodingOfEachChar', else -1.
int HuffmanTree::searchIfHaveThisEncoding(string enco)
{
	for (size_t i = 0; i < 26; i++)
		if (encodingOfEachChar[i] == enco)
			return i;

	return -1;
}

//build a tree by given the struct of the tree in bits and the order of the letters of the leafs
void HuffmanTree::creatTree(HuffmanNode* root, string encStrc, int& index1, string letters, int& index2)
{

	if (encStrc[index1] == '0')
	{
		root->left = new HuffmanNode();
		root->right = new HuffmanNode();
		creatTree(root->left, encStrc, ++index1, letters, index2);
		creatTree(root->right, encStrc, ++index1, letters, index2);
	}
	else
	{
		if (index2 >= OrderOfLetters.size())
			throw " ";
		root->ch = letters[index2++];
	}
}


void HuffmanTree::printLetters(HuffmanNode* root)
{
	if (root == NULL)
		return;
	if (root->left)
		printLetters(root->left);
	if (root->left == NULL && root->right == NULL)
	{
		cout << root->ch;
	}
	if (root->right)
		printLetters(root->right);
}
