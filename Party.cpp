#include"Party.h"
#include"Helper.h"
namespace hw2 {
	int Party::countId = 0;

	Party::Party(char* name, Citizen* candid, int amountOfDistricts) :id(countId), candid(candid), amountOfElectors(0)
	{
		countId++;
		copyStr(&(this->name), name);
		this->candidPerDistrict = new CandidPerDistrictList(amountOfDistricts);
	}
	Party::Party(const Party& other)
	{
		*this = other;
	}
	Party::Party(ifstream& infile)
	{
		int nLen;
		infile.read(reinterpret_cast<char*>(&nLen), sizeof(int));
		this->name = new char[nLen + 1];
		infile.read(this->name, sizeof(char) * nLen);
		this->name[nLen] = '\0';
		infile.read(reinterpret_cast<char*>(&id), sizeof(int));
		infile.read(reinterpret_cast<char*>(&amountOfElectors), sizeof(int));
		this->candid = nullptr;
		candidPerDistrict = nullptr;
	}

	Party::~Party()
	{
		delete[]name;
		delete candidPerDistrict;
	}

	const Party& Party::operator=(const Party& other)
	{
		if (this != &other)
		{
			delete[] this->name;
			copyStr(&(this->name), other.name);
			this->id = other.id;
			this->amountOfElectors = other.amountOfElectors;
			this->candid = other.candid;
		}
		return *this;
	}


	//Getters
	const char* Party::getName()const
	{
		return this->name;
	}
	const Citizen* Party::getCandid()const
	{
		return this->candid;
	}
	int Party::getId()const
	{
		return this->id;
	}
	CandidPerDistrictList* Party::getCandidPerDistrictList()const
	{
		return this->candidPerDistrict;
	}

	int Party::getAmountOfElectors()const
	{
		return this->amountOfElectors;
	}

	CList* Party::getDistrictCandidates(int districtId)
	{
		CPDNode* curr = this->candidPerDistrict->getHead();
		int i = 0;
		while (curr != nullptr && i < districtId)
		{
			i++;
			curr = curr->getNext();
		}
		return curr->getListOfCandidates();
	}

	//Setters
	bool Party::setCandid(Citizen* candid)
	{
		this->candid = candid;
		return true;
	}
	bool Party::setCandidPerDistrict(CandidPerDistrictList* candidPerDistrict)
	{
		this->candidPerDistrict = candidPerDistrict;
		return true;
	}
	bool Party::addElectors(int num)
	{
		(this->amountOfElectors) += num;
		return true;
	}

	bool Party::addCandidToDistrict(Citizen* candid, int DId)
	{
		CPDNode* curr = this->candidPerDistrict->getHead();
		for (int i = 0; i < DId; i++)
		{
			curr = curr->getNext();
		}
		if (curr == nullptr)
			return false;
		curr->getListOfCandidates()->addToTail(candid);
		return true;
	}

	ostream& operator<<(ostream& os, const Party& p)
	{
		os << p.getId() << " - Name: " << p.getName() << ", Candidate for PM: " << p.getCandid()->getName() << "The Candidates are: " << p.getCandidPerDistrictList() << endl;
		return os;
	}

	void Party::save(ofstream& outfile)const
	{
		int nLen = strlen(name);
		outfile.write(reinterpret_cast<const char*>(&nLen), sizeof(int));
		outfile.write(name, sizeof(char) * nLen);
		outfile.write(reinterpret_cast<const char*>(&id), sizeof(int));
		outfile.write(reinterpret_cast<const char*>(&amountOfElectors), sizeof(int));
		//candid->serialSave(outfile);
		//candidPerDistrict->serialSave(outfile);
	}
	void Party::serialSave(ofstream& outfile)const
	{
		outfile.write(reinterpret_cast<const char*>(&id), sizeof(int));
	}
	void Party::pSerialSave(ofstream& outfile)const
	{
		candid->serialSave(outfile);
		candidPerDistrict->serialSave(outfile);
	}
}