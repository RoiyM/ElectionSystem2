#pragma once
#include"CandidPerDistrictList.h"
#include"Citizen.h"
#include<iostream>
using namespace std;
namespace hw2 {
	class Party
	{
	private:
		static int countId;
		char* name;
		int id;
		int amountOfElectors; //how many seats in the knesset
		Citizen* candid;
		CandidPerDistrictList* candidPerDistrict;

	public:
		Party(char* name, Citizen* candid, int amountOfDistricts);
		Party(ifstream& infile);
		Party(const Party& other);

		~Party();
		friend ostream& operator<<(ostream& os, const Party& p);
		const Party& operator=(const Party& other);

		//Getters
		const char* getName()const;
		const Citizen* getCandid()const;
		int getId()const;
		CandidPerDistrictList* getCandidPerDistrictList()const;
		CList* getDistrictCandidates(int districtId);
		int getAmountOfElectors()const;

		//Setters
		bool setCandid(Citizen* candid);
		bool setCandidPerDistrict(CandidPerDistrictList* candidPerDistrict);
		bool addElectors(int num);
		bool addCandidToDistrict(Citizen* candid, int DId);

		bool save(ofstream& outfile)const;
		bool serialSave(ofstream& outfile)const;
		bool pSerialSave(ofstream& outfile)const;
	};
}