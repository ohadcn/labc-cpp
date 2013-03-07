/**
 * file:RegMatrix.cpp
 * this file has the implementation of the class RegMatrix
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 3 in c++ course.
 */

#include "RegMatrix.h"
#include "Exround.h"

#define DEFAULT_SIZE 1
#define DEFAULT_VALUE 0

RegMatrix::RegMatrix():RegMatrix(DEFAULT_SIZE,DEFAULT_SIZE,vector<double>(DEFAULT_SIZE*DEFAULT_SIZE,DEFAULT_VALUE))
{

}

RegMatrix::RegMatrix(size_t rows, size_t cols, const vector<double> cells) :
									vector< vector<double> >(rows,vector<double>(cols)),_rows(rows),_cols(cols)
{
	if(cells.size()!=rows*cols)
	{
		reportError();
	}
	for(size_t i=0;i<_rows;i++)
	{
		for(size_t j=0;j<_cols;j++)
		{
			(*this)[i][j]=ExRound(cells[i*_cols+j]);
		}
	}
}

RegMatrix::RegMatrix(const SparseMatrix old):
                    vector< vector<double> >(old.getNumOfRows(),vector<double>(old.getNumOfCols(),0))
                                                    ,_rows(old.getNumOfRows()),_cols(old.getNumOfCols())
{
    for(auto i=old.getStart();i!=old.getEnd();i++)
	{
		(*this)[i->first/_cols][i->first%_cols]=i->second;
	}
}

bool RegMatrix::trace(double &theTrace) const
{
	if(_cols!=_rows)
	{
		return false;
	}
	theTrace=0;
	for(size_t i=0;i<_cols;i++)
	{
		theTrace+=(*this)[i][i];
	}
	return true;
}

bool RegMatrix::det(double &theDeterminant) const
{
	if(_cols!=_rows)
	{
		return false;
	}
	if(_cols==1)
	{
		theDeterminant=*(this->begin()->begin());
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
					if(k!=i)
					{
						vec[newSize*(j-1)+(k<i?k:k-1)]=at(j).at(k);
					}
				}
			}
			RegMatrix sub(newSize,newSize,vec);
			sub.det(subRes);
			theDeterminant+=sign*subRes*at(0).at(i);
			sign=-sign;
		}
	}
	return true;
}

RegMatrix RegMatrix::transpose() const
{
	RegMatrix result;
	result.reserve(_cols);
	for(size_t i=0;i<_cols;i++)
	{
		result[i].reserve(_rows);
		for(size_t j=0;j<_rows;j++)
		{
			result[i][j]=(*this)[j][i];
		}
	}
	result._cols=_rows;
	result._rows=_cols;
	return result;
}

ostream& operator <<(ostream &out,const RegMatrix &matrix)
{
	out.setf(ios_base::fixed);
	out.precision(3);
	for(size_t i=0;i<matrix._rows;i++)
	{
		for(size_t j=0;j<matrix._cols;j++)
		{
			out<<matrix[i][j];
			if(i!=matrix._rows-1 || j!=matrix._cols-1)
			{
				out<<'\t';
			}
		}
		out<<endl;
	}
	return out;
}

RegMatrix operator -(const RegMatrix &other)
{
	RegMatrix result(other);
	for(size_t i=0;i<other._rows;i++)
	{
		for(size_t j=0;j<other._cols;j++)
		{
			result[i][j]=-other[i][j];
		}
	}

	return result;
}

RegMatrix RegMatrix::operator -=(const RegMatrix &other)
{
	(*this)+= (-other);
	return *this;
}

RegMatrix RegMatrix::operator -(const RegMatrix &other) const
{
	RegMatrix result(*this);
	result-=other;
	return result;
}

RegMatrix RegMatrix::operator +=(const RegMatrix &other)
{
	if(this->_rows!=other._rows || this->_cols!=other._cols)
	{
		reportError();
	}
	for(size_t i=0;i<_rows;i++)
	{
		for(size_t j=0;j<_cols;j++)
		{
			(*this)[i][j]+=other[i][j];
		}
	}
	return *this;
}

RegMatrix RegMatrix::operator +(const RegMatrix &other) const
{
	RegMatrix result(*this);
	result+=other;
	return result;
}

RegMatrix RegMatrix::operator *=(const RegMatrix &other)
{
	RegMatrix temp(*this);
	if(this->_cols!=other._rows )
	{
		reportError();
	}
	_cols=other._cols;
	this->clear();
	reserve(_cols);
	for(size_t i=0;i<_rows;i++)
	{
		(*this)[i].reserve(_rows);
		for(size_t j=0;j<other._cols;j++)
		{
			(*this)[i][j]=0;
			for(size_t k=0;k<other._rows;k++)
			{
				(*this)[i][j]+=temp[i][k]*other.at(k).at(j);
			}
		}
	}
	return *this;
}

RegMatrix RegMatrix::operator *(const RegMatrix &other) const
{
	RegMatrix result(*this);
	result*=other;
	return result;
}

bool RegMatrix::operator ==(const RegMatrix &other) const
{
	if(this->_rows!=other._rows || this->_cols!=other._cols)
	{
		return false;
	}
	for(size_t i=0;i<_rows;i++)
	{
		for(size_t j=0;j<_cols;j++)
		{
			if((*this)[i][j]!=other[i][j])
			{
				return false;
			}
		}
	}
    return true;
}

size_t RegMatrix::getNumOfCols() const
{
    return _cols;
}

size_t RegMatrix::getNumOfRows() const
{
    return _rows;
}

double RegMatrix::getVal(int col, int row) const
{
    return at(col).at(row);
}

bool RegMatrix::operator !=(const RegMatrix &other) const
{
	return !(*this==other);
}

