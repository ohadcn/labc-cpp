/**
 * MyIntFunctions.c
 * functions for handeling hash table of integers
 * written by ohad cohen <ohadcn@cs.huji.ac.il>
 * ex. 4, c programing course
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "MyIntFunctions.h"

/**
 * calculate hash of an integer
 * the hash is just N mod tableSize
 */
int IntFcn (const void *key, size_t tableSize)
{
    assert(key!=NULL);
    int val=(*(int*)key);
    if(val<0)
    {
        val-=val*tableSize;
    }
    return val%tableSize;
}

/**
 * print the number
 * equivalent to calling printf("%d",*(int*)key)
 */
void IntPrint (const void *key)
{
    assert(key!=NULL);
    printf("%d",*(int*)key);
}

/**
 * compare two integers
 * return non-zero if the numbers are equal, and zero if they are not
 */
int IntCompare (const void *key1, const void *key2)
{
    assert(key1!=NULL && key2!=NULL);    
    return (*(int*)(key1)==*(int*)(key2));
}


