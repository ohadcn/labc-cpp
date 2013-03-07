/**
 * file:Exround.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 3 in c++ course.
 */
#ifndef EXROUND_H
#define EXROUND_H

/**
 * file: Exround.h
 * methods:
 * double ExRound(double num) - round num to the 3rd digit after the point
 *
 * defines:
 * EPSILON - this defines a little number, so number under it should be treated as zeroes.
 */

#define EPSILON .001

double ExRound(double num);

#endif // EXROUND_H
