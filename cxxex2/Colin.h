/**
 * file:Colin.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#ifndef COLIN_H
#define COLIN_H

#include "College.h"

/**
 * @brief The Colin class
 * represent a candidate that is a graduate of Colin College
 * 
 * public constructor: get three parameters, all equivalent to Candidate constructor
 * has only methods inherited from Candidate, defining all the abstract members of it.
 */

class Colin:public College
{
public:
	Colin(long,double,double,double);
    virtual ~Colin();
    
protected:
	virtual std::string instituteName() const;	
    virtual double getAverageOfInstitute() const;
	virtual double factor() const;
	
private:
	static int s_counter;
	static double s_sumGrades;
};

#endif // COLIN_H
