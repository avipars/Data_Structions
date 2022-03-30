
#include <string>
#include "Volunteer.h"
#include "Client.h"
#include "Hash.h"
#include "HashClient.h"
#include "HashVolunteer.h"
#include "Item.h"
#include "HashTbls.h"
#include <iostream>
using namespace std;
int main()
{
	char ch;

	list <Volunteer*> lst;
	HashTbls ht;
	cout << "Hash Tables\n";
	do
	{
		cout << "\nChoose one of the following" << endl;
		cout << "n: New volunteer" << endl;
		cout << "d: Del a volunteer " << endl;
		cout << "c: New client" << endl;
		cout << "l: Add a connection volunteer-client " << endl;
		cout << "*: Print volunteers that helped a client " << endl;
		cout << "i: Print clients that were helped by a voluneer " << endl;
		cout << "p: Print hash tables" << endl;
		cout << "e: Exit" << endl;
		try
		{
			Volunteer v;
			Client c;
			cin >> ch;
			switch (ch)
			{
			case 'n':
				cout << "Enter volunteer name phone address" << endl;
				cin >> v; ht.addVolunteer(v);
				break;
			case 'd':
				cout << "enter volunteer name ";
				cin >> v.name; ht.delVolunteer(v);
				break;
			case 'c':
				cout << "please enter name and phone and address of client" << endl;
				cin >> c; ht.addClient(c);
				break;
			case 'l':
				cout << "enter volunteer name and client phone ";
				cin >> v.name >> c.phone;
				ht.addVolunteerToClient(v, c);
				break;
			case '*':
				cout << "enter client phone ";
				cin >> c.phone; ht.listOfVolunteers(c);
				break;
			case 'i':
				cout << "enter volunteer name ";
				cin >> v.name; ht.listOfClients(v);
				break;
			case 'p': ht.printAll(); break;
			case 'e': cout << "bye "; break;
			default: cout << "Error ";  break;
			}
		}
		catch (const char* ex)
		{
			cout << ex << endl;
		}

	} while (ch != 'e');

	return 0;
}
