/**
 * file:GrahamScan.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 1 in c++ course.
 */

#include <assert.h>
#include "GrahamScan.h"
#include "Point.h"
#include "PointList.h"
#include "Stack.h"

/**************************************************************
 * this file contains the implementation of getConvexHull()
 * method and all it's helper methods and classes
 **************************************************************/

//*************************************************************
//enums

//DIRECTION enum
typedef enum DIRECTION 
{
    RIGHT, STRAIGHT, LEFT
    
}DIRECTION;


//***************************************************************
//helper methods

//whichDirection method
static DIRECTION whichDirection(const Point *left, const Point *center, const Point *right)
{
    assert(left!=NULL && center != NULL && right!= NULL);
    long stat = (left->getX()-center->getX())*(center->getY()-right->getY())-
            (left->getY()-center->getY())*(center->getX()-right->getX());
    
    if(stat==0)
    {
        return STRAIGHT;
    }
    else if(stat>0)
    {
        return RIGHT;
    }
    return LEFT;
}

//**************************************************************
//classes

//ByAngle class
class ByAngle:public PointComperator
{
public:
    ByAngle(Point *rel):_rel(rel)
    {
        assert(rel!=NULL);
    }
    int compare(Point* a,Point* b)
    {
        assert(a!=NULL && b!= NULL);
        switch (whichDirection(a,_rel,b)) 
        {
        case RIGHT:
            return 1;
            break;
        case LEFT:
            return -1;
            break;
        case STRAIGHT:
            return 0;
            break;
        default:
            break;
        }
        return 0;
    }
    
private:
    Point* _rel;
};

//compByPos class
class compByPos:public PointComperator
{
public:
    compByPos()
    {
    }

   virtual int compare(Point* a,Point* b)
    {
        assert(a!=NULL && b!= NULL);
        return (((*a)>(*b))?-1:1);
    }    
};

//*****************************************************************
//getConvexHull() method
PointList* getConvexHull(PointList *graph)
{
    assert(graph!=NULL);
    int min=graph->getMin();
    ByAngle comparision((*graph)[min]);
    Stack *hull=new Stack();
    compByPos byPos;    
    PointList *result=new PointList(false);
    if(graph->size()<=3)
    {
            delete hull;
            for(int i=0;i<graph->size();i++)
            {
                result->Add((*graph)[i]);
            }
            result->sort(&byPos);
            return result;
    }
    graph->sort(&comparision);
    hull->push((*graph)[0]);
    hull->push((*graph)[1]);
    for(int i=2;i<graph->size();i++)
    {
        while(whichDirection(hull->underPeek(),hull->peek(),(*graph)[i])==RIGHT && hull->size()>2)
        {
            hull->pull();
        }
        hull->push((*graph)[i]);
    }
    while(hull->size())
    {
        result->Add(hull->pull());
    }
    delete hull;
    result->sort(&byPos);
    return result;
}
