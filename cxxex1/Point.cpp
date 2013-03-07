/**
 * file:Point.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 1 in c++ course.
 */

#include <iostream>
#include <math.h>
#include "Point.h"

using namespace std;

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class Point.
// --------------------------------------------------------------------------------------


Point::Point(long x, long y):_x(x),_y(y)
{
}

// Access methods
long Point::getX() const
{
	return _x;
}
long Point::getY() const
{
	return _y;
}

//comparision methods & operators
bool Point::operator ==(const Point &other) const
{
    return isEqual(other);
}

bool Point::operator !=(const Point &other) const
{
    return !isEqual(other);
}

bool Point::operator >(const Point &other) const
{
    return (getX()>other.getX())||
            ((getX()==other.getX())&&(getY()>other.getY()));
}

bool Point::operator <(const Point &other) const
{
    return other > *this;
}

bool Point::isEqual(const Point &other) const
{
	return (getY()==other.getY()&&getX()==other.getX());
}

// Other methods
ostream &operator <<(ostream &out,Point const &p)
{
    out << p.getX() << "," << p.getY() << endl;
    return out;
}

istream &operator >>(istream &in, Point **p)
{
    long x,y;
    char delimeter;
    
    //i skiped the delimeter char checking, as it doesn't metter, and we asked to assume legall input
    in>>x>>delimeter>>y;
    *p=new Point(x,y);
    return in;
}
