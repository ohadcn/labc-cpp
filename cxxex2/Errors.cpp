/**
 * file:Errors.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#include "Errors.h"

// --------------------------------------------------------------------------------------
// This file contains the implementation of the method reportError.
// --------------------------------------------------------------------------------------

#include <iostream>

void reportError(const char *msg, int errorCode)
{
	std::cerr<<msg;
	exit(errorCode);
}
