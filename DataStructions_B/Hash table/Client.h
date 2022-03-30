
#pragma once
#include "Item.h"
#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include "Volunteer.h"
using namespace std;

class Client
{

public:

	string name;
	int phone;
	string address;
	list <string> volunteersNames;

	//defult ctor
	Client() { name = ""; phone = 0; address = ""; }

	//ctor
	Client(string myName, int myPhoneNum, string Myaddress)
	{
		if (myPhoneNum <= 0)
			throw "ERROR";
		name = myName;
		phone = myPhoneNum;
		address = Myaddress;
	}

	friend ostream& operator<< (ostream& os, const Client& c);
	friend istream& operator >>(istream& is, Client& c);
	bool operator ==(const Client c) const;
};

// Implementation// 

ostream& operator<<(ostream& os, const Client& c)
{
	os << "client ";
	os << "name: " << c.name << " ";
	os << "Phone: " << c.phone << " ";
	os << "address: " << c.address;
	if (c.volunteersNames.size() > 0)
	{
		os << "helped by:  ";
		for (auto it = c.volunteersNames.begin(); it != c.volunteersNames.end(); it++)
			cout << *it << " ";
	}

	return os;
}

istream& operator>>(istream& is, Client& c)
{
	string _name, _address;
	int _phone;

	is >> _name;
	is >> _phone;
	is >> _address;

	if (_phone < 0)
		throw "ERROR";

	c.name = _name;
	c.phone = _phone;
	c.address = _address;

	return is;
}

bool Client::operator==(const Client c) const
{

	if (phone == c.phone)
		return true;
	return false;
}

