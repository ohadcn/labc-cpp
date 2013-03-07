/**
 * file:PointComperator.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 1 in c++ course.
 */

#ifndef POINTCOMPERATOR_H
#define POINTCOMPERATOR_H


#include "Point.h"


/**
 * @brief The PointComperator class
 * an abstract class, for comparing two points.
 * methods:
 * PointComperator() - constractor
 * compare() - this method should get two points and compare them, returning negative integer iff the first one is
 * bigger and a positive otherwise
 */


class PointComperator
{
public:
    PointComperator();
    virtual int compare(Point*,Point*)=0;
};

#endif // POINTCOMPERATOR_H
