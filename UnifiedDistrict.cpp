#include "UnifiedDistrict.h"
namespace hw2 {
	UnifiedDistrict::UnifiedDistrict(char* name, int amountOfRep):District(name, amountOfRep)
	{
	}
	UnifiedDistrict::UnifiedDistrict(ifstream& infile) : District(infile)
	{
	}
	bool UnifiedDistrict::save(ofstream& outfile)const
	{
		int type = 1;
		outfile.write(reinterpret_cast<const char*>(&type), sizeof(int));
		return District::save(outfile);
		return true;
	}
}