/*
 * This Driver is for testing RegMatrix and RegMatrix classs
 */
#include "SparseMatrix.h"
#include "RegMatrix.h"

#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>

#define REG_MAT 1
#define SPARSE_MAT 2

#define LINE "=========="
#define MAT_LINE "--------"
#define DELIM ','

const std::string OPERATIONS[10] = {"-", "trace", "det", "transpose", "+", "*", "+=", "*=", "==", "!="};

std::string g_line;

void unaryOperation(const int operatorChoice);
void unaryOperationReg(const int operatorChoice, const RegMatrix& s);
void unaryOperationSparse(const int operatorChoice, const SparseMatrix& s);

void binaryOperation(const int operatorChoice);
void binaryOperationRegReg(const int operatorChoice, RegMatrix& r1, RegMatrix& r2);
void binaryOperationRegSp(const int operatorChoice, RegMatrix& r1, SparseMatrix& s2);
void binaryOperationSpReg(const int operatorChoice, SparseMatrix& s1, RegMatrix& r2);
void binaryOperationSpSp(const int operatorChoice, SparseMatrix& s1, SparseMatrix& s2);

void printResultRegMatrix(const RegMatrix& regMat);
void printResultSparseMatrix(const SparseMatrix& spMat);
void readMatrixInfo(int& rows,int& cols,std::vector<double>& cells);

int main()
{

    std::cout<<"Choose operation:"<<std::endl;

    int item;
    for (item=1; item<=10; item++)
    {
      std::cout<< item << ". " << "\t" << OPERATIONS[item-1]<< std::endl;
    }
   

    getline(std::cin,g_line);
    int operatorChoice = atoi(g_line.c_str());
    assert (operatorChoice > 0 && operatorChoice <=10);

    if (operatorChoice <= 4)
    {
        unaryOperation(operatorChoice);        
    }
    else
    {
        binaryOperation(operatorChoice);
    }

    return 0;
}

void unaryOperation(const int operatorChoice)
{
    std::cout<< "Operation "<< OPERATIONS[operatorChoice-1]<< " requires 1 operand matrix."<< std::endl;
    std::cout<< "How would you like the matrix to be represented ("<< REG_MAT<<
        " for regular and "<< SPARSE_MAT<< " for sparse)?"<< std::endl;
    getline(std::cin,g_line);
    int matType = atoi(g_line.c_str());
    assert(matType == REG_MAT || matType == SPARSE_MAT);

    // Read the matrix information:
    int rows,cols;
    std::vector<double> cells;
    readMatrixInfo(rows,cols,cells);
    RegMatrix r;
    SparseMatrix s;

    // Perform the operation:
    switch (matType)
    {
      case REG_MAT:
          r = RegMatrix(rows,cols,cells);
          std::cout<<MAT_LINE<<std::endl<<"got matrix:"<<std::endl;
	  std::cout << r;
          unaryOperationReg(operatorChoice, r);
          break;
      case SPARSE_MAT:
          s = SparseMatrix(rows,cols,cells);
          std::cout<<MAT_LINE<<std::endl<<"got matrix:"<<std::endl;
	  std::cout << s;
          unaryOperationSparse(operatorChoice, s);
          break;
      default:
          exit(1);
    }
}

void unaryOperationReg(const int operatorChoice, const RegMatrix& r)
{
    RegMatrix resMat;
    double res;
    bool b;

    switch (operatorChoice)
    {
      case 1: 
          resMat = -r;
          printResultRegMatrix(resMat);
          break;
      case 2: 
          b = r.trace(res);
          if (b)
          {
              std::cout<< "The matrix is square and its trace is "<< res<< std::endl;
          }
          else
          {
              std::cout<< "The matrix isn't square"<< std::endl;
          }
          break;
      case 3:
          b = r.det(res);
          if (b)
          {
              std::cout<< "The matrix is square and its determinant is "<< res<< std::endl;
          }
          else
          {
              std::cout<< "The matrix isn't square"<< std::endl;
          }
          break;
      case 4:
          resMat = r.transpose();
          printResultRegMatrix(resMat);
          break;
      default:
          exit(1);
    }

}

void unaryOperationSparse(const int operatorChoice, const SparseMatrix& s)
{

    SparseMatrix resMat;
    double res;
    bool b;

    switch (operatorChoice)
    {
      case 1: 
          resMat = -s;
          printResultSparseMatrix(resMat);
          break;
      case 2: 
          b = s.trace(res);
          if (b)
          {
              std::cout<< "The matrix is square and its trace is "<< res<< std::endl;
          }
          else
          {
              std::cout<< "The matrix isn't square"<< std::endl;
          }
          break;
      case 3:
          b = s.det(res);
          if (b)
          {
              std::cout<< "The matrix is square and its determinant is "<< res<< std::endl;
          }
          else
          {
              std::cout<< "The matrix isn't square"<< std::endl;
          }
          break;
      case 4:
          resMat = s.transpose();
          printResultSparseMatrix(resMat);
          break;
      default:
          exit(1);
    }

}

