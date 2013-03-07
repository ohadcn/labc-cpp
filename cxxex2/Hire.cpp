/**
 * file:Hire.cpp
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */


#include <iostream>
#include <getopt.h>
#include "Errors.h"
#include "IO.h"
#include "Candidate.h"

// --------------------------------------------------------------------------------------
// This file contains the main method and some helper methods for it.
// --------------------------------------------------------------------------------------

//******** helper methods **********
#define MAX_SALARY 30000

void swap(int &a,int &b)
{
    int temp=a;
    a=b;
    b=temp;
}

List<Candidate>* getMaxTwo(const List<Candidate>* list)
{
    List<Candidate>* result=new List<Candidate>(false);
    //highLow always holds max(0..lowPart)
    //see README for more detailed explanation of the algorithm
    int lowPart=0;
    int highLow=0;

    int resLow=0;//holds the resulting candidates
    int resHigh=list->size()-1;
    for(int i=resHigh;i>=0;i--)    
    {
        while((*list)[lowPart]->getSalary()+(*list)[i]->getSalary()<=MAX_SALARY && lowPart<list->size()-1)
        {
            if((*list)[lowPart]->getWorth()>(*list)[highLow]->getWorth())
            {
                highLow=lowPart;
            }
            lowPart++;
        }
        
        //if their salaries are in range & they have better grades, or the starting results are illigal (may happen
        //for 1st couple
        //beside make sure it's not the same person...
        if((((*list)[i]->getWorth()+(*list)[highLow]->getWorth()>(*list)[resLow]->getWorth()+(*list)[resHigh]->getWorth()
                                            && (*list)[i]->getSalary()+(*list)[highLow]->getSalary()<=MAX_SALARY)
                                       ||((*list)[resLow]->getSalary()+(*list)[resHigh]->getSalary()>MAX_SALARY))
                                                                                                && (i!= highLow)) 
        {
            resHigh=i;
            resLow=highLow;
        } //if
        
    } //for
    
    if(resLow>resHigh)
    {
        swap(resLow,resHigh);
    }
    
    result->Add((*list)[resLow]);
    result->Add((*list)[resHigh]);
    return result;
} //getMaxTwo



//************** main starts here ***********

int main(int argc, char **args)
{
	List<Candidate> *list=new List<Candidate>();
	List<Candidate> *result;

    redirectIO(argc,args);
	setOutputFormat();
    
    if (optind < argc)
	{
		reportError("too many arguments");
	}
	
	cin>>list;
    result=getMaxTwo(list);
    
    for(int i=0;i<result->size();i++)
    {
        (*result)[i]->print();
    }
	
	delete list;
	delete result;
	restoreIO();
}

