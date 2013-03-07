/**
 * file:University.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "Candidate.h"

/**
 * @brief The University class
 * represent an academic institute such as a University.
 * this class is an abstract class.
 * this class inherites the Candidate class.
 * has only methods inherited from Candidate.
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

class University:public Candidate
{
public:
	University(long,double,double);
	virtual ~University();
	virtual double getWorth() const;
	virtual void print() const;
};

#endif // UNIVERSITY_H
