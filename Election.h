#pragma once
#include"PList.h"
#include"CList.h"
#include"DList.h"
#include"Helper.h"
//
namespace hw2 {
	class Election
	{
	private:
		Date date;
		int amountOfCitizens;
		CList* voterBook;
		int amountOfDistricts;
		DList* districts;
		int amountOfParties;
		PList* parties;

		void freeCitizens();
		void freeParties();
		void freeDistricts();

		Citizen* findCitizenById(int id);

		Party* findPartyById(int id);
		PNode* findPNodeyById(int id);

		District* findDistrictById(int id);
		DNode* findDNodeById(int id);

		void increaseTotalPartyVotes(int partyId);
		void increasePartyVotesInDistrict(int partyId, int districtId);

		PNode** makeSortedPartiesArray(PList* pLst);

		void printParties(PList* lst, District* district);

		Party* findMaxVotes(int districtId);

		static void merge(PNode* arr[], int start, int mid, int end);
		static void mergeSort(PNode* arr[], int l, int r);

		bool setPC(ifstream& infile);
		bool setPD(ifstream& infile);
		bool setPP(ifstream& infile);
		
		
	public:
		
		Election(Date& date);
		Election(ifstream& infile);
		virtual ~Election();
		virtual bool addDistrict(const char* name, int numOfRep, int districtType);// 1
		virtual bool addCitizen(char* name, int id, int YOB, int DId);// 2
		virtual bool addParty(char* name, int candidId);// 3
		virtual bool addCitizenAsPartyCandid(int candidId, int partyId, int DId);// 4
		virtual void display(int x);// 5, 6, 7
		virtual bool vote(int id, int partyId);//8
		virtual void displayResult();//9
		virtual bool save(const char* name) const;//11
		bool setP(ifstream& infile);

	protected:
		virtual bool saveE(ofstream& outfile) const;//11

	};
}