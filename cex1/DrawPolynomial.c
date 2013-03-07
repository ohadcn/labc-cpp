//DrawPolynomial.c
//writen by Ohad Cohen <ohadcn@cs.huji.ac.il> for ex1 in labc course

#include <stdio.h>
#include <math.h>

//---------------------------------------------------------------------------------------
//				polynoms systems
//
// General	:	The program plots a graph of a 3rd degree polynom.
// Input	:	the three parameters of the polynom
// Output	:	plot of the polynom
// 
//---------------------------------------------------------------------------------------

//get absolute value of a number
#define ABS(A) ((A)>0?(A):-(A))

int main()
{
    int minX=-35, maxX=35, minY=-10, maxY=10;//set parameters

    //read numbers
    double a,b,c,d;
    printf("y(x)=a+b*x+c*x^2+d*x^3\n");
    printf("Select a:\n");
    scanf("%lf",&a);
    printf("Select b:\n");
    scanf("%lf",&b);
    printf("Select c:\n");
    scanf("%lf",&c);
    printf("Select d:\n");
    scanf("%lf",&d);

    printf("y(x)=(%.3f)+(%.3f)*x+(%.3f)*x^2+(%.3f)*x^3\n",a,b,c,d);

    //draw function
    int x,y;
    for(y=maxY;y>=minY;y--)
    {
        for(x=minX;x<=maxX;x++)
        {
            if(fabs(y-(a+x*(b+x*(c+x*(d)))))<0.5)
            {
                printf("*");
                continue;
            }
            if(x==0)
            {
                if(y==0)
                {
                    printf("+");
                    continue;
                }
                printf("|");
                continue;
            }
            if(y==0)
            {
                printf("-");
                continue;
            }
            printf(" ");
        }
        printf("\n");
    }
    return 0;
}
