/**
 * file:List.h
 * this file has been rewritten by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 * this file was originally written as PointList class for ex1, and had some changes (generics) for ex2
 */

#ifndef LIST_H
#define LIST_H

/**
 * @brief The List class
 * represent a list.
 * 
 * public members:
 *
 * List() - constractor, get an optional parameter, orig, setting this parameter to false tells the
 * class that you holds those objects by other structurs, so it has no need to delete them when it finished.
 *
 * ~List() - a destructor. also calls the destructor of the T objects if not told otherwise by constructor parameters.
 *
 * Add() - add an object to the list
 * size() - returns the number of elements in the list
 * <List>[int i] - operator returning a pointer to the i's object in the list.
 *
 */

template <class T>
class List
{
public:
	List(bool orig=true);
	~List();
	
	void Add(T *t_p);
	
	T* operator[](int index) const;
	
	int size() const;
	
private:
	int _arrSize;
	int _currentIndex;
	T **_list;
	const bool _isOrig;
	void enlargeList();
};


//since we are using templates, all the implemetation must be in here

#define RESIZE_FACTOR 2

#define STARTING_SIZE 10

template <class T>
List<T>::List(bool orig):_isOrig(orig)
{
	_arrSize=STARTING_SIZE;
	_currentIndex=0;
	_list=new T*[STARTING_SIZE];
}


template <class T>
List<T>::~List()
{
	if(_isOrig){
		for(int i=0;i<size();i++)
		{
			delete _list[i];
		}
	}
	delete [] _list;
}


template <class T>
void List<T>::Add(T *t_p)
{
	if(_currentIndex>=_arrSize)
	{
		enlargeList();
	}
	_list[_currentIndex++]=t_p;
}


template <class T>
T *List<T>::operator [](int index) const
{
	return _list[index];
}


template <class T>
int List<T>::size() const
{
	return _currentIndex;
}


template <class T>
void List<T>::enlargeList()
{
	T **temp=new T*[size()*RESIZE_FACTOR];
	for(int i=0;i<_currentIndex;i++)
	{
		temp[i]=_list[i];
	}
	delete [] _list;
	_list=temp; 
	_arrSize*=RESIZE_FACTOR;
}

#endif // LIST_H
