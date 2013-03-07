/**
 * file:Colin.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#include "Colin.h"

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class Colin.
// --------------------------------------------------------------------------------------

#define COLIN_FACTOR -10
#define COLIN_NAME "Colin"

int Colin::s_counter=0;
double Colin::s_sumGrades=0;

Colin::Colin(long id, double grades, double salary,double projectGrade):College(id,grades,salary,projectGrade)
{
	s_counter++;
	s_sumGrades+=grades;
	
	#ifdef I_AM_REFERENCE_GRADE
		setReferenceGrade(getAverageOfInstitute());
	#endif
}

Colin::~Colin()
{
    s_counter--;
    s_sumGrades-=getGrade();
    #ifdef I_AM_REFERENCE_GRADE
        setReferenceGrade(getAverageOfInstitute());
    #endif
}

double Colin::getAverageOfInstitute() const
{
	return s_sumGrades/s_counter;
}

double Colin::factor() const
{
	return COLIN_FACTOR;
}

string Colin::instituteName() const
{
	return COLIN_NAME;
}
