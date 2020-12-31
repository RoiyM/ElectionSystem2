#include "Citizen.h"
#include "Helper.h"
#include "District.h"
//
namespace hw2 {
	Citizen::Citizen(char* name, int id, int YOB, District* district) :id(id), yearOfBirth(YOB), voted(false), district(district)
	{
		copyStr(&(this->name), name);
	}

	Citizen::Citizen(const Citizen& other)
	{
		(*this) = other;
	}

	Citizen::Citizen(ifstream& infile)
	{
		int nLen;
		infile.read(reinterpret_cast<char*>(&nLen), sizeof(int));
		this->name = new char[nLen + 1];
		infile.read(this->name, sizeof(char) * nLen);
		this->name[nLen] = '\0';
		infile.read(reinterpret_cast<char*>(&id), sizeof(int));
		infile.read(reinterpret_cast<char*>(&yearOfBirth), sizeof(int));
		this->district = nullptr;
		infile.read(reinterpret_cast<char*>(&voted), sizeof(bool));
	}
	Citizen::~Citizen()
	{
		delete[] name;
	}

	const Citizen& Citizen::operator=(const Citizen& other)
	{
		if (this != &other)
		{
			delete[] this->name;
			copyStr(&(this->name), other.name);
			this->id = other.id;
			this->yearOfBirth = other.yearOfBirth;
			this->district = other.district;
			this->voted = other.voted;
		}
		return *this;
	}

	//Getters
	const char* Citizen::getName()const
	{
		return this->name;
	}
	int Citizen::getId()const
	{
		return this->id;
	}
	int Citizen::getYearOfBirth()const
	{
		return this->yearOfBirth;
	}
	int Citizen::getDistrictId()const
	{
		return this->district->getId();
	}
	bool Citizen::getVoted()const
	{
		return this->voted;
	}


	//Setters
	bool Citizen::setName(char* name)
	{
		if (this->name != nullptr)
		{
			delete[] this->name;
		}
		copyStr(&(this->name), name);
		return true;
	}

	bool Citizen::setDistrict(District* district)
	{
		this->district = district;
		return true;
	}

	bool Citizen::setVoted()
	{
		this->voted = true;
		return true;
	}

	ostream& operator<<(ostream& os, const Citizen& c)
	{
		os << c.getName() << " - ID: " << c.getId() << ", year of birth: " << c.getYearOfBirth() << ", district id: " << c.getDistrictId() << endl;
		return os;
	}

	bool Citizen::save(ofstream& outfile)const
	{
		int nLen = strlen(name);
		outfile.write(reinterpret_cast<const char*>(&nLen), sizeof(int));
		outfile.write(name, sizeof(char) * nLen);
		outfile.write(reinterpret_cast<const char*>(&id), sizeof(int));
		outfile.write(reinterpret_cast<const char*>(&yearOfBirth), sizeof(int));
		//int dId = district->getId(); //write the district id of the citizen
		//outfile.write(reinterpret_cast<const char*>(&dId), sizeof(int));
		outfile.write(reinterpret_cast<const char*>(&voted), sizeof(bool));
		return outfile.good();
	}
	bool Citizen::serialSave(ofstream& outfile)const
	{
		outfile.write(reinterpret_cast<const char*>(&id), sizeof(int));
		return outfile.good();
	}
	bool Citizen::pSerialSave(ofstream& outfile)const
	{
		int dId = this->district->getId();
		outfile.write(reinterpret_cast<const char*>(&dId), sizeof(int));
		return outfile.good();
	}
}