/**
 * file:College.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#include "College.h"

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class College.
// --------------------------------------------------------------------------------------

#define PROJECT_WIGHT (0.6)
#define GRADES_WIGHT (1-PROJECT_WIGHT)

College::College(long id, double grades, double salary,double projectGrade):Candidate(id,grades,salary),
                                                                                _projectGrade(projectGrade)
{
}

College::~College()
{
}

double College::getWorth() const
{
	return PROJECT_WIGHT*getProjecGrade()+GRADES_WIGHT*(getReferenceGrade()/getAverageOfInstitute())*getGrade()
                                                                                                     +factor();
}

double College::getProjecGrade()const
{
	return _projectGrade;
}

void College::print() const
{
	std::cout<<"ID: "<<this->getID()<<" |college: "<<this->instituteName()<<" |average: "
			   <<this->getGrade()<<" |project: "<<this->getProjecGrade()<<" |worth: "
			   <<this->getWorth()<<std::endl;
}
