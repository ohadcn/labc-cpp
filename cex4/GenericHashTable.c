/**
 * GenericHashTable.c
 * functions for handeling hash table for objects of any kind
 * written by ohad cohen <ohadcn@cs.huji.ac.il>
 * ex. 4, c programing course
 */

//******** includes *********
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "GenericHashTable.h"
#include "TableErrorHandle.h"

//********* defines *********

/**
 * how much to resize the table, when need
 */
#define RESIZE_FACTOR (2)

//the maximum size of each cell in the array
#define MAX_CELL_SIZE (2)

//this value is returned bt find when looking for key that doesn't exists in the table
#define NOT_FOUND (-1)

//printing separator
#define CELL_SEPARATOR "\t-->\t"

//********* structs ********

/**
 * this struct holds a key in hash table
 * you can use those objects to hold any kind of information you like
 * but keep it using the same type of objects so you won't missed it up
 */
typedef struct Object
{
    void *key;
    ObjectP next;

}Object;

/**
 * this struct holds a hash table of 'Object's
 */
typedef struct Table
{
    int size;//origanal size
    int arrSize;
    int factor;//ratio; how much the array was stretched
    HashFcn hash;
    PrintFcn printObj;
    ComparisonFcn compare;
    ObjectP *theTable;
}Table;

//********* private functions **********


/**
 * enlarge the table by RESIZE_FACTOR and put each cell of the old table in cell
 * [OLD_INDEX*RESIZE_FACTOR] of the new one
 * this function also free the memory of the old table
 */
static bool enlargeTable(TableP table)
{
    assert(table!=NULL && table->theTable!=NULL);
    int i;
    ObjectP *newTable=(ObjectP*)calloc(table->arrSize*RESIZE_FACTOR,sizeof(ObjectP));
    if(newTable==NULL)
    {
        return false;
    }

    for(i=0;i<table->arrSize;i++)
    {
        newTable[i*RESIZE_FACTOR]=table->theTable[i];
    }

    //update other fields of the struct
    free(table->theTable);
    table->theTable=newTable;
    table->arrSize*=RESIZE_FACTOR;
    table->factor*=RESIZE_FACTOR;
    return true;
}

/**
 * a helper function for putInCell
 * this function gets an ObjectP, and a pointer to ObjectP, and tries to put object in objPlace, or in
 * his next's up to MAX_CELL_SIZE levels
 */
static bool putInCellHelper(const ObjectP object,ObjectP* objPlace,int index)
{
    if(index>=MAX_CELL_SIZE)
    {
        return false;
    }
    if((*objPlace)==NULL)
    {
        (*objPlace)=object;
        return true;
    }
    else
    {
        return putInCellHelper(object,&(*objPlace)->next,index+1);
    }
}


/**
 * try to put <object> in <cell> of <table>
 * return true on success and false if cell is full
 * cell is full if it already holds MAX_CELL_SIZE objects
 */
static bool putInCell(TableP table,const ObjectP object,int cell)
{
    assert(table!=NULL && table->theTable!=NULL);
    return putInCellHelper(object,table->theTable+cell,0);
}

/**
 * i just found that my IDE has nice autonatic format for documantation, i'll try to use it more next time..
 * @brief findInCell find if a <key> appears in a <cell> - a linked list
 * @param key the key to look for
 * @param cell the cell to look in
 * @param compare the comparison function, see ComparisonFcn reference for using and creating such
 * @return the index of <key> in <cell>, NOT_FOUND if <cell> doesn;t contain <key>
 */
static int findInCell(const void *key,const ObjectP cell,const ComparisonFcn compare)
{
    int result;
    if(cell==NULL)
    {
        return NOT_FOUND;
    }
    if(compare(key,cell->key))
    {
        return 0;
    }
    return ((result=findInCell(key,cell->next,compare))!=NOT_FOUND?result+1:result);
}

/**
 * @brief printCell prints a cell, a linked list of elements
 * @param cell the cell to print
 * @param print the printing function
 */
static void printCell(const ObjectP cell,const PrintFcn print)
{
    if(cell==NULL)
    {
        return;
    }
    print(cell->key);
    printf(CELL_SEPARATOR);
    printCell(cell->next,print);
}

//******** public functions ***********

/**
 * Allocate memory for an object which points to the given key.
 * If run out of memory, free all the memory that was already allocated by the function,
 * report error MEM_OUT to the standard error and return NULL.
 */
