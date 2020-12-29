#pragma once
#include "Election.h"
namespace hw2{
	class SimpleElection : public Election
	{
	public:
		SimpleElection(Date date, int numOfElectors);
		SimpleElection(ifstream& infile);
		bool addDistrict(const char* name, int numOfRep);
		bool addCitizen(char* name, int id, int YOB, int DId);
		bool addCitizenAsPartyCandid(int candidId, int partyId, int DId);
		void display(int x);
		bool save(const char* name) const;
	};

}