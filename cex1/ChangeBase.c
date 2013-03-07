//ChangeBase.c
//writen by Ohad Cohen <ohadcn@cs.huji.ac.il> for ex1 in labc course

#include <stdio.h>

//---------------------------------------------------------------------------------------
//				change base
//
// General	:	The program converts number bases.
// Input	:	three numbers: the original base, the number in the original base, and the target base
//				separated by #
// Output	:	the number in the target base
// 
//---------------------------------------------------------------------------------------

int main()
{
    int origBase,numOrig,tarBase,num=0,digval=1;
    long digValTar=1,numTar=0;
    scanf("%d#%d#%d",&origBase,&numOrig,&tarBase);
    
    //convert to base 10
    while(numOrig>0)
    {
        int dig=numOrig%10;
        num+=digval*dig;
        digval*=origBase;
        numOrig/=10;
        if(dig>=origBase)
        {
            printf("invalid");
            return 1;
        }
    }
    
    //convert to target base
    while(num>0)
    {
        int dig=num%tarBase;
        numTar+=digValTar*dig;
        digValTar*=10;
        num/=tarBase;
    }
    printf("%ld",numTar);
    return 0;
}
