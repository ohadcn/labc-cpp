/**
 * file:RegMatrix.cpp
 * this file has the implementation of the class SparseMatrix
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 3 in c++ course.
 */

#include "RegMatrix.h"
#include "SparseMatrix.h"
#include "Exround.h"
#include <cmath>

#define EMPTY_CELL 0.0
#define DEFAULT_SIZE 1
#define DEFAULT_VALUE 0
#define SIZE_MESSEGE "Number of elements actually in List:"

SparseMatrix::SparseMatrix():
            SparseMatrix(DEFAULT_SIZE,DEFAULT_SIZE,vector<double>(DEFAULT_SIZE*DEFAULT_SIZE,DEFAULT_VALUE))
{
}

SparseMatrix::SparseMatrix(size_t rows, size_t cols, const vector<double> cells):_rows(rows),_cols(cols)
{
	int index;
	if(cells.size()!=rows*cols)
	{
		reportError();
	}
	for(size_t i=0;i<rows;i++)
	{
		for(size_t j=0;j<cols;j++)
		{
			if(abs(cells[(index=(i*_cols+j))])>EPSILON)
			{
				(*this)[index]=ExRound(cells[index]);
			}
		}
	}
}

SparseMatrix::SparseMatrix(const RegMatrix old):_rows(old.getNumOfRows()),_cols(old.getNumOfCols())
{
	for(size_t i=0;i<_rows;i++)
	{
		for(size_t j=0;j<_cols;j++)
		{
            if(abs(old.getVal(i,j))>EPSILON)
			{
                (*this)[i*_cols+j]=old.getVal(i,j);
			}
		}
	}
}

bool SparseMatrix::trace(double &theTrace) const
{
	int index;
	if(_cols!=_rows)
	{
		return false;
	}
	theTrace=0;
	for(size_t i=0;i<_cols;i++)
	{
		if(count(index=i*_rows+i))
		{
			theTrace+=(*this).at(index);
		}
	}
	return true;
}

bool SparseMatrix::det(double &theDeterminant) const
{
	if(_cols!=_rows)
	{
		return false;
	}
	if(_cols==1)
	{
		theDeterminant=(count(0)?at(0):EMPTY_CELL);
		return true;
	}
	else
	{
		int sign=1;
		size_t newSize=_cols-1;
		theDeterminant=0;
		for(size_t i=0;i<_cols;i++)
		{
			vector<double> vec(newSize*newSize);
			double subRes;
			for(size_t j=1;j<_cols;j++)
			{
				for(size_t k=0;k<_rows;k++)
				{
					if(k!=i && count(j*_cols+k))
					{
						vec[newSize*(j-1)+(k<i?k:k-1)]=this->at(j*_cols+k);
					}
				}
			}
			SparseMatrix sub(newSize,newSize,vec);
			sub.det(subRes);
			theDeterminant+=sign*subRes*(count(i)?at(i):EMPTY_CELL);
			sign=-sign;
		}
	}
	return true;
}

SparseMatrix SparseMatrix::transpose() const
{
	SparseMatrix result;
	result.clear();
	for(auto i=begin();i!=end();i++)
	{
		result[(i->first%_cols)*_rows + i->first/_cols] = i->second;
	}
	result._rows=_cols;
	result._cols=_rows;
	return result;
}

ostream &operator <<(ostream &out, const SparseMatrix &matrix)
{
	out.setf(ios_base::fixed);
	out.precision(3);
	int index;
	for(size_t i=0;i<matrix._rows;i++)
	{
		for(size_t j=0;j<matrix._cols;j++)
		{
			if(matrix.count(index=(i*matrix._cols+j)))
			{
				out<<matrix.at(index);
			}
			else
			{
				out<<EMPTY_CELL;
			}
			if(i!=matrix._rows-1 || j!=matrix._cols-1)
			{
				out<<'\t';
			}
		}
		out<<endl;
	}
	out<<SIZE_MESSEGE<<matrix.size()<<endl;
//	out.unsetf(ios_base::floatfield);
	return out;
}

SparseMatrix operator -(const SparseMatrix &matrix)
{
	SparseMatrix result(matrix);
	for(auto i=result.begin();i!=result.end();i++)
	{
		result[i->first] = -(i->second);
	}
	return result;
}

SparseMatrix SparseMatrix::operator -(const SparseMatrix &other) const
{
	SparseMatrix result(*this);
	result-=other;
	return result;
}

SparseMatrix SparseMatrix::operator -=(const SparseMatrix &other)
{
	(*this)+= (-other);
	return *this;
}

SparseMatrix SparseMatrix::operator +(const SparseMatrix &other) const
{
	SparseMatrix result(*this);
	result+=other;
	return result;
}

SparseMatrix SparseMatrix::operator +=(const SparseMatrix &other)
{
	if(this->_rows!=other._rows || this->_cols!=other._cols )
	{
		reportError();
	}
	for(auto i=other.begin();i!=other.end();i++)
	{
		(*this)[i->first]+=i->second;
	}
	return *this;
}

SparseMatrix SparseMatrix::operator *(const SparseMatrix &other) const
{
	SparseMatrix result(*this);
	result*=other;
	return result;
}

SparseMatrix SparseMatrix::operator *=(const SparseMatrix &other)
{
	SparseMatrix temp(*this);
	double val;
	if(this->_cols!=other._rows )
	{
		reportError();
	}
	this->clear();
	_cols=other._cols;
	for(size_t i=0;i<_rows;i++)
	{
		for(size_t j=0;j<other._cols;j++)
		{
			val=0;
			for(size_t k=0;k<other._rows;k++)
			{
				if(temp.count(i*temp._cols+k) && other.count(k*other._cols+j))
				{
					val+=temp[i*temp._cols+k]*other.at(k*other._cols+j);
				}
			}
			if(val)
			{
				(*this)[i*_cols+j]=val;
			}
		}
	}
	return *this;
}

bool SparseMatrix::operator ==(const SparseMatrix &other) const
{
	if(this->_rows!=other._rows || this->_cols!=other._cols || this->size() != other.size())
	{
		return false;
	}
	for(auto i=begin();i!=end();i++)
	{
		if( (!other.count(i->first)) || other.at(i->first)!=i->second)
		{
			return false;
		}
	}
    return true;
}

size_t SparseMatrix::getNumOfRows() const
{
    return _rows;
}

size_t SparseMatrix::getNumOfCols() const
{
    return _cols;
}

double SparseMatrix::getVal(int col, int row) const
{
    return at(row*_cols+col);
}

map<int,double>::const_iterator SparseMatrix::getStart() const
{
    return begin();
}

map<int,double>::const_iterator SparseMatrix::getEnd() const
{
    return end();
}

bool SparseMatrix::operator !=(const SparseMatrix &other) const
{
	return !(*this==other);
}
