/**
 * MyStringFunctions.c
 * functions for handeling hash table of strings
 * written by ohad cohen <ohadcn@cs.huji.ac.il>
 * ex. 4, c programing course
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyStringFunctions.h"
#include <assert.h>

#define END_OF_STRING '\0'

/**
 * calculate hash of a string
 */
int StringFcn (const void *key, size_t tableSize)
{
    assert(key!=NULL);
    int asciiSum=0;
    int i;
    for(i=0;((char*)key)[i]!=END_OF_STRING;i++)
    {
        asciiSum+=((char*)key)[i];
    }
    return asciiSum%tableSize;
}

/**
 * print the string
 * equivalent to calling printf("%s",*(int*)key)
 */
void StringPrint (const void *key)
{
    assert(key!=NULL);
    printf("%s",(char*)key);
}

/**
 * compare two strings
 * return non-zero if the are equal, and zero if they are not
 */
int StringCompare (const void *key1, const void *key2)
{
    assert(key1!=NULL && key2!=NULL);
    return (!strcmp((char*)key1,(char*)key2));
}


