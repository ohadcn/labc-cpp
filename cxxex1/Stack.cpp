/**
 * file:Stack.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 1 in c++ course.
 */

#include "Stack.h"
#include <iostream>

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class Stack.
// --------------------------------------------------------------------------------------

Stack::Stack():PointList(false)
{
}

void Stack::push(Point *p)
{
    Add(p);
}

Point* Stack::peek()
{
    if(size()==0)
    {
        return NULL;
    }
    return operator [](size()-1);
}

int Stack::size()
{
    return ((PointList*)this)->size();
}

Point* Stack::underPeek()
{
    if(size()<=1)
    {
        return NULL;
    }
    return operator [](size()-2);
}

Point* Stack::pull()
{
    Point* result=peek();
    removeLast();
    return result;
}
