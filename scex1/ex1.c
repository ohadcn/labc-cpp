//ex1.c

#include <stdio.h>

#include "DEFINITIONS.H"

//**************************************************************
//define epsilon, range, f and g if they weren't defined already
//the default valued is documented at the declaration of findEq()
//function
//**************************************************************
#ifndef EPSILON
    #define EPSILON 0.0001
#endif

#ifndef RANGE
    #define RANGE 1000
#endif

#ifndef F
    #define F(x) x + 0.5
#endif

#ifndef G
    #define G(x) 10.5 -x
#endif


//*************
//local defines
//*************

//absolute value, the ex, spec, demand not using math.h
#define ABS(x) ((x)>0?x:-(x))

//check if two double values are equals
#define EQUAL(A,B) (ABS((A)-(B))<EPSILON)

//not found return value
#define NOT_FOUND -1



//*********************************************************************************
//                  find equal point of two functions
//
//general    :    the main function of this program is to test if two functions has
//                different return values for each integer in renge
//                this function gets it's parameters as global defined
//
//    parameter    |   default value    |
//  ---------------+--------------------+--------------------------------
//      F(x)       |       x + 0.5      | a monotonic increasing function
//      G(x)       |       10.5 -x      | a monotonic decreasing function
//     RANGE       |        1000        | the maximum value to test
//    EPSILON      |       0.0001       | the required accuracy
//
//output : the integer value for whom the functions will return the same value, and
//         the return value, or -1 if the functions never returned the same value.
//*********************************************************************************
int findEq()
{
    int max=RANGE;
    int min=0;
    while(max>min+1)
    {
        int mid=(max+min)/2;
        if(EQUAL(F(mid),G(mid)))
        {
            printf("%d\n%3.3f",mid,F(mid));
            return mid;
        }
        if(F(mid)>G(mid))
        {
            max=mid;
        }
        else
        {
            min=mid;
        }

    }
    return NOT_FOUND;
}


//*************************************************************************
//this main function exist just to demonstrate the usage of findEq function
//*************************************************************************
int main()
{
    return findEq();
}

