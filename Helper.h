#pragma once
using namespace std;
namespace hw2 {
	struct Date {
		int day, month, year;// date of the elections
	};
	int strlen(const char* str);
	void copyStr(char** pDest, const char* src);
}