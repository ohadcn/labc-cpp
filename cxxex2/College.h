/**
 * file:College.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#ifndef COLLEGE_H
#define COLLEGE_H

#include "Candidate.h"

/**
 * @brief The College class
 * represent an academic institute such as a college.
 * this class is an abstract class.
 * this class inherites the Candidate class.
 *
 * public methods:
 * getProjecGrade() - return the grade the cadidate got for his project.
 *
 * virtual methods of Candidate implemented:
 * print()
 * getWorth()
 *
 * virtual methods of Candidate not implemented and need to be implemented by inheriting classes:
 * instituteName()
 * getAverageOfInstitute()
 * factor()
 */

class College:public Candidate
{
public:
	College(long,double,double,double);
	virtual ~College();
	
	virtual double getWorth() const;
	double getProjecGrade() const;
	virtual void print() const;

private:
	const double _projectGrade;
};

#endif // COLLEGE_H
