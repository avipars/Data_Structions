
#pragma once
#include "Hash.h"
#include "Item.h"
#include "Volunteer.h"
#include<string>
#include<iostream>
#include <cmath>

template <typename T, typename K>
class HashVolunteer : public Hash<Volunteer, string>
{
public:

	//ctor
	HashVolunteer(int num) : Hash <Volunteer, string>::Hash(num) {};

	//dtor
	~HashVolunteer()
	{
		if (hashTable)
		{
			delete[] hashTable;
			hashTable = NULL;
			size = 0;
		}
	}
	int h1(string key) override;//the first hash function
	int h2(string key) override;//the second hash function

	void insert(Item<Volunteer, string> item)override;
	int convertStringToUniqInt(string& str);
};

///implementation ///


//override the insert function
template<typename T, typename K>
void HashVolunteer<T, K>::insert(Item<Volunteer, string> item)
{
	item.key = item.data.name;
	this->Hash::insert(item);
}


template <typename T, typename K>
int HashVolunteer<T, K>::h1(string key)
{
	return convertStringToUniqInt(key) % size;

}



template <typename T, typename K>
int HashVolunteer <T, K>::h2(string key)
{
	return convertStringToUniqInt(key) % (size - 1) + 1;
}


//Auxiliary function that converts a string to an integer so we can use it as a key
template <typename T, typename K>
int HashVolunteer <T, K>::convertStringToUniqInt(string& str)
{
	int key = 0;
	int i = 0;

	//Each letter starting from the end of the string is given a unique
	//value so that at the end we get an integer that will serve as a key
	for (auto iter = str.rbegin(); iter != str.rend(); iter++)
	{
		key += ((int)(*iter) % 96) * pow(3, i);
		i++;
	}

	return key;
}