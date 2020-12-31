#include<iostream>
#include<fstream>
#include"Citizen.h"
#include"Party.h"
#include"District.h"
#include"Election.h"
#include"SimpleElection.h"
#include"UnifiedDistrict.h"
#include <typeinfo>
//
using namespace std;
using namespace hw2;

const int MaxSize = 50;

enum PrimeMenu { CreateNew = 1, Load, getOut };

enum Menu {
	AddDistrict = 1,
	AddCitizen,
	AddParty,
	AddCitizenAsPartyCandid,
	DispalyDistricts,
	DisplayCitizens,
	DisplayParties,
	Vote,
	DisplayResults,
	Exit,
	SaveElection,
	LoadExistElection
};


int main()
{
	bool ok;
	int choice;
	char name[MaxSize];
	int id, partyId, yearOfBirth, districtId, numOfRep, repId;
	int electionType, districtType;
	Date date;
	Election* election = nullptr;
	ifstream infile;
	cout << "Hello and welcome" << endl <<
		"this is an interactive system" << endl;
	cout << endl << "Prime Menu:" << endl <<
		"1. Create new Election Round" << endl <<
		"2. Load exist Election round from file" << endl <<
		"3. Exit" << endl;
	cout << "please enter your choice: ";
	cin >> choice;
	switch (choice)
	{
	case CreateNew:
		cout << "Please enter a date for the election (day, month, year): ";
		cin >> date.day;
		cin >> date.month;
		cin >> date.year;
		while (!(((date.day >= 1 && date.day <= 31)) && ((date.month >= 1 && date.month <= 12))))
		{
			cout << "wrong input" << endl;
			cout << "Please enter a Valid date for the election (day, month, year): ";
			cin >> date.day;
			cin >> date.month;
			cin >> date.year;
		}
		cout << "Please enter the type of the Election: "<<endl
			<< "1 for Regular Election and 2 for Simple Election: ";
		cin >> electionType;
		if (electionType == 1)
		{
			election = new Election(date);
		}
		else
		{
			cout << "please enter the amount of rep: ";
			cin >> numOfRep;
			while (numOfRep < 0)
			{
				cout << "wrong input" << endl;
				cout << "Please enter a Valid amount of rep: ";
				cin >> numOfRep;
			}
			election = new SimpleElection(date, numOfRep);
		}
		break;
	case Load:
		//load from file
		break;
	case getOut:
		exit(0);
		break;
	default:
		cout << "ERROR! wrong input!"<<endl;
		break;
	}

	while (true)
	{
		cout << endl << "Menu:" << endl <<
			"1. Add District" << endl <<
			"2. Add Citizen" << endl <<
			"3. Add Party" << endl <<
			"4. Add Citizen as a Party member" << endl <<
			"5. Print all Districts" << endl <<
			"6. Print all Citizens" << endl <<
			"7. Print all Parties" << endl <<
			"8. Vote" << endl <<
			"9. Display results" << endl <<
			"10. Exit" << endl<<
			"11. Save Election" << endl<<
			"12. Load Exist Election" << endl;
		cout << "please enter your choice: ";

		cin >> choice;
		switch (choice)
		{
		case AddDistrict:
			////Distruct type: Unified / Divided
			cout << "please enter the District Type: " << endl << "1 for Unified and 2 for Divided: ";
			cin >> districtType;
			cout << "Please enter a name: ";
			cin >> name;
			cout << "please enter the amount of rep: ";
			cin >> numOfRep;
			while (numOfRep<0)
			{
				cout << "wrong input" << endl;
				cout << "Please enter a Valid amount of rep: ";
				cin >> numOfRep;
			}
			if (!election->addDistrict(name, numOfRep, districtType))
			{
				cout << "ERROR! you can't add Districts in this type of Election! " << endl;
			}
			break;
		case AddCitizen:
			cout << "Please enter a name: ";
			cin >> name;
			cout << "please enter an id: ";
			cin >> id;
			cout << "please enter year of birth: ";
			cin >> yearOfBirth;
			cout << "please enter district id: ";
			cin >> districtId;
			ok = election->addCitizen(name, id, yearOfBirth, districtId);
			if (!ok)
			{
				cout << "wrong input!!! there is no such district or the id is taken" << endl;
			}
			break;
		case AddParty:
			cout << "Please enter a name: ";
			cin >> name;
			cout << "please enter the id of the candid for the PM: ";
			cin >> id;
			ok = election->addParty(name, id);
			if (!ok)
			{
				cout << "wrong input!!! the candid does not exist" << endl;
			}
			break;
		case AddCitizenAsPartyCandid:
			cout << "please enter the rep id: ";
			cin >> repId;
			cout << "please enter the party id: ";
			cin >> partyId;
			cout << "please enter district id: ";
			cin >> districtId;
			ok = election->addCitizenAsPartyCandid(repId, partyId, districtId);
			if (!ok)
			{
				cout << "wrong input!!!" << endl;
			}
			break;
		case DispalyDistricts:
			election->display(5);
			break;
		case DisplayCitizens:
			election->display(6);
			break;
		case DisplayParties:
			election->display(7);
			break;
		case Vote:
			cout << "please enter your id: ";
			cin >> id;
			cout << "please enter the party id: ";
			cin >> partyId;
			ok = election->vote(id, partyId);
			if (!ok)
			{
				cout << "wrong input!!!" << endl;
			}
			break;
		case DisplayResults:
			cout << "Date: " << date.day << "/" << date.month << "/" << date.year << endl;
			election->displayResult();
			break;
		case Exit:
			delete election;
			exit(0);
			break;
		case SaveElection:
			cout << "Please enter file name: ";
			cin >> name;
			if (!election->save(name))
			{
				cout << "ERROR! The Election could not be saved. " << endl;
				exit(1);
			}
			break;
		case LoadExistElection:
			cout << "Please enter file name to load: ";
			cin >> name;
			delete election;
			infile.open(name, ios::binary);
			if (!infile)
			{
				cout << "ERROR! The Election could not be loaded! " << endl;
				exit(1);
			}
			int type;
			infile.read(reinterpret_cast<char*>(&type), sizeof(int));
			if(!infile.good())
			{
				cout << "ERROR! The reading has FAILD! " << endl;
				exit(1);
			}
			if (type == 1)
			{
				election = new Election(infile);
			}
			else //type == 2
			{
				election = new SimpleElection(infile);
			}
			if(election==nullptr)
			{
				cout << "ERROR! The Election could not be loaded! " << endl;
				exit(1);
			}
			if(!election->setP(infile))
			{
				cout << "ERROR! The Election could not be loaded! " << endl;
				exit(1);
			}
			break;
		default:
			cout << "WRONG INPUT!!" << endl;
			break;
		}
	}
	delete election;
}
