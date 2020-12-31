#pragma once
#include "District.h"
//
namespace hw2 {
	class UnifiedDistrict : public District
	{
	public:
		UnifiedDistrict(char* name, int amountOfRep);
		UnifiedDistrict(ifstream& infile);
		friend ostream& operator<<(ostream& os, UnifiedDistrict& d)
		{
			os << "UnifiedDistrict: " << d.getId() << " - Name: " << d.getName() << ", amount of representative: " << d.getAmountOfRep() << endl;
			return os;
		}
		bool save(ofstream& outfile)const;
	};
}