void binaryOperation(const int operatorChoice)
{
    std::cout<< "Operation "<< OPERATIONS[operatorChoice-1]<< " requires 2 operand matrices."<< std::endl;

    std::cout<< "How would you like the first matrix to be represented ("<< REG_MAT<<
        " for regular and "<< SPARSE_MAT<< " for sparse)?"<< std::endl;
    getline(std::cin,g_line);
    int mat1Type = atoi(g_line.c_str());
    assert(mat1Type == REG_MAT || mat1Type == SPARSE_MAT);

    std::cout<< "How would you like the second matrix to be represented ("<< REG_MAT<<
        " for regular and "<< SPARSE_MAT<< " for sparse)?"<< std::endl;
    getline(std::cin,g_line);
    int mat2Type = atoi(g_line.c_str());
    assert(mat2Type == REG_MAT || mat2Type == SPARSE_MAT);

    // Read the matrix information:
    int rows1,cols1,rows2,cols2;
    std::vector<double> cells1;
    std::vector<double> cells2;

    std::cout<< "Insert first matrix:"<< std::endl;
    readMatrixInfo(rows1,cols1,cells1);
    std::cout<< "Insert second matrix:"<< std::endl;
    readMatrixInfo(rows2,cols2,cells2);
    RegMatrix *r1 = NULL;
    RegMatrix *r2 = NULL;
    SparseMatrix *s1 = NULL;
    SparseMatrix *s2 = NULL;

    // The 4 combinations of matrix types:
    if (mat1Type == REG_MAT)
    {
        r1 = new RegMatrix(rows1,cols1,cells1);
        std::cout<< MAT_LINE<< std::endl<< "Got first matrix:"<< std::endl;
	std::cout << *r1;

        if (mat2Type == REG_MAT)
        {
            r2 = new RegMatrix(rows2,cols2,cells2);
            std::cout<< MAT_LINE<< std::endl<< "Got second matrix:"<< std::endl;
	    std::cout << *r2;
            binaryOperationRegReg(operatorChoice,*r1,*r2);
	    delete r2;
        }
        else
        {
            s2 = new SparseMatrix(rows2,cols2,cells2);
            std::cout<< MAT_LINE<< std::endl<< "Got second matrix:"<< std::endl;
	    std::cout << *s2;
            binaryOperationRegSp(operatorChoice,*r1,*s2);
	    delete s2;
        }
	delete r1;
	
    }
    else
    {
        s1 = new SparseMatrix(rows1,cols1,cells1);
        std::cout<< MAT_LINE<< std::endl<< "Got first matrix:"<< std::endl;
	std::cout << *s1;
        if (mat2Type == REG_MAT)
        {
            r2 = new RegMatrix(rows2,cols2,cells2);
            std::cout<< MAT_LINE<< std::endl<< "Got second matrix:"<< std::endl;
	    std::cout << *r2;
            binaryOperationSpReg(operatorChoice,*s1,*r2);
	    delete r2;
        }
        else
        {
            s2 = new SparseMatrix(rows2,cols2,cells2);
            std::cout<< MAT_LINE<< std::endl<< "Got second matrix:"<< std::endl;
	    std::cout << *s2;
            binaryOperationSpSp(operatorChoice,*s1,*s2);
	    delete s2;
        }
	delete s1;
    }
    
}

void binaryOperationRegReg(const int operatorChoice, RegMatrix& r1, RegMatrix& r2)
{
    RegMatrix resMat;
    bool b;
    std::string str;
    switch (operatorChoice)
    {
      case 5:
          resMat = r1+r2;
          printResultRegMatrix(resMat);
          break;
      case 6:
          resMat = r1*r2;
          printResultRegMatrix(resMat);
          break;
      case 7:
          r1+=r2;
          std::cout<< "Now the first matrix is:"<< std::endl;
          printResultRegMatrix(r1);
          break;
      case 8:
          r1*=r2;
          std::cout<< "Now the first matrix is:"<< std::endl;
          printResultRegMatrix(r1);
          break;
      case 9:
          b = (r1==r2);
          str = b ? "are" : "are not";
          std::cout<< LINE<< std::endl<< "The two matrices " << str<< " equal."<< std::endl;
          break;
      case 10:
          b = (r1!=r2);
          str = b ? "are" : "are not";
          std::cout<< LINE<< std::endl<< "The two matrices " << str<< " different."<< std::endl;
          break;
    }
}

