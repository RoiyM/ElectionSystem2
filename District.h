#pragma once
#include"CList.h"
#include<iostream>
//
using namespace std;
namespace hw2 {
	class District
	{
	private:
		static int countId;
		char* name;
		int id;
		int amountOfRep;
		float presentOfVoters;
		CList* allowedVoters;
		CList* elected;
		int countVotes; //how many citizen voted in the district

	public:
		District(char* name, int amountOfRep);
		District(const District& other);
		District(ifstream& infile);
		virtual ~District();
		friend ostream& operator<<(ostream& os, District& d);
		const District& operator=(const District& other);

		//Getter
		const char* getName()const;
		int getId()const;
		float getPresentOfVoters()const;
		int getAmountOfRep()const;
		int getCountVotes()const;
		CList* getAllowedVotersList()const;
		CList* getElectedList()const;

		//Setter
		bool setName(char* name);
		bool setAmountOfRep(int aor);
		bool setPresentOfVoters(float POV);
		bool setAllowedVotersList(CList* lst);
		bool setElectedList(CList* lst);
		bool increaseVoteCountByOne();

		bool printAddToElected(CList* candidates, int x);

		virtual bool save(ofstream& outfile)const;
		bool pSerialSave(ofstream& outfile)const;

	};
}


