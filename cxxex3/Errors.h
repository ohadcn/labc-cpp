/**
 * file:Errors.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 3 in c++ course.
 */

#ifndef ERRORS_H
#define ERRORS_H

//for exit() & EXIT_FAILURE
#include <cstdlib> 

#define DEFAULT_ERROR_MESSAGE "Violation of matrix operation rules"

/**
 * file: Errors.h
 * this header has the method reportError()
 * this methods prints an error message and exits the program with EXIT_FAILURE or other user-defined exit code
 */

void reportError(const char *msg=DEFAULT_ERROR_MESSAGE, int errorCode=EXIT_FAILURE);

#endif // ERRORS_H
