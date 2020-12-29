#include "UnifiedDistrict.h"
namespace hw2 {
	UnifiedDistrict::UnifiedDistrict(char* name, int amountOfRep):District(name, amountOfRep)
	{
	}
	UnifiedDistrict::UnifiedDistrict(ifstream& infile) : District(infile)
	{
	}
	void UnifiedDistrict::save(ofstream& outfile)const
	{
		int type = 1;
		outfile.write(reinterpret_cast<const char*>(&type), sizeof(int));
		District::save(outfile);
	}
}