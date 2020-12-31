#include "DividedDistrict.h"
//
namespace hw2 {
	DividedDistrict::DividedDistrict(char* name, int amountOfRep):District(name, amountOfRep)
	{
	}
	DividedDistrict::DividedDistrict(ifstream& infile):District(infile)
	{
	}

	bool DividedDistrict::save(ofstream& outfile)const
	{
		int type = 2;
		outfile.write(reinterpret_cast<const char*>(&type), sizeof(int));
		return District::save(outfile);
		return true;
	}

}