#include "SimpleElection.h"
namespace hw2 {
	SimpleElection::SimpleElection(Date date, int numOfElectors) :Election(date)
	{
		this->Election::addDistrict("UnitedDistricts", numOfElectors, 2);
	}
	SimpleElection::SimpleElection(ifstream& infile) : Election(infile)
	{
	}

	bool SimpleElection::addDistrict(const char* name, int numOfRep)
	{
		return false;
	}

	bool SimpleElection::addCitizen(char* name, int id, int YOB, int DId)
	{
		return this->Election::addCitizen(name, id, YOB, 0);
	}

	bool SimpleElection::addCitizenAsPartyCandid(int candidId, int partyId, int DId)
	{
		return this->Election::addCitizenAsPartyCandid(candidId, partyId, 0);
	}

	void SimpleElection::display(int x)
	{
		switch (x)
		{
		case 5:
			cout << "ERROR!" << endl;
			break;
		case 6:
			Election::display(6);
			break;
		case 7:
			Election::display(7);
			break;
		default:
			break;
		}
	}

	bool SimpleElection::save(const char* name) const
	{
		ofstream outfile(name, ios::binary | ios::trunc);
		if (!outfile) 
		{
			return false;
		}
		int type = 2;
		outfile.write(reinterpret_cast<const char*>(&type), sizeof(int)); //write the type
		if (!outfile.good())
			return false;
		if (!saveE(outfile))
			return false;
		outfile.close();
		return true;
	}
}