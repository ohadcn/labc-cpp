/**
 * file:Bob.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#include "Bob.h"

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class Bob.
// --------------------------------------------------------------------------------------

#define BOB_FACTOR 7
#define BOB_NAME "Bob"

int Bob::s_counter=0;
double Bob::s_sumGrades=0;

Bob::Bob(long id, double grades, double salary):University(id,grades,salary)
{   
	 s_counter++;
	 s_sumGrades+=grades;
	 
	 #ifdef I_AM_REFERENCE_GRADE
		 setReferenceGrade(getAverageOfInstitute());
	 #endif
}

Bob::~Bob()
{
    s_counter--;
    s_sumGrades-=getGrade();
    #ifdef I_AM_REFERENCE_GRADE
        setReferenceGrade(getAverageOfInstitute());
    #endif
}

string Bob::instituteName() const
{
	return BOB_NAME;
}

double Bob::getAverageOfInstitute() const
{
	return s_sumGrades/s_counter;
}

double Bob::factor() const
{
	return BOB_FACTOR;
}
