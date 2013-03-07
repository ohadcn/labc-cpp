/**
 * file:Bob.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#ifndef BOB_H
#define BOB_H

#include "University.h"

/**
 * @brief The Bob class
 * represent a candidate that is a graduate of Bob University
 * 
 * public constructor: get three parameters, all equivalent to Candidate constructor
 * has only methods inherited from Candidate, defining all the abstract members of it.
 */

class Bob:public University
{
public:
	Bob(long,double,double);
    virtual ~Bob();
    
protected:
	virtual std::string instituteName() const;	
    virtual double getAverageOfInstitute() const;
	virtual double factor() const;
	
private:
	static int s_counter;
	static double s_sumGrades;
	
};

#endif // BOB_H
