/**
 * file:Stack.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 1 in c++ course.
 */

#ifndef STACK_H
#define STACK_H

#include "Point.h"
#include "PointList.h"

/**
 * @brief The Stack class
 * this class represent a stack of points
 *
 * public members:
 * Stack() - a constructor
 * pull() - returns a pointer to the head of the stack, and removes it from the stack.
 * peek() - returns a pointer to head of the stack.
 * underpeek() - returns a pointer to the point after the head of the stack.
 * push() - put a point in the stack
 * size() - returns the number of the points in the stack.
 */
class Stack :private PointList
{
public:
    Stack();
    Point *pull();
    Point *peek();
    Point *underPeek();
    void push(Point *p);
    int size();
};

#endif // STACK_H
