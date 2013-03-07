/**
 * file:Candidate.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#include "Candidate.h"

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class Candidate.
// --------------------------------------------------------------------------------------

#include "Errors.h"

#define MIN_GRADE 55
#define MAX_GRADE 100

//the ex. desc don't tell us what this value should be, so I feel free to set it
#define DEFAULT_REF_GRADE 100

//initiate the reference grade for case there are no alice graduates
double Candidate::_referenceGrade =DEFAULT_REF_GRADE;

Candidate::Candidate(long id, double grades, double salary):_id(id),_grade(grades),_salary(salary)
{
	if(salary<0)
	{
		reportError("salary can't be negative\ndon\'t be so greedy");
	}

	if(grades>MAX_GRADE || grades<MIN_GRADE)
	{
		reportError("grade is not in range");
	}
}

Candidate::~Candidate()
{
}

double Candidate::getSalary() const
{
	return _salary;
}

double Candidate::getGrade() const
{
	return _grade;
}

long Candidate::getID() const
{
	return _id;
}

double Candidate::getReferenceGrade() const
{
	return _referenceGrade;
}

void Candidate::setReferenceGrade(double grade)
{
	_referenceGrade=grade;
}

