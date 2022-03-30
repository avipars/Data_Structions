#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <cmath>
#include "HuffmanTree.h"
#include <map>
using namespace std;

int main()
{
	char choice;
	HuffmanTree* t = NULL;
	string word;
	int n;
	int index = -1;
	string letters, encStrc, encTxt;

	cout << "enter E to encode a text\n";
	cout << "enter D to decode a text\n";
	cout << "enter X to exit\n";

	do
	{
		try {

			cin >> choice;
			switch (choice)
			{
			case 'E':

				cout << "enter the original text" << endl;
				cin >> word;
				t = new HuffmanTree(word);
				t->encodeWord(word);
				break;
			case 'D':

				cout << "enter n ";
				cin >> n;
				cout << endl << "enter the letters ";
				cin >> letters;
				cout << endl << "enter the encoded structure ";
				cin >> encStrc;
				cout << endl << "enter the encoded text ";
				cin >> encTxt;

				t = new HuffmanTree(encStrc, n, letters, encTxt);

				cout << endl;
				break;
			}
		}
		catch (...)
		{
			cout << "ERROR\n";
		}
	} while (choice != 'X');

	cout << "bye" << endl;
	return 0;
}
