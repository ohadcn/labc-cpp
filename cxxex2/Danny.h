/**
 * file:Danny.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#ifndef DANNY_H
#define DANNY_H

#include "College.h"

/**
 * @brief The Danny class
 * represent a candidate that is a graduate of Danny College
 * 
 * public constructor: get three parameters, all equivalent to Candidate constructor
 * has only methods inherited from Candidate, defining all the abstract members of it.
 */

class Danny:public College
{
public:
	Danny(long,double,double,double);
    virtual ~Danny();
    
protected:
	virtual std::string instituteName() const;	
    virtual double getAverageOfInstitute() const;
	virtual double factor() const;
	
private:
	static int s_counter;
	static double s_sumGrades;
};

#endif // DANNY_H
