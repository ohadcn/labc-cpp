/**
 * file:PointList.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 1 in c++ course.
 */

#ifndef POINTLIST_H
#define POINTLIST_H

#include <iostream>
#include "Point.h"
#include "PointComperator.h"

using namespace std;


/**
 * @brief The PointList class
 * represent a list of points.
 * 
 *
 * public members:
 *
 * PointList() - constractor, get an optional parameter, orig, setting this parameter to false tells the
 * class that you holds those points by other structurs, so it has no need to delete them when it finished.
 *
 * ~PointList() - a destructor. also calls the destructor of points if not told otherwise by constructor parameters.
 *
 * Add() - add a point to the list
 * size() - returns the number of elements in the list
 * sort() - sort the list using a givven comperator. this method put the minimum (see getMin) as the first 
 * and only than use the given comparing method.
 * getMin() - returns the index of the minimal point in this list.
 * <PointList>[int i] - operator returning a pointer to the i's point in the list.
 * <ostream> << <PointList> - output the PointList to a stream, this will output "result\n" and than all the
 * points that are in the list.
 *
 * static members:
 * getFromUser() - gets list of points from the standard input.
 *
 * protected members:
 * removeLast() - remove the last point in the list
 *
 */

#define STARTING_SIZE 10

class PointList
{
public:
    PointList(bool orig=true);
    ~PointList();
    
    void Add(Point *p);
            
    Point* operator[](int index) const;
    
    int size() const;
    
    void sort(PointComperator *compare);
    int getMin();
    
    static PointList getFromUser();
    
protected:
    void removeLast();
    
private:
    void swap(int i, int j);
    void quickSort(PointComperator *compare, int start, int end);
    int _arrSize;
    int _currentIndex;
    Point **_list;
    void enlargeList();
    bool _isOrig;
};

ostream& operator <<(ostream &out,PointList const &p);
//PointList getFromUser();

#endif // POINTLIST_H
