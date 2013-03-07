/**
 * file:IO.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */


// --------------------------------------------------------------------------------------
// This file contains the implementation of the IO methods needed by that program.
// --------------------------------------------------------------------------------------

#include "IO.h"
#include "Alice.h"
#include "Bob.h"
#include "Colin.h"
#include "Danny.h"
#include "Errors.h"
#include <getopt.h>
#include <fstream>


//***************************************************
//reading operators.

istream &operator >>(istream &in, Candidate *(&p))
{
	float grade,projectGrade,salary;
	long ID;
	char university;
    in>>university;
    
    //sometimes the last newline makes cin not stoping at end of input
    //so we need to check it after reading the 1st char
    if(in.eof())
    {
        return in;
    }
	switch (university) {
	case 'A':
		in>>ID>>grade>>salary;
		p=new Alice(ID,grade,salary);
		break;
		
	case 'B':
		in>>ID>>grade>>salary;
		p=new Bob(ID,grade,salary);
		break;
		
	case 'C':
		in>>ID>>grade>>projectGrade>>salary;
		p=new Colin(ID,grade,salary,projectGrade);
		break;
		
	case 'D':
		in>>ID>>grade>>projectGrade>>salary;
		p=new Danny(ID,grade,salary,projectGrade);
		break;
		
	default:
		reportError("unknown institute");
		break;
	}
	return in;
}

istream &operator >>(istream &in, List<Candidate> *list)
{
	Candidate *temp;
	while(in>>temp)
	{
		list->Add(temp);
	}
	return in;
}

//*********************************************************
//IO redirection methods

//keep them all outside so they can be kept from function to function.
#define ARGS_STR "i:o:"
streambuf *backin,*backout;
ifstream ifile;
ofstream ofile;

void redirectIO(int argc,char **args)
{
	backin=cin.rdbuf();
	backout=cout.rdbuf();
	char arg;
	while((arg=getopt(argc,args,ARGS_STR))!=-1)
	{
		switch (arg) {
		case 'o':
			ofile.open(optarg);
			if(!ofile)
			{
				reportError("can\'t output to file!");
			}
			
			cout.rdbuf(ofile.rdbuf());
			break;
		case 'i':
			ifile.open(optarg);
			if(!ifile)
			{
				reportError("input file not exist or not readable");
			}
			cin.rdbuf(ifile.rdbuf());
			break;
		default:
			reportError("unknown parameter");
		}
	}
}

void restoreIO()
{
	cout.unsetf(ios_base::floatfield);
	cout.rdbuf(backout);
	cin.rdbuf(backin);
	if(ifile)
	{
		ifile.close();
	}
	if(ofile)
	{
		ofile.close();
	}
}

void setOutputFormat()
{
	cout.setf(ios_base::fixed);
	cout.precision(4);
}
