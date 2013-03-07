//CheckDependency.c
//this code has been writen for ex2 in c course at huji university
//by Ohad Cohen <ohadcn@cs.huji.ac.il>


/**
 * test a dependacy tree for cycles
 * this program gets a file by the format file:comma-seperated list of dependecies and finds out
 * if this dependacy tree contain cycles or not
 * input:a file name
 * output:"Cyclic Dependency" if the tree has cycles;"Acyclic Dependencies" if not
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//const from ex. assumptions
#define MAX_FILES 1000
#define MAX_DEPENDS_PER_FILE 100
#define MAX_FILENAME 64
#define MAX_LINE_LENGTH 1000


//this message will be presented to the user in case of ilegal parameters
#define USAGE "usage:CheckDependency <filename>\n"

//the char used to seperate filenames
#define NAMES_SEPERATOR ","

//the desired number of arguments
#define MIN_ARGS 2
#define MAX_ARGS 2


//those defines are used in the DFS algorythm
#define NOT_VISITED 0
#define PRE_VISITED 1
#define VISITED 2

//used for empty cells in the dependancy list
#define EMPTY -1

/**
 * this struct holds a filename and it's dependacies.
 * the usage of that exact struct is demanded by ex. description
 */
typedef struct fileslist
{
	char filename[MAX_FILENAME+1];
	int depends[MAX_DEPENDS_PER_FILE];
}fileslist;

/**
 * recursive helper method for testing dependecy tree for cycles; this tree search for cycles starting
 * at "current" parameter
 */
int cyclesCheckRecursive(fileslist dependancies[],int numOfFiles,int isVisited[],int current)
{
	int i=-1;//used in a loop, for cross-platform support i should put it here and not near the loop

	if(isVisited[current])
	{
		if(isVisited[current]==PRE_VISITED)
		{
			return true;
		}
		if(isVisited[current]==VISITED)
		{
			return false;
		}
	}

	isVisited[current]=PRE_VISITED;

	while(dependancies[current].depends[++i]!=EMPTY)
	{
		if(cyclesCheckRecursive(dependancies,numOfFiles,isVisited,dependancies[current].depends[i]))
		{
			return true;
		}

	}
	isVisited[current]=VISITED;

	return false;
}

/**
 * this method gets a dependacy tree and the number of files in it and test it for having cycles
 * this method returns 1 if there are cycles or 0 otherwise
 */
int hasCycles(fileslist dependancies[],int numOfFiles)
{
	//it could have been more efficient to use numOfFiles insteed of MAX_FILES, but ex. description demand
	//using only fixed-seize arrays
	int checked[MAX_FILES]={NOT_VISITED};
	int i;

	for(i=0;i<numOfFiles;i++)
	{
		if(cyclesCheckRecursive(dependancies,numOfFiles,checked,i))
		{
			return true;
		}
	}

	return false;
}

/**
 * this method get files list, and name of requested file and finds the index of file <name> in the array
 * if the file is not included in the list the method adds it (this method also update arrSize after adding a file)
 */
int getIndexForName(fileslist dependancies[],int *arrSize,char *name)
{
	int i;
	for(i=0;i<*arrSize;i++)
	{
		if(!strcmp(name,dependancies[i].filename))
		{
			return i;
		}
	}

	strcpy(dependancies[*arrSize].filename,name);

	for(i=0;i<MAX_DEPENDS_PER_FILE;i++)
	{
		dependancies[*arrSize].depends[i]=EMPTY;
	}

	return (*arrSize)++;
}

/**
 * this method reads dependacy tree from file <filename> to filelist <dependacies>
 * and returns the number of files in the list
 * if the file is not found the function quit the program
 */
int readDependancyFromFile(char *filename,fileslist dependancies[])
{
	FILE* file=fopen(filename,"r");
	if(file==NULL)
	{
		printf("file \"%s\" not found\n%s",filename,USAGE);
		exit(EXIT_FAILURE);
	}


	int numOfFiles=0;
	while(!feof(file))
	{

		int currentFileIndex,currentDepIndex,depsSize=0;
		char *depName,//this one holds the name of the currnt analyzed dep.
		name[MAX_FILENAME+1],//the name of the file
		deps[MAX_LINE_LENGTH+1];//the line of the dependacies

		//normal %s: %s is not so stable in such cases, so i verify that the : and the space won't get in.
		fscanf(file,"%[^: ]: %s\n",name,deps);

		currentFileIndex=getIndexForName(dependancies,&numOfFiles,name);
		while(dependancies[currentFileIndex].depends[depsSize]!=-1)
		{
			depsSize++;
		}


		depName=strtok(deps,NAMES_SEPERATOR);
		while(depName!=NULL)
		{
			currentDepIndex=getIndexForName(dependancies,&numOfFiles,depName);
			dependancies[currentFileIndex].depends[depsSize++]=currentDepIndex;
			depName=strtok(NULL,NAMES_SEPERATOR);
		}

	}

	fclose(file);

	return numOfFiles;
}

int main(int argc,char **argv)
{
	int numOfFiles;
	fileslist dependancies[MAX_FILES];

	//remember that argv[0] is the execution command!
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

	numOfFiles=readDependancyFromFile(argv[1],dependancies);


	if(hasCycles(dependancies,numOfFiles))
	{
		printf("Cyclic Dependency\n");
	}
	else
	{
		printf("Acyclic Dependencies\n");
	}


	return EXIT_SUCCESS;
}
