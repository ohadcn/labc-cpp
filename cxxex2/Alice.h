/**
 * file:Alice.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#ifndef ALICE_H
#define ALICE_H

#include "University.h"

/**
 * @brief The Alice class
 * represent a candidate that is a graduate of Alice University
 * 
 * public constructor: get three parameters, all equivalent to Candidate constructor
 * has only methods inherited from Candidate, defining all the abstract members of it.
 */

class Alice:public University
{
public:
	Alice(long,double,double);
    virtual ~Alice();
    
protected:
	virtual std::string instituteName() const;	
    virtual double getAverageOfInstitute() const;
	virtual double factor() const;
	
private:
	static int s_counter;
	static double s_sumGrades;
	
};

#endif // ALICE_H
