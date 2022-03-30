
#pragma once
#include "Hash.h"
#include "Client.h"

template <typename T, typename K>
class HashClient : public Hash	< Client, int>
{

public:

	//ctor
	HashClient(int num) : Hash <Client, int>::Hash(num) {};

	//dtor
	~HashClient()
	{
		if (hashTable)
		{
			delete[] hashTable;
			hashTable = NULL;
			size = 0;
		}
	}
	int h1(int key) override; //the first hash function
	int h2(int key) override; //the second hash function

	void insert(Item<Client, int> item)override;//override the insert function

};


// implementation //

//the first hash function
template <typename T, typename K>
int HashClient <T, K>::h1(int key)
{
	return key % size;

}

//the second hash function
template <typename T, typename K>
int HashClient <T, K>::h2(int key)
{
	return key % (size - 1) + 1;
}

//override the insert function
template<typename T, typename K>
void HashClient<T, K>::insert(Item<Client, int> item)
{
	item.key = item.data.phone;
	this->Hash::insert(item);
}