ObjectP CreateObject(void *key)
{
    ObjectP newObj=malloc(sizeof(Object));
    if(newObj==NULL)
    {
        ReportError(MEM_OUT);
        return NULL;
    }
    newObj->key=key;
    newObj->next=NULL;
    return newObj;
}


/**
 * Allocate memory for a hash table with which uses the given functions.
 * tableSize is the number of cells in the hash table.
 * If run out of memory, free all the memory that was already allocated by the function,
 * report error MEM_OUT to the standard error and return NULL.
 */
TableP CreateTable(size_t tableSize, HashFcn hfun, PrintFcn pfun, ComparisonFcn fcomp)
{
    if(hfun==NULL || pfun==NULL || fcomp==NULL)
    {
        ReportError(GENERAL_ERROR);
        return NULL;
    }

    TableP newTable=(TableP)malloc(sizeof(Table));
    if(newTable==NULL)
    {
            ReportError(MEM_OUT);
            return NULL;
    }

    newTable->factor=1;
    newTable->compare=fcomp;
    newTable->hash=hfun;
    newTable->size=tableSize;
    newTable->arrSize=tableSize;
    newTable->printObj=pfun;
    newTable->theTable=(ObjectP*)calloc(newTable->size,sizeof(ObjectP));
    if(newTable->theTable==NULL)
    {
            ReportError(MEM_OUT);
            free(newTable);
    }
    return newTable;
}


/**
 * Insert an object to the table.
 * If all the cells appropriate for this object are full, duplicate the table.
 * If run out of memory during the table duplication, report
 * MEM_OUT and do nothing (the table should stay at the same situation
 * as it was before the duplication).
 * If everything is OK, return TRUE. Otherwise (an error occured) return FALSE.
 */
Boolean InsertObject(TableP table, ObjectP object)
{
    if(table==NULL || object==NULL)
    {
        ReportError(GENERAL_ERROR);
        return FALSE;
    }
    int cell=table->hash(object->key,table->size)*table->factor;
    int i;
    for(i=0;i<table->factor;i++)
    {
        if(putInCell(table,object,cell+i))
        {
            return TRUE;
        }
    }

    //if we are here there is no place in the table so we should allocate new one
    if(enlargeTable(table))
    {
        putInCell(table,object,cell*RESIZE_FACTOR+1);
        return TRUE;
    }
    else //probably problem with new memory allocation
    {
        ReportError(MEM_OUT);
        return FALSE;
    }
}



/**
 * Search the table and look for an object with the given key.
 * If such object is found fill its cell number into arrCell (where 0 is the
 * first cell), and its placement in the list into listNode (when 0 is the
 * first node in the list, i.e. the node that is pointed from the table
 * itself).
 * If the key was not found, fill both pointers with value of NOT_FOUND.
 */
void FindObject(ConstTableP table, const void* key, int* arrCell, int* listNode)
{
    if(table==NULL || key==NULL || arrCell==NULL || listNode == NULL)
    {
        ReportError(GENERAL_ERROR);
        return;
    }

    int cell=table->hash(key,table->size)*table->factor;
    int i,j;
    for(i=0;i<table->factor;i++)
    {
        if((j=findInCell(key,table->theTable[cell+i],table->compare))!=NOT_FOUND)
        {
            *arrCell=cell+i;
            *listNode=j;
            return;
        }
    }

    //not found on the list
    *arrCell=NOT_FOUND;
    *listNode=NOT_FOUND;
}


/**
 * Print the table (use the format presented in PrintTableExample).
 */
void PrintTable(ConstTableP table)
{
    if(table == NULL || table->theTable==NULL)
    {
        ReportError(GENERAL_ERROR);
        return;
    }
    int i;
    for(i=0;i<table->arrSize;i++)
    {
        printf("[%d]\t",i);
        printCell(table->theTable[i],table->printObj);
        printf("\n");
    }
}


/**
 * Free all the memory allocated for an object, including the memory allocated
 * for the key.
 * Use this function when you free the memory of the table.
 */
void FreeObject(ObjectP object)
{
    if(object==NULL)
    {
        return;
    }
    free(object->key);
    FreeObject(object->next);
    free(object);
}


/**
 * Free all the memory allocated for the table.
 * It's the user responsibility to call this function before exiting the program.
 */
void FreeTable(TableP table)
{
    if(table==NULL)
    {
        return;
    }
    int i;
    for(i=0;i<table->arrSize;i++)
    {
        FreeObject(table->theTable[i]);
    }
    free(table->theTable);
    free(table);
}
