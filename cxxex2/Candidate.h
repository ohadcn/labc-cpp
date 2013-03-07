/**
 * file:Candidate.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <iostream>

using namespace std;

/**
 * @brief The Candidate class
 * represent a Candidate for work.
 * this class is an abstract class: you can't initiate an instance of it & you can only inherite it.
 *
 * public methods:
 * constructor: get three parameters, the ID of the candidate (long), his grades average & his demanded salary.
 * destructor.
 * getSalary() - returns the salary required by the candidate
 * getGrade() - returns the grade of the candidate
 * getID() - returns the ID of the candidate
 *
 * abstract public members:
 * instituteName() - returns the name of the institute the candidate did gradute in.
 * print() - prints all the information about the candidate to std::cout
 * getWorth() - get a revised version of the grades for a candidate, this version also taking acount for the 
 * the institute the candidate graduate, other ingredients of the grade etc.
 *
 * protected methods:
 * getReferenceGrade() - returns the average grade of the institute all grade should be factorized for.
 * if setReferenceGrade() was called - returns the value it sets, otherwise returns DEFAULT_REF_GRADE
 * setReferenceGrade(int) - set the grade to factorize all the grades for.
 *
 * protected abstract methods:
 * getAverageOfInstitute() - returns the average grade in the institute the candidate graduated.
 * factor() - returns the factorizing for the institute the candidate graduated, this factor represent the
 * prestige of that institute and the quality of students graduating there.
 */

class Candidate
{
public:
	Candidate(long,double,double);
	virtual ~Candidate();
	double getSalary() const;
	double getGrade() const;
	long getID() const;
	virtual std::string instituteName() const =0;
	virtual void print() const =0;
    virtual double getWorth() const = 0;
	
protected:
	double getReferenceGrade() const;
	static void setReferenceGrade(double);
	virtual double getAverageOfInstitute() const =0;
	virtual double factor() const =0;
	
private:
	static double _referenceGrade;
	const long _id;
	const double _grade;
	const double _salary;
};

#endif // CANDIDATE_H
