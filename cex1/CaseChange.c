//CaseChange.c
//writen by Ohad Cohen <ohadcn@cs.huji.ac.il> for ex1 in labc course

#include <stdio.h>
#include <math.h>

//---------------------------------------------------------------------------------------
//				change Case
//
// General	:	The program converts character cases.
// Input	:	a character
// Output	:	depends on the inputed character: for a letter the output is the same letter converted to
// 				upper/lowercase, if the character is a number the program outputs the square of it
//				for other characters the program just print it again
//
//---------------------------------------------------------------------------------------


int main()
{
    char input;
    scanf("%c",&input);
    int done=0;
    if((input>='a')&&(input<='z'))
    {
        done=1;
        printf("%c->%c\n",input,(input-'a'+'A'));
    }
    if(((input>='A')&&(input<='Z')&&(!done)))
    {
        done=1;
        printf("%c->%c\n",input,(input-'A'+'a'));
    }
    if((input>='0')&&(input<='9')&&(!done))
    {
        done=1;
        printf("%.0f\n",pow(input-'0',2));
    }
    if(!done)
    {
        printf("%c\n",input);
    }
    return 0;
}
