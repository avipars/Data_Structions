
#pragma once
#include "Item.h"
#include<iostream>
#include<algorithm>
#include<string>
#include <vector>
#include <cmath>
using namespace std;


template <typename T, typename K>
class Hash
{

public:
	Item <T, K>* hashTable;
	int size;

	//ctor
	Hash(int num)
	{
		size = PrimeNum(num);
		hashTable = new Item<T, K>[size];
	}

	//dtor
	~Hash()
	{
		if (hashTable)
		{
			delete[] hashTable;
			hashTable = NULL;
			size = 0;
		}
	}

	virtual int h1(K key) = 0; //the first hash function

	virtual int h2(K key) = 0;//the second hash function

	int hash(K key, int i);//the main hash function that return the appropriate index

	virtual void insert(Item<T, K> item);
	int search(Item<T, K> item);
	void deleteItem(Item<T, K> item);
	void printHashTable();
	static int PrimeNum(int num); //return the closest prime number to a given number

};



/// Implementation ///


//the main hash function that return the appropriate index
template<typename T, typename K>
int Hash<T, K>::hash(K key, int i)
{
	return (h1(key) + (i * h2(key))) % size;
}


//insert new item
template<typename T, typename K>
void Hash<T, K>::insert(Item<T, K> item)
{
	int i;
	int index = 0;
	for (i = 0; i < size; i++)
	{
		index = hash(item.key, i);

		//if the place available insert there
		if (hashTable[index].flag == state::empty || hashTable[index].flag == state::deleted)
		{
			item.flag = state::full;
			hashTable[index] = item;
			return;
		}
	}

	if (i == size)
		throw "ERROR";
}

//search an item
template<typename T, typename K>
int Hash<T, K>::search(Item<T, K> item)
{
	int i;
	int index = 0;
	for (i = 0; i < size; i++)
	{
		index = hash(item.key, i);

		if (hashTable[index].flag != state::deleted)
		{
			//if the item fount return his index
			if (hashTable[index].data == item.data)
				return index;

			//if the place is empty the item not found
			//Because if he was in the table he should have been in that index
			if (hashTable[index].flag == state::empty)
				return -1;
		}

	}

	//the item not found
	if (i == size)
		return -1;
}


//delete an item
template<typename T, typename K>
void Hash<T, K>::deleteItem(Item<T, K> item)
{
	int i;
	int index = 0;
	for (i = 0; i < size; i++)
	{
		index = hash(item.key, i);

		//if the place is empty or deleted throw an error because this item not exist
		if (hashTable[index].flag == state::empty || hashTable[index].flag == state::deleted)
			throw "ERROR";
		if (hashTable[index].data == item.data)
		{
			hashTable[index].flag = state::deleted;
			return;
		}
	}
	if (i == size)
		throw "ERROR";

}

//print the details of the table
template<typename T, typename K>
void Hash<T, K>::printHashTable()
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (hashTable[i].flag == state::full)
		{
			cout << hashTable[i].key << ":";
			cout << hashTable[i].data << endl;
		}
	}
}


//return nearest prime number, bigger from a given number
template<typename T, typename K>
int Hash<T, K>::PrimeNum(int num)
{
	bool flag = false;
	int i;
	while (!flag)
	{
		for (i = 2; i <= sqrt(num); i++)
		{
			if (!(num % i))
			{
				num++;
				break;
			}
		}

		//if there is not number that divide num, end the loop
		if (i > sqrt(num))
			flag = true;
	}
	return num;
}