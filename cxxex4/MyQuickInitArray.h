/*
 * file: MyQuickInitArray.h
 * this file has been written by Ohad Cohen as part of ex. 4 in labc++ course.
 * this class is based on the class List<T> I wrote for ex2 in that course
 * which is generalization of the class PointList i built for ex1.
 *
 * this file contains the class MyQuickInitArray<typename T>, this class can be used as array, besides it can
 * guaranty initialization & access in O(1) or copy in O(n) (n - actual number of elements in the list)
 *
 * public constructors:
 * MyQuickInitArray(int n) - initialize a MyQuickInitArray of size n
 * keep in mind that after creation, you can't change the size of he array
 * this constructor has constant running time
 *
 * MyQuickInitArray(MyQuickInitArray old) - make a copy of old (deep copy)
 * the running times of this constructor is O(n), when n is number of elements actually in old
 *
 * destructor:
 * ~MyQuickInitArray() - destruct the object and free all the resources associated with it.
 * works on O(n), n- number of elements in the MyQuickInitArray
 *
 * public operators:
 * arr[int n] - get the n'th element in the array.
 * throws std::out_of_range if n is greater than the size of the array
 * works in O(1)
 *
 * const arr[int n] - get the n'th element in the array.
 * throws std::out_of_range if n is greater than the size of the array
 * returns DEFAULT_VALUE if the n'th element is not initialized in the array
 * works in O(1)
 *
 * = <MyQuickInitArray> - (placement operator) - put the content of another MyQuickInitArray into this
 * MyQuickInitArray, making a deep copy of all it's contents.
 * works on O(n+m), n- number of elements in the old array, m - number of elements in the new array.
 * 
 */

#ifndef MYQUICKINITARRAY_H
#define MYQUICKINITARRAY_H

#define MIN_SIZE 0
#define DEFAULT_VALUE 0

#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <iostream>


template <typename T>
class MyQuickInitArray
{

private:
	void initArrays(int size)
	{
		_A=(T**)calloc(sizeof(T*),size);
		if(_A==NULL)
		{
			throw new std::exception();
		}
		
		_B=(int*)calloc(sizeof(int),size);
		if(_B==NULL)
		{
			free(_A);
			throw new std::exception();
		}

		_C=(int*)calloc(sizeof(int),size);
		if(_C==NULL)
		{
			free(_A);
			free(_B);
			throw new std::exception();
		}
	}


	void clone(const MyQuickInitArray<T> &old)
	{
		_size=old._size;
		_actualSize=old._actualSize;
		initArrays(old._size);
		memcpy(_A,old._A,sizeof(T*)*_size);
		memcpy(_B,old._B,sizeof(int)*_size);
		memcpy(_C,old._C,sizeof(int)*_size);
		for(int i=0;i<_actualSize;i++)
		{
			_A[_C[i]]=new T(*old._A[old._C[i]]);
		}
	}


	void freeMem(T** a,int* b,int* c,int actualSize)
	{
		for(int i=0;i<actualSize;i++)
		{
			delete a[c[i]];
		}
		free(a);
		free(b);
		free(c);
	}


public:
	MyQuickInitArray<T>(int size): _size(size),_actualSize(0)
	{
		if(size<MIN_SIZE)
		{
			throw new std::exception();
		}
		initArrays(size);
	}


	MyQuickInitArray<T>(const MyQuickInitArray<T> &old)
	{
		clone(old);
	}

	
	~MyQuickInitArray()
	{
		freeMem(_A,_B,_C,_actualSize);
	}


	T &operator[](int n)
	{
		if(n>_size || n<0)
		{
			throw new std::out_of_range("Error: the cell you requested does not exist in that array..");
		}

		if(_B[n]>=_actualSize || _B[n]<0 || _C[_B[n]]!=n)
		{
			_A[n]=new T();
			_C[_actualSize]=n;
			_B[n]=_actualSize++;
		}

		return *(_A[n]);
	}


	const T &operator[](int n) const
	{
		if(n>_size || n<0)
		{
			throw new std::out_of_range("Error: the cell you requested does not exist in that array..");
		}
		
		if(_B[n]>_actualSize || _B[n]<0 || _C[_B[n]]!=n)
		{
			return DEFAULT_VALUE;
		}
		
		return *(_A[n]);
	}


	MyQuickInitArray<T> &operator=(const MyQuickInitArray &old)
	{
		T** oldA=_A;
		int *oldB=_B,*oldC=_C,oldSize=_size;
		clone(old);
		freeMem(oldA,oldB,oldC,oldSize);
		return *this;
	}


private:
	int _size,_actualSize;
	T **_A;
	int *_B,*_C;
};

#endif // MYQUICKINITARRAY_H
