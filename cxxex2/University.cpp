/**
 * file:University.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#include "University.h"

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class University.
// --------------------------------------------------------------------------------------

University::University(long id, double grades, double salary):Candidate(id,grades,salary)
{
}

University::~University()
{
}

void University::print() const
{
	cout<<"ID: "<<this->getID()<<" |univ: "<<this->instituteName()<<" |average: "<<this->getGrade()<<" |worth: "
																				<<this->getWorth()<<std::endl;
}

double University::getWorth() const
{
	return getGrade()*(getReferenceGrade()/getAverageOfInstitute())+factor();
}

