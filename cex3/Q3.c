/**
 * file: Q3.c
 * written for ex. 3 in labc course, by Ohad Cohen <ohadcn@cs.huji.ac.il>
 * contains methods for finding substring
 */

#include <string.h>

#define NOT_FOUND -1

#define END_OF_STRING '\0'

/**
 * this method returns the index of str2 in str1
 * parameters:
 * isCyclic: set this to true (non-zero) to allow cyclic substring
 * step: the step the substring appear in, set this to 1 for normal substring look
 * str1: the string to look in
 * str2: the string to look for
 */
int findSubStr(const int isCyclic,const int step, const char* str1, const char* str2)
{
	int str1size=strlen(str1);
	int str1Index,str2Index,i;

	for(i=0;i<str1size;i++)
	{
		str1Index=i;
		str2Index=0;
		while(str1[str1Index]==str2[str2Index])
		{
			str2Index++;
			str1Index+=step;
			if(str2[str2Index]==END_OF_STRING)
			{
				return i;
			}

			if(isCyclic)
			{
				str1Index %=str1size;
			}
			else if(str1Index>=str1size)
				{
					break;
				}

		}
	}
	return NOT_FOUND;
}

/**
 * this method returns the index of the first occurance of a substring in a string
 * this method do not demand the substring to appear continious, this means any number of characters can be
 * between two following characters in the substring, and the number can be varing
 * parameters:
 * str1: the string to look in
 * str2: the string to look for
 */
int findSubStrAnyStep(const char* str1, const char* str2)
{
	int str1size=strlen(str1);
	int str1Index,str2Index=0;
	//the index of the first character in str1
	int startIndex=-1;
	for(str1Index=0;str1Index<str1size;str1Index++)
	{
		if(str1[str1Index]==str2[str2Index])
		{
			if(!str2Index)
			{
				startIndex=str1Index;
			}

			str2Index++;
			if(str2[str2Index]==END_OF_STRING)
			{
				return startIndex;
			}
		}
	}
	return NOT_FOUND;
}

/**
 * this method returns the index of str2 in str1
 * parameters:
 * isCyclic: set this to true (non-zero) to allow cyclic substring
 * step: the step the substring appear in, set this to 1 for normal substring look
 * setting step to zero enables varing step size
 * str1: the string to look in
 * str2: the string to look for
 */
int extendedSubStr(const int isCyclic,const int step, const char* str1, const char* str2)
{
	if(step)
	{
		return findSubStr(isCyclic,step,str1,str2);
	}
	else
	{
		return findSubStrAnyStep(str1,str2);
	}
}
