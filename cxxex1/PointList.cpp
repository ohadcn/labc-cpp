/**
 * file:PointList.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 1 in c++ course.
 */

#include <assert.h>
#include "PointList.h"
#include <exception>
#include "Point.h"

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class PointComperator.
// --------------------------------------------------------------------------------------

#define RESIZE_FACTOR 2
using namespace std;

PointList::PointList(bool orig)
{
    _arrSize=STARTING_SIZE;
    _currentIndex=0;
    _list=new Point*[STARTING_SIZE];
    _isOrig=orig;
}

PointList::~PointList()
{
    if(_isOrig){
        for(int i=0;i<size();i++)
        {
            delete _list[i];
        }
    }
    delete [] _list;
}

void PointList::Add(Point *p)
{
    if(_currentIndex>=_arrSize)
    {
        enlargeList();
    }
    _list[_currentIndex++]=p;
    
}

void PointList::enlargeList()
{
    Point **temp=new Point*[size()*RESIZE_FACTOR];
    for(int i=0;i<_currentIndex;i++)
    {
        temp[i]=_list[i];
    }
    delete [] _list;
    _list=temp; 
    _arrSize*=RESIZE_FACTOR;
}


Point* PointList::operator[](int index) const
{
    if(index>=size())
    {
        return NULL;
    }
    return _list[index];
}

int PointList::size() const
{
    return _currentIndex;
}

ostream& operator <<(ostream &out,PointList const &list)
{
    out<<"result"<<endl;
    for(int i=0;i<list.size();i++)
    {
        out<<*list[i];
    }
    return out;
}

PointList PointList::getFromUser()
{
    Point *temp;
    PointList list;
    while(cin>>&temp)
    {
        list.Add(temp);
    }

    //operator >> allocates memory even when fails on the last try
    delete temp;
    
    return list;
}

int PointList::getMin()
{
    int min=0;
    for(int i=0;i<size();i++)
    {
        if(*_list[min]>*_list[i])
        {
            min=i;
        }
    }
    return min;
}

void PointList::sort(PointComperator *compare)
{
    assert(compare != NULL);
    
    //see sort documentation
    swap(getMin(),0);
    quickSort(compare,1,size()-1);
}

void PointList::quickSort(PointComperator *compare, int start, int end)
{
    assert(compare != NULL && start >=0 && end<size());

    if(start>=end)
    {
            return;
    }
    
    //quick sort
    int k=start;
    int i;
    for(i=start;i<end;i++)
    {
        if(compare->compare(_list[i],_list[end])>0)
        {
            swap(i,k++);
        }
    }
    swap(k,end);
    quickSort(compare,start,k-1);
    quickSort(compare,k+1,end);
}

void PointList::swap(int i,int j)
{
    assert(i<size() && j<size());
    
    Point* temp=_list[i];
    _list[i]=_list[j];
    _list[j]=temp;
}

void PointList::removeLast()
{
    if(_currentIndex==0)
    {
        return;
    }
    
    _currentIndex--;
    
    if(_isOrig)
    {
        delete _list[_currentIndex];
    }
}

