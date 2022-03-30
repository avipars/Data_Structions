/*
#pragma once
#include <iostream>
#include <string>
#include<list>
#include <algorithm>
using namespace std;

class Volunteer
{

public:
	string name;
	int phone;
	string address;
	list <string> clientsNames;

	//defult ctor
	Volunteer() { name = "unnamed"; phone = 0; address = "unnamed"; }

	//ctor
	Volunteer(string name_, int phone_, string address_)
	{
		if (phone <= 0)
			throw "ERROR";
		name = name_;
		phone = phone_;
		address = address_;
	}

	//getters
	string getName()const;
	int getPhone()const;
	string getAddress()const;

	bool operator== (const Volunteer) const;
	friend istream& operator>>(istream& is, Volunteer& volunteer);
	friend ostream& operator<<(ostream& os, Volunteer& volunteer);
};

/// Implementation ///

string Volunteer::getName()const
{
	return name;
}

int Volunteer::getPhone()const
{
	return phone;
}
string Volunteer::getAddress()const
{
	return address;
}

bool Volunteer::operator==(const Volunteer volunteer) const
{
	bool equal = false;
	if (this->name == volunteer.name)
		equal = true;
	return equal;
}

istream& operator>>(istream& is, Volunteer& volunteer)
{
	int phone_;
	string name_, address_;
	is >> name_ >> phone_ >> address_;
	if (phone_ < 0)
		throw "ERROR";
	volunteer.name = name_;
	volunteer.phone = phone_;
	volunteer.address = address_;
	return is;
}

ostream& operator<<(ostream& os, Volunteer& volunteer)
{
	os << "volunteer ";
	os << "name=" << volunteer.name << " ";
	os << "Phone=" << volunteer.phone << " ";
	os << "address=" << volunteer.address;

	return os;
}
