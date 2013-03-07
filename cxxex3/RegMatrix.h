/**
 * file:RegMatrix.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 3 in c++ course.
 */
#ifndef REGMATRIX_H
#define REGMATRIX_H

/**
 * @brief The RegMatrix class
 * this class holds a matrix.
 *
 * constructors:
 * RegMatrix() - default constructor, constructs 1X1 with 0
 * RegMatrix(rows,cols,vector<double> cells) - construct a matrix by size rowsXcols using values from cells
 * RegMatrix(SparseMatrix) - convert SparseMatrix to RegMatrix
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
#include "Errors.h"
#include "SparseMatrix.h"

using namespace std;
class RegMatrix: private vector< vector<double> > {

public:
	//constructors
	RegMatrix();
	RegMatrix (size_t rows, size_t cols,const vector<double> cells );
	RegMatrix(const SparseMatrix old);
	
	//unaries
	bool trace ( double &theTrace ) const;
	bool det ( double &theDeterminant ) const;
	RegMatrix transpose() const;

	//binaries
	RegMatrix operator -(const RegMatrix &other) const;
	RegMatrix operator -=(const RegMatrix &other);
	RegMatrix operator +(const RegMatrix &other) const;
	RegMatrix operator +=(const RegMatrix &other);
	RegMatrix operator *(const RegMatrix &other) const;
	RegMatrix operator *=(const RegMatrix &other);
	bool operator !=(const RegMatrix &other) const;
	bool operator ==(const RegMatrix &other) const;

    //other methods
    size_t getNumOfRows() const;
    size_t getNumOfCols() const;
    double getVal(int col, int row) const;

	//friends
	friend ostream& operator << ( ostream &out,const RegMatrix &matrix );
	friend RegMatrix operator - ( const RegMatrix &other );
	
private:
	size_t _rows,_cols;
};

ostream& operator << ( ostream &out,const RegMatrix &matrix );
RegMatrix operator - ( const RegMatrix &m );

#endif // REGMATRIX_H