void binaryOperationRegSp(const int operatorChoice, RegMatrix& r1, SparseMatrix& s2)
{
    RegMatrix resMat;
    bool b;
    std::string str;
    switch (operatorChoice)
    {
      case 5:
          resMat = r1+s2;
          printResultRegMatrix(resMat);
          break;
      case 6:
          resMat = r1*s2;
          printResultRegMatrix(resMat);
          break;
      case 7:
          r1+=s2;
          std::cout<< "Now the first matrix is:"<< std::endl;
          printResultRegMatrix(r1);
          break;
      case 8:
          r1*=s2;
          std::cout<< "Now the first matrix is:"<< std::endl;
          printResultRegMatrix(r1);
          break;
      case 9:
          b = (r1==s2);
          str = b ? "are" : "are not";
          std::cout<< LINE<< std::endl<< "The two matrices " << str<< " equal."<< std::endl;
          break;
      case 10:
          b = (r1!=s2);
          str = b ? "are" : "are not";
          std::cout<< LINE<< std::endl<< "The two matrices " << str<< " different."<< std::endl;
          break;
    }
}

void binaryOperationSpReg(const int operatorChoice, SparseMatrix& s1, RegMatrix& r2)
{
    RegMatrix resMat;
    bool b;
    std::string str;
    switch (operatorChoice)
    {
      case 5:
          resMat = s1+r2;
          printResultRegMatrix(resMat);
          break;
      case 6:
          resMat = s1*r2;
          printResultRegMatrix(resMat);
          break;
      case 7:
          s1+=r2;
          std::cout<< "Now the first matrix is:"<< std::endl;
          printResultRegMatrix(s1);
          break;
      case 8:
          s1*=r2;
          std::cout<< "Now the first matrix is:"<< std::endl;
          printResultRegMatrix(s1);
          break;
      case 9:
          b = (s1==r2);
          str = b ? "are" : "are not";
          std::cout<< LINE<< std::endl<< "The two matrices " << str<< " equal."<< std::endl;
          break;
      case 10:
          b = (s1!=r2);
          str = b ? "are" : "are not";
          std::cout<< LINE<< std::endl<< "The two matrices " << str<< " different."<< std::endl;
          break;
    }
}

void binaryOperationSpSp(const int operatorChoice, SparseMatrix& s1, SparseMatrix& s2)
{
    SparseMatrix resMat;
    bool b;
    std::string str;
    switch (operatorChoice)
    {
      case 5:
          resMat = s1+s2;
          printResultSparseMatrix(resMat);
          break;
      case 6:
          resMat = s1*s2;
          printResultSparseMatrix(resMat);
          break;
      case 7:
          s1+=s2;
          std::cout<< "Now the first matrix is:"<< std::endl;
          printResultSparseMatrix(s1);
          break;
      case 8:
          s1*=s2;
          std::cout<< "Now the first matrix is:"<< std::endl;
          printResultSparseMatrix(s1);
          break;
      case 9:
          b = (s1==s2);
          str = b ? "are" : "are not";
          std::cout<< LINE<< std::endl<< "The two matrices " << str<< " equal."<< std::endl;
          break;
      case 10:
          b = (s1!=s2);
          str = b ? "are" : "are not";
          std::cout<< LINE<< std::endl<< "The two matrices " << str<< " different."<< std::endl;
          break;
    }
}


void readMatrixInfo(int& rows,int& cols,std::vector<double>& cells)
{
    std::cout<< "number of rows:";
    getline(std::cin,g_line);
    rows = atoi(g_line.c_str());

    std::cout<< "number of columns:";
    getline(std::cin,g_line);
    cols = atoi(g_line.c_str());

    std::cout<< "Now insert the values of the matrix, row by row."<< std::endl<<
        "After each cell add the char \'"<< DELIM<< "\'"<<
        " (including after the last cell of a row)."<< std::endl<<
        "Each row should be in a separate line."<<std::endl;

    int row,col;
    for (row = 0; row < rows; row++)
    {
        getline(std::cin,g_line);

        std::stringstream stream(g_line);
        std::string numStr;
        double val;
        for (col = 0; col < cols; col++)
        {
            getline(stream,numStr,DELIM);
            val = atof(numStr.c_str());
            cells.push_back(val);
        }
    }

}

void printResultRegMatrix(const RegMatrix& regMat)
{
    std::cout<<LINE<<std::endl;
    std::cout<< "Resulted matrix:"<<std::endl;
    std::cout << regMat;
}

void printResultSparseMatrix(const SparseMatrix& spMat)
{
    std::cout<<LINE<<std::endl;
    std::cout<< "Resulted matrix:"<<std::endl;
    std::cout << spMat;
}
