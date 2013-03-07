/**
 * file:SparseMatrix.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 3 in c++ course.
 */

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

/**
 * @brief The SparseMatrix class
 * this class holds a matrix.
 * this class is optimized for sparse matrixes, for regular matrixes use RegMatrix class
 *
 * constructors:
 * SparseMatrix() - default constructor, constructs 1X1 with 0
 * SparseMatrix(rows,cols,vector<double> cells) - construct a matrix by size rowsXcols using values from cells
 * SparseMatrix(RegMatrix) - convert RegMatrix to SparseMatrix
 *
 * const public methods:
 * bool trace(&double result) - calc the trace of the matrix, returning it to result
 * returns false if can't calc trace (e,g: not square matrix)
 *
 * bool det(&double result) - calc the determinant of the matrix, returning it to result
 * returns false if can't calc trace (e,g: not square matrix)
 *
 * transpose() - returns the transpose of the matrix.
 *
 * getNumOfRows() - returns the number of rows in the matrix
 *
 * getNumOfCols() - returns the number of columns in the matrix
 *
 * getVal(int col,int row) - returns the number in the [col,rows] in the matrix
 *
 * getStart() - returns a const iterator to the start of the matrix
 *
 * getEnd() - returns a const iterator to the end of the matrix
 *
 * const public operators:
 * ostream<<SparseMatrix - output the matrix
 *
 * SparseMatrix+SparseMatrix - returns val by val sum of the matrixes
 *
 * SparseMatrix-SparseMatrix - returns val by val differnce of matrixes
 *
 * SparseMatrix*SparseMatrix - returns dot product of matrixes
 *
 * SparseMatrix==SparseMatrix - returns true iff both matrixes are equal
 *
 * SparseMatrix!=SparseMatrix - returns true iff two matrixes are different
 *
 * -SparseMatrix - returns val by val negatives of a matrix
 *
 * non-const public operators:
 * SparseMatrix-=SparseMatrix - returns val by val sum of the matrixes
 *
 * SparseMatrix+=SparseMatrix - returns val by val differnce of matrixes
 *
 * SparseMatrix*=SparseMatrix - returns dot product of matrixes
 */

#include <iostream>
#include <vector>
#include <map>

class RegMatrix;


using namespace std;
class SparseMatrix:public map<int,double>
{
public:
	//constructors
	SparseMatrix();
	SparseMatrix (size_t rows, size_t cols,const vector<double> cells );
	SparseMatrix(const RegMatrix old);
	
	//unaries
	bool trace ( double &theTrace ) const;
	bool det ( double &theDeterminant ) const;
	SparseMatrix transpose() const;

	//binaries
	SparseMatrix operator -(const SparseMatrix &other) const;
	SparseMatrix operator -=(const SparseMatrix &other);
	SparseMatrix operator +(const SparseMatrix &other) const;
	SparseMatrix operator +=(const SparseMatrix &other);
	SparseMatrix operator *(const SparseMatrix &other) const;
	SparseMatrix operator *=(const SparseMatrix &other);
	bool operator !=(const SparseMatrix &other) const;
	bool operator ==(const SparseMatrix &other) const;

    //other methods
    size_t getNumOfRows() const;
    size_t getNumOfCols() const;
    double getVal(int col, int row) const;
    const_iterator getStart() const;
    const_iterator getEnd() const;

	//friends
	friend ostream& operator << ( ostream &out,const SparseMatrix &matrix );
	friend SparseMatrix operator - ( const SparseMatrix &other );
	
private:
    size_t _rows,_cols;
};

ostream& operator << ( ostream &out,const SparseMatrix &matrix );
SparseMatrix operator - ( const SparseMatrix &other );

#endif // SPARSEMATRIX_H
