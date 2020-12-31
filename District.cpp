#include "District.h"
#include "Helper.h"
#include <iostream>
#include <fstream>
#include <typeinfo>
//
using namespace std;
namespace hw2 {
	int District::countId = 0;
	class DividedDistrict;
	District::District(char* name, int aor) :id(countId), countVotes(0), presentOfVoters(0), amountOfRep(aor)
	{
		countId++;
		copyStr(&(this->name), name);
		this->allowedVoters = new CList();
		this->elected = new CList();
	}
	District::District(const District& other)
	{
		(*this) = other;
	}
	District::District(ifstream& infile)
	{
		int nLen;
		infile.read(reinterpret_cast<char*>(&nLen), sizeof(int));
		this->name = new char[nLen + 1];
		infile.read(this->name, sizeof(char) * nLen);
		this->name[nLen] = '\0';
		infile.read(reinterpret_cast<char*>(&id), sizeof(int));
		infile.read(reinterpret_cast<char*>(&amountOfRep), sizeof(int));
		infile.read(reinterpret_cast<char*>(&presentOfVoters), sizeof(float));
		allowedVoters = nullptr;
		elected = nullptr;
		infile.read(reinterpret_cast<char*>(&countVotes), sizeof(int));
	}
	District::~District()
	{
		delete[] name;
		delete this->elected;
		delete this->allowedVoters;
	}

	const District& District::operator=(const District& other)
	{
		if (this != &other)
		{
			delete[] this->name;
			copyStr(&(this->name), other.name);
			this->id = other.id;
			this->amountOfRep = other.amountOfRep;
			this->presentOfVoters = other.presentOfVoters;
			this->allowedVoters = other.allowedVoters;
			this->elected = other.elected;
		}
		return *this;
	}

	//Getter
	const char* District::getName()const
	{
		return this->name;
	}
	int District::getId()const
	{
		return this->id;
	}
	float District::getPresentOfVoters()const
	{
		return this->presentOfVoters;
	}
	int District::getCountVotes()const
	{
		return this->countVotes;
	}
	CList* District::getAllowedVotersList()const
	{
		return this->allowedVoters;
	}
	CList* District::getElectedList()const
	{
		return this->elected;
	}
	int District::getAmountOfRep()const
	{
		return this->amountOfRep;
	}

	//Setter
	bool District::setName(char* name)
	{
		if (this->name != nullptr)
		{
			delete[] this->name;
		}
		copyStr(&(this->name), name);
		return true;
	}

	bool District::setPresentOfVoters(float POV)
	{
		this->presentOfVoters = POV;
		return true;
	}
	bool District::setAllowedVotersList(CList* lst)
	{
		this->allowedVoters = lst;
		return true;
	}
	bool District::setElectedList(CList* lst)
	{
		this->elected = lst;
		return true;
	}

	bool District::setAmountOfRep(int aor)
	{
		this->amountOfRep = aor;
		return true;
	}

	bool District::increaseVoteCountByOne()
	{
		(this->countVotes)++;
		return true;
	}

	bool District::printAddToElected(CList* candidates, int x)
	{/////////////////////////////////////////////////////////////////////////////////////
		int i = 0;
		CNode* curr = candidates->getHead();
		if (curr == nullptr)
		{
			cout << "NO CANDIDATES!" << endl;
		}
		while (i < x && curr != nullptr)
		{
			this->elected->addToTail(curr->getInfo());
			cout << curr->getInfo()->getName() << " ";
			i++;
			curr = curr->getNext();
		}
		if (i == x)
			return true;
		return false;
	}

	ostream& operator<<(ostream& os, District& d)
	{
		os << d.getId() << " - Name: " << d.getName() << ", amount of representative: " << d.getAmountOfRep() << endl;
		return os;
	}

	bool District::save(ofstream& outfile)const
	{
		int nLen = strlen(name);
		outfile.write(reinterpret_cast<const char*>(&nLen), sizeof(int));
		outfile.write(name, sizeof(char) * nLen);
		outfile.write(reinterpret_cast<const char*>(&id), sizeof(int));
		outfile.write(reinterpret_cast<const char*>(&amountOfRep), sizeof(int));
		outfile.write(reinterpret_cast<const char*>(&presentOfVoters), sizeof(float));
		//allowedVoters->serialSave(outfile);
		//elected->serialSave(outfile);
		outfile.write(reinterpret_cast<const char*>(&countVotes), sizeof(int));
		return outfile.good();
	}
	bool District::pSerialSave(ofstream& outfile)const
	{
		if(!allowedVoters->serialSave(outfile))
			return false;
		return elected->serialSave(outfile);
	}

}