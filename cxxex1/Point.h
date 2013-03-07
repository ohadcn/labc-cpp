/**
 * file:Point.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 1 in c++ course.
 */

#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

// Point.h

/**
 * @brief The Point class
 * represent a point in 2D plane
 * methods:
 * constractor: Point(long,long)
 * getX, getY - returns the X/Y coordinates of the point
 * isEqual - compare two points, returns true iff both the coordinates of the two points are equal.
 *
 * operators:
 * <Point> == <Point> - the same as isEqual()
 * <Point> != <Point> - the opposite of isEqual()
 * <Point a> > <Point b> - compare two points, by x's than by y's, returns true iff a>b
 * 
 * <istream> >> <Point **a> - get a point from the stream, in format x,y
 * <ostream> << <Point a> - output point to a stream, in format x,y
 */

class Point
{
public:

	Point(long x,long y);

	long 	getX() const;
	long 	getY() const;

	bool	isEqual(const Point &other) const;

    //comparision operators
    bool operator==(const Point &other) const;
    bool operator>(const Point &other) const;
    bool operator<(const Point &other) const;
    bool operator!=(const Point &other) const;

private:
	long _x;
	long _y;

};

//input/output operators
ostream &operator <<(ostream &out,Point const &p);
istream &operator >>(istream &in,Point **p);

#endif
