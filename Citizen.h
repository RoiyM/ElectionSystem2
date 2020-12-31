#pragma once
#include<iostream>
//
using namespace std;
namespace hw2 {
	class District;
	class Citizen {
	private:
		char* name;
		int id;
		int yearOfBirth;
		District* district;
		bool voted;

	public:
		Citizen(char* name, int id, int YOB, District* district);
		Citizen(const Citizen& other);
		Citizen(ifstream& infile);
		~Citizen();
		friend ostream& operator<<(ostream& os, const Citizen& c);
		const Citizen& operator=(const Citizen& other);

		//Getters
		const char* getName()const;
		int getId()const;
		int getYearOfBirth()const;
		int getDistrictId()const;
		bool getVoted()const;
		
		//Setters
		bool setName(char* name);
		bool setDistrict(District* district);
		bool setVoted();
		
		bool save(ofstream& outfile)const;
		bool serialSave(ofstream& outfile)const;
		bool pSerialSave(ofstream& outfile)const;


	};
}