/**
 * file:Danny.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#include "Danny.h"

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class Danny.
// --------------------------------------------------------------------------------------

#define DANNY_FACTOR -15
#define DANNY_NAME "Danny"

int Danny::s_counter=0;
double Danny::s_sumGrades=0;

Danny::Danny(long id, double grades, double salary,double projectGrade):College(id,grades,salary,projectGrade)
{
	s_counter++;
	s_sumGrades+=grades;
	
    #ifdef I_AM_REFERENCE_GRADE
        setReferenceGrade(getAverageOfInstitute());
    #endif
}

Danny::~Danny()
{
    s_counter--;
    s_sumGrades-=getGrade();
    
    #ifdef I_AM_REFERENCE_GRADE
        setReferenceGrade(getAverageOfInstitute());
    #endif
}

double Danny::getAverageOfInstitute() const
{
	return s_sumGrades/s_counter;
}

double Danny::factor() const
{
	return DANNY_FACTOR;
}

string Danny::instituteName() const
{
	return DANNY_NAME;
}
