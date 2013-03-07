/**
 * file:ConvexHull.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 1 in c++ course.
 */

#include <iostream>
#include "Point.h"
#include "PointList.h"
#include "GrahamScan.h"
#include "Stack.h"

/**************************************************************
 * this file contains the main method of the ConvexHull prigram
 **************************************************************/


using namespace std;

int main()
{
    PointList points=PointList::getFromUser();
    PointList *convexHull=getConvexHull(&points);
    cout<<*convexHull;
    
    //points is not a pointer so it will be destroid automatically after program execution
    delete convexHull;
}
