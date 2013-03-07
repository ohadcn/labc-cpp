/**
 * file:Alice.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#include "Alice.h"

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class Alice.
// --------------------------------------------------------------------------------------

#define ALICE_FACTOR 0
#define ALICE_NAME "Alice"

#define I_AM_REFERENCE_GRADE

int Alice::s_counter=0;
double Alice::s_sumGrades=0;

Alice::Alice(long id, double grade, double salary):University(id,grade,salary)
{
	s_counter++;
	s_sumGrades+=grade;
	
	#ifdef I_AM_REFERENCE_GRADE
		setReferenceGrade(getAverageOfInstitute());
    #endif
}

Alice::~Alice()
{
    s_counter--;
    s_sumGrades-=getGrade();
    #ifdef I_AM_REFERENCE_GRADE
        setReferenceGrade(getAverageOfInstitute());
    #endif
}

string Alice::instituteName() const
{
	return ALICE_NAME;
}

double Alice::getAverageOfInstitute() const
{
	return s_sumGrades/s_counter;
}

double Alice::factor() const
{
	return ALICE_FACTOR;
}
