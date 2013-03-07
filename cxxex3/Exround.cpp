/**
 * file:Etc.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 3 in c++ course.
 */
#include <cmath>

// --------------------------------------------------------------------------------------
// This file contains the implementation of the method ExRound.
// --------------------------------------------------------------------------------------

#define ROUND 1000.0

double ExRound(double num)
{
	//round keeps -0.0 as negative, while we need to change it...
	return floor(num*ROUND+.5)/ROUND;
}
