/**
 * file:GrahamScan.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 1 in c++ course.
 */

#ifndef GRAHAMSCAN_H
#define GRAHAMSCAN_H

#include "PointList.h"

//GrahamScan.h

/**
 * this header file contain one method, getConvexHull, this method get a PointList that represent a graph
 * and returns the convex hull of the graph.
 */

PointList *getConvexHull(PointList *graph);

#endif // GRAHAMSCAN_H
