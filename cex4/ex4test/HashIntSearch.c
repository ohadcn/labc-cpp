#include <stdio.h>
#include <stdlib.h>
#include "GenericHashTable.h"
#include "MyIntFunctions.h"

#define MINIMAL_VAL -15
#define MAXIMAL_VAL 15

int main(int argc, char *argv[])
{

    // (1) read table size and a key to find
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: GenericHashTable <table size> <key>\n");
        exit(1);
    }

    unsigned int tableSize;
    int val;
    sscanf(argv[1], "%d", &tableSize);
    sscanf(argv[2], "%d", &val);
    
    
    // (2) create the table
    
    TableP table = CreateTable(tableSize, &IntFcn, &IntPrint, &IntCompare);
    if (table == NULL) 
    {
        printf("ERROR: failed to create table!\n");
        return 0;
    }
    

    // (3) insert objects
    
    int i;
    Boolean insert_object_i;
    for (i=MINIMAL_VAL; i<MAXIMAL_VAL; i++) 
    {
        int *p = malloc(sizeof(int));
        *p = i;
        ObjectP object = CreateObject(p);
        if (object == NULL) 
	{
            printf("ERROR: failed to create object %d!\n", i);
            return 0;
        }
        insert_object_i = InsertObject(table, object);
        if (insert_object_i == FALSE) 
	{
            printf("ERROR: failed to insert object %d to the table!\n", i);
            return 0;   
        }
    }

    // (4) print the table
    PrintTable(table);

    // (5) look for the key
    
    int arrCell;
    int listNode;
    
    FindObject(table, &val, &arrCell, &listNode);
    printf("%d\t%d\t%d\n", val, arrCell, listNode);


    // (6) free the table
    FreeTable(table);
        
    return 0;
}
