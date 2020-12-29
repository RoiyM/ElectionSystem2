#include"Helper.h"
namespace hw2 {
	int strlen(const char* str)
	{
		int count = 0;
		while (str[count] != '\0')
		{
			count++;
		}
		return count;
	}

	void copyStr(char** pDest, const char* src)
	{
		char* dest = new char[strlen(src) + 1];
		int i = 0;
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		*pDest = dest;
	}

}