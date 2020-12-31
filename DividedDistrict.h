#pragma once
#include "District.h"
//
namespace hw2 {
	class DividedDistrict : public District
	{
	public:
		DividedDistrict(char* name, int amountOfRep);
		DividedDistrict(ifstream& infile);
		friend ostream& operator<<(ostream& os, DividedDistrict& d)
		{
			os << "DividedDistrict: " << d.getId() << " - Name: " << d.getName() << ", amount of representative: " << d.getAmountOfRep() << endl;
			return os;
		}
		bool save(ofstream& outfile)const;
	};
}