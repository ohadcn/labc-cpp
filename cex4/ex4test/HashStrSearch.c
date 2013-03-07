#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GenericHashTable.h"
#include "MyStringFunctions.h"


int main(int argc, char *argv[])
{
    // (1) read table size and a key to find
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: GenericHashTable <table size> <key (string up to 9 chars)>\n");
        exit(1);
    }

    unsigned int tableSize;
    char val[10];
    sscanf(argv[1], "%d", &tableSize);
    sscanf(argv[2], "%s", val);

    // (2) create the table
    
    TableP table =  CreateTable(tableSize, &StringFcn, &StringPrint, &StringCompare);
    if (table == NULL) 
    {
        printf("ERROR: failed to create table!\n");
        return 0;
    }

    
    // (3) insert objects
    
    char* str = "abcdefghijlmnop";
    char* kstr;
    unsigned int j;
    Boolean insert_object_j;
    for (j=0; j<strlen(str)-4; j++) 
    {
        kstr = malloc(sizeof(char) * 5);
        strncpy(kstr,str+j,4);
        kstr[4] = '\0';
        ObjectP strobj = CreateObject(kstr);
        if (strobj == NULL) 
	{
            printf("ERROR: failed to create object %d!\n", j);
            return 0;
        }
        insert_object_j = InsertObject(table, strobj);
        if (insert_object_j == FALSE) 
	{
            printf("ERROR: failed to insert object %d to the table!\n", j);
            return 0;     
        }
    }

    // (4) print the table
    PrintTable(table);

    // (5) look for the key
    
    int arrCell;
    int listNode;
    
    FindObject(table, val, &arrCell, &listNode);
    printf("%s\t%d\t%d\n", val, arrCell, listNode);
    
    
    // (6) free the table
    FreeTable(table);

    return 0;
}




