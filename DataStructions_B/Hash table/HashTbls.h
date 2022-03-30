
#pragma once
#include <string>
#include "Volunteer.h"
#include "Client.h"
#include "Hash.h"
#include "HashClient.h"
#include "HashVolunteer.h"
#include "Item.h"
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class HashTbls
{

public:
	HashClient <Client, int> HashTblsClient;
	HashVolunteer <Volunteer, string> HashTblsVolunteer;
	list<Item<Volunteer, string>> deletedVolunteers;

	//defult ctor
	HashTbls() : HashTblsClient(100),
		HashTblsVolunteer(100)
	{};

	void addVolunteer(Volunteer v);
	void delVolunteer(Volunteer v);
	void addClient(Client c);
	void addVolunteerToClient(Volunteer v, Client c);
	void listOfVolunteers(Client c);
	void listOfClients(Volunteer v);
	void printAll();
};


// implementaion//


//add new volunteer
void HashTbls::addVolunteer(Volunteer v)
{
	Item<Volunteer, string> item(v);
	HashTblsVolunteer.insert(item);
}

//delete given volunteer
void HashTbls::delVolunteer(Volunteer v)
{
	Item<Volunteer, string> item(v);
	item.key = v.name;
	int index = HashTblsVolunteer.search(item);
	HashTblsVolunteer.deleteItem(item);
	deletedVolunteers.push_back(HashTblsVolunteer.hashTable[index]);
}

//add new client
void HashTbls::addClient(Client c)

{
	Item<Client, int> item(c);
	HashTblsClient.insert(item);
}

//Add a connection volunteer-client
void HashTbls::addVolunteerToClient(Volunteer v, Client c)
{
	Item<Volunteer, string> itemVolunteer(v);
	itemVolunteer.key = v.name;

	//if the volunteer not exist throw an error
	if (HashTblsVolunteer.search(itemVolunteer) == -1)
		throw "ERROR";

	Item<Client, int> itemClient(c);
	itemClient.key = c.phone;

	//if the client not exist throw an error
	if (HashTblsClient.search(itemClient) == -1)
		throw "ERROR";

	int indexC = HashTblsClient.search(itemClient);
	int indexV = HashTblsVolunteer.search(itemVolunteer);

	//We will go through the list of volunteers at the
	//client and check if the volunteer is there. If he not there we add it to the list
	for (auto it = HashTblsClient.hashTable[indexC].data.volunteersNames.begin(); it != HashTblsClient.hashTable[indexC].data.volunteersNames.end(); it++)
	{
		if (*it == v.name)
			throw "ERROR";
	}
	HashTblsClient.hashTable[indexC].data.volunteersNames.push_back(HashTblsVolunteer.hashTable[indexV].data.name);

	//We will go through the list of clients at the
	//volunteer and check if the client is there. If he not there we add it to the list
	for (auto it = HashTblsVolunteer.hashTable[indexV].data.clientsNames.begin(); it != HashTblsVolunteer.hashTable[indexV].data.clientsNames.end(); it++)
	{
		if (*it == c.name)
			throw "ERROR";
	}
	HashTblsVolunteer.hashTable[indexV].data.clientsNames.push_back(HashTblsClient.hashTable[indexC].data.name);
}

//print the list of volunteers that helpted the client
void HashTbls::listOfVolunteers(Client c)
{
	Item<Client, int> itemClient(c);
	itemClient.key = c.phone;
	cout << "The volunteers that helped to client " << itemClient.key << ": ";
	if (HashTblsClient.search(itemClient) != -1)
	{
		int index = HashTblsClient.search(itemClient);
		for (auto it = HashTblsClient.hashTable[index].data.volunteersNames.begin(); it != HashTblsClient.hashTable[index].data.volunteersNames.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
}

//print the list of clients that were helped by the volunteer
void HashTbls::listOfClients(Volunteer v)
{
	Item<Volunteer, string> itemVolunteer(v);
	itemVolunteer.key = v.name;
	cout << "The clients that were helped by volunteer " << itemVolunteer.key << ": ";

	if (HashTblsVolunteer.search(itemVolunteer) != -1)
	{
		int index = HashTblsVolunteer.search(itemVolunteer);
		for (auto it = HashTblsVolunteer.hashTable[index].data.clientsNames.begin(); it != HashTblsVolunteer.hashTable[index].data.clientsNames.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}

	//if the volunteer not exsit search if this volunteer was exist but deleted
	// If so, print the his client list
	else
	{
		for (auto it1 = deletedVolunteers.begin(); it1 != deletedVolunteers.end(); it1++)
		{
			if (it1->key == itemVolunteer.key)
			{
				for (auto it2 = it1->data.clientsNames.begin(); it2 != it1->data.clientsNames.end(); it2++)
				{
					cout << *it2 << " ";
				}
			}
		}
	}
}


//print the all clients and volunteers
void HashTbls::printAll()
{
	cout << "Volunteer:" << endl;
	HashTblsVolunteer.printHashTable();
	cout << "Client:" << endl;
	HashTblsClient.printHashTable();
}