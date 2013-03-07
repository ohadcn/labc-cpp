//CheckParenthesis.c
//this code has been writen for ex2 in c course at huji university
//by Ohad Cohen <ohadcn@cs.huji.ac.il>

/**
 * test a file for the validity of parenthesis usage: if every opening parenthesis has closing one;
 * and no oclosing brackets appear without opening one
 * input:a file name
 * output:Ok if the file is legal, "Bad structure" otherwise;
 * on case of error the program print error message and exit with status code 1
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> //for exit codes

//this message will be presented to the user in case of ilegal parameters
#define USAGE "usage:CheckParenthesis <filename>\n"

//the desired number of arguments
#define MIN_ARGS 2
#define MAX_ARGS 2


/**
 * this function reruns true if the input character is a closing parentesis and false otherwise
 */
int isCloser(char closer)
{
	return (closer==')')||(closer==']')||(closer=='}')||(closer=='>');
}


/**
 * this function reruns true if the input character is a opening parentesis and false otherwise
 */
int isOpener(char opener)
{
	return (opener=='(')||(opener=='[')||(opener=='{')||(opener=='<');
}


/**
 * this function returns the closer of the inputed parenthesis
 * warning: make sure tou put in a parenthesis open, the output for other characters is unexpected
 */
char getMyCloser(char opener)
{
	//checked it in the ascii table:every opening & closing bracket have one char between:except () which
	//appear one after another
	return (opener=='(')?opener+1:opener+2;
}

/**
 * check a block of brackets in the file for being legal
 * legal means that no other closing bracket appear inside, and the file is not ended before those bracket closed
 *
 * parameters:
 * file - the file that contains this paragrath; assuming this file is opened for reading & it point to the start
 * of the bracket block needs to be tested
 * parEnd - the character who should appear at the end of the block
 */
int isParenthesisBlockCorrect(FILE* file,char parEnd)
{
	char current;

	while((current=fgetc(file))!=EOF)
	{
		if(current==parEnd)//end of block
		{
			return true;
		}

		//if this is an opening bracket, get recursively in, if there is an error in the inner block return false
		if((isOpener(current)
			&&(!isParenthesisBlockCorrect(file,getMyCloser(current))))

				//if an irrelevant closing brackets appears return false
				||(isCloser(current)))
		{
			return false;
		}
	}
	return false;//the file ended without the closing brackets
}


/**
 * test a file for being parenthesis - legal, mean every parenthsis in the file is closed
 * parameters:
 * file - a reading-open pointer to the file to be tested
 */
int isParenthesisCorrect(FILE* file)
{
	char current;

	while((current=fgetc(file))!=EOF)
	{
		//see comment on similar code above (in the former function)
		if((isOpener(current)
			&&(!isParenthesisBlockCorrect(file,getMyCloser(current))))
				||(isCloser(current)))
		{
			return false;
		}
	}
	return true;
}


/**
 * the main function of this code, the start of the code to be run.
 */
int main(int argc,char **argv)
{
	FILE* file;

	if(argc>MAX_ARGS)
	{
		printf("too many parameters!\n%s",USAGE);
		return EXIT_FAILURE;
	}
	if(argc<MIN_ARGS)
	{
		printf("please supply a file!\n%s",USAGE);
		return EXIT_FAILURE;

	}

	//****** main code starts here ********
	file=fopen(argv[1],"r");
	if(file==NULL)
	{
		printf("file \"%s\" not found\n",argv[1]);
		return 1;
	}

	if(isParenthesisCorrect(file))
	{
		printf("Ok\n");
	}
	else
	{
		printf("Bad structure\n");
	}

	fclose(file);

	return EXIT_SUCCESS;
}
