/**
 * file: Board.c
 * written for ex. 3 in labc course, by Ohad Cohen <ohadcn@cs.huji.ac.il>
 * contains methods for tic tac toe game
 */

#include "Board.h"
#include "ErrorHandle.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define EMPTY_CELL ' '
#define X_CELL 'X'
#define O_CELL 'O'

#define DEFUALT_COLS 10
#define DEFUALT_ROWS 10

#define PRINT_WIDTH 10
#define PRINT_HEIGHT 10
#define PRINT_SPACE 2

#define STARTING_PLAYER X_CELL

#define SEQ_LENGTH 5

#define ERROR 'E'

#define getOtherPlayer(A) X_CELL+O_CELL-A

#define MAX(A,B) (((A)>(B))?(A):(B))

typedef struct cell
{
    int col,row;
}cell;

typedef struct Board
{
    char** table;
    char turn;
    cell size,lastPlayed;
}Board;

//************  private functions  ***********

/*
 * enlarge the table of board to feet rows and cols
 * if it needs to enlarge, it double the size of the requested dimension
 * this function returns true and reallocate space for the new table in case of success
 * or returns false and do nothing otherwise
 */
static bool enlargeTable(BoardP board,const int rows,const int cols)
{
    int i,j;
    //if current size is enouth, leave it
    //otherwise new size is twice the requested size
    int newSizeRows=(rows>=board->size.row?2*rows:board->size.row),
            newSizeCols=(cols>=board->size.col?2*cols:board->size.col);
    char* temp;
    char** newTable=(char**)realloc(board->table,newSizeRows*sizeof(char*));
    if(newTable==NULL)
    {
        return false;
    }
    board->table=newTable;

    for(i=0;i<board->size.row;i++)
    {
        temp=(char*)realloc(board->table[i],newSizeCols*sizeof(char));
        if(temp==NULL)
        {
            return false;
        }
        board->table[i]=temp;

        //initialize the new cells to empty ones
        for(j=board->size.col;j<newSizeCols;j++)
        {
            board->table[i][j]=EMPTY_CELL;
        }
    }

    for(i=board->size.row;i<newSizeRows;i++)
    {
        temp=calloc(newSizeCols,sizeof(char));
        if(temp==NULL)
        {
            //we can't be sure that memory allocated in this loop will be freed in case of error,
            //so we free it here
            for(j=board->size.col;j<i;j++)
            {
                free(board->table[i]);
            }
            return false;
        }
        board->table[i]=temp;

        for(j=0;j<newSizeCols;j++)
        {
            board->table[i][j]=EMPTY_CELL;
        }
    }
    board->size.col=newSizeCols;
    board->size.row=newSizeRows;
    return true;
}

/*
 * returns the number of the digits in the number num
 * (in base 10)
 */
static int numOfDigits(int num)
{
    int i;
    for(i=1;num>0;num/=10,i++);
    return i-1;
}

//************ public functions *********


/*
 * Allocate memory for a default empty board (size 10X10) and return it.
 * If run out of memory, free all the memory that was already allocated by the function,
 * report error MEM_OUT to the standard error and return NULL.
 */
BoardP createNewDefaultBoard()
{
    return createNewBoard(DEFUALT_ROWS,DEFUALT_COLS);
}

/*
 * Allocate memory for an empty board (size rows X cols) and return it.
 * If run out of memory, free all the memory that was allocate, report error MEM_OUT and return NULL.
 */
BoardP createNewBoard(int rows, int cols)
{
    BoardP newBoard=(BoardP)malloc(sizeof(Board));
    int i,j;
    newBoard->size.row=rows;
    newBoard->size.col=cols;
    newBoard->turn=STARTING_PLAYER;
    newBoard->table=(char**)calloc(newBoard->size.row,sizeof(char*));
    if((newBoard->table)==NULL)
    {
        reportError(MEM_OUT);
        return NULL;
    }
    for(i=0;i<newBoard->size.row;i++)
    {
        newBoard->table[i]=(char*)calloc(newBoard->size.col,sizeof(char));
        if((newBoard->table[i])==NULL)
        {
            reportError(MEM_OUT);
            freeBoard(newBoard);
            return NULL;
        }
        for(j=0;j<newBoard->size.row;j++)
        {
            newBoard->table[i][j]=EMPTY_CELL;
        }
    }
    //avoid valgrind warnings for using uninitialized values when PlayBoard calls to getWinner() before the first move
    //or when the first move was ilegal
    newBoard->lastPlayed.col=0;
    newBoard->lastPlayed.row=0;
    return newBoard;
}

/*
 * Duplicate the original board and return a new one.
 * The old board stays exactly the same (its memory is not freed etc).
 * In case the function runs out of memory while creating the new board, MEM_OUT error is reported and NULL is
 * returned.
 * The old board stays the same. You should free all the memory that was already allocated for the new board.
 */
BoardP duplicateBoard(ConstBoardP originalBoard)
{
    assert(originalBoard!=NULL);
    BoardP newBoard=(BoardP)malloc(sizeof(Board));
    int i;
    newBoard->size.col=originalBoard->size.col;
    newBoard->size.row=originalBoard->size.row;
    newBoard->turn=originalBoard->turn;
    newBoard->lastPlayed.col=originalBoard->lastPlayed.col;
    newBoard->lastPlayed.row=originalBoard->lastPlayed.row;
    newBoard->table=(char**)calloc(newBoard->size.row,sizeof(char*));
    if((newBoard->table)==NULL)
    {
        reportError(MEM_OUT);
        return NULL;
    }
    for(i=0;i<newBoard->size.row;i++)
    {
        newBoard->table[i]=(char*)calloc(newBoard->size.col,sizeof(char));
        if((newBoard->table[i])==NULL)
        {
            reportError(MEM_OUT);
            freeBoard(newBoard);
            return NULL;
        }
        memcpy(newBoard->table[i],originalBoard->table[i],(newBoard->size.col)*sizeof(char));
    }
    return newBoard;
}


/*
 * Check the value of the square row,col on the board. Assume the squares index is starting from zero.
 * Return 'X' if 'X' owns the square, 'O' (big o, not a zero) if 'O' owns the square, and ' ' (a space) if it's an
 * empty square.
 * If row or col are negative, report an error OUT_OF_BOUND and return 'E'.
 * If (row,col) is out of the current memory allocated area, then it must be an empty square - return ' ' (a space).
 */
char getBoardSquare(ConstBoardP theBoard, int row, int col)
{
    assert(theBoard!=NULL);
    if(row<0 || col<0)
    {
        reportError(OUT_OF_BOUND);
        return ERROR;
    }

    else if(col>=theBoard->size.col || row>=theBoard->size.row)
    {
        return EMPTY_CELL;
    }

    else
    {
        return theBoard->table[row][col];
    }
}


/*
 * Make a move: mark on location (row,col) the value 'val'.
 * If 'val' is not 'X' or 'O', report BAD_VAL and do nothing.
 * If row or col are negative report OUT_OF_BOUND and do nothing.
 * If square (row,col) is already full, report SQUARE_FULL and do nothing.
 * If val is 'X' but it's 'O' turn (or val is 'O' but it's 'X' turn) - report WRONG_TURN and do nothing.
 * If sqaure (row,col) is out of the current memory area - allocate more memory
 * for a board making sure to increase the size of the required dimension(s) to
 * make the move possible.
 * If run out of memory during the allocation, report MEM_OUT and do nothing (the board should
 * stay at the same situation as it was before the function call).
 * If the function success, update information require for getWinner() function.
 * If everything is OK, return TRUE. Otherwise (an error occure) return FALSE.
 */
Boolean putBoardSquare(BoardP theBoard, int row, int col, char val)
{
    assert(theBoard!=NULL);
    if(val!=X_CELL && val !=O_CELL)
    {
        reportError(BAD_VAL);
        return FALSE;
    }
    else if(row<0 || col<0)
    {
        reportError(OUT_OF_BOUND);
        return FALSE;
    }
    else if(val !=theBoard->turn)
    {
        reportError(WRONG_TURN);
        return FALSE;
    }
    else if(getBoardSquare(theBoard,row,col)!=EMPTY_CELL)
    {
        reportError(SQUARE_FULL);
        return FALSE;
    }//done error checking

    if(row>=theBoard->size.row || col>=theBoard->size.col)
    {
        if(!enlargeTable(theBoard,row,col))
        {
            reportError(MEM_OUT);
            return FALSE;
        }
    }
    theBoard->table[row][col]=val;
    theBoard->lastPlayed.col=col;
    theBoard->lastPlayed.row=row;
    theBoard->turn=getOtherPlayer(theBoard->turn);
    return TRUE;

}


/*
 * Check if there's a winner on the board - a player that owns 5 squares in a line (vertical, horizontal or
 * diagonal).
 * Return the player ('X' / 'O') is such exists, or ' ' (space) otherwise.
 * Should work in O(1) - use information provided by the putBoardSquare() function.
 */
char getWinner(ConstBoardP board)
{
    assert(board!=NULL);
    int seqSize=0;
    int i;
    char lastPlayer=getOtherPlayer(board->turn);

    //test size vertically
    for(i=1;getBoardSquare(board,board->lastPlayed.row+i,board->lastPlayed.col)==lastPlayer;i++);
    seqSize=i;
    //when testing backwards, make sure you are not getting inside the negative side of the board
    for(i=1;board->lastPlayed.row>=i && getBoardSquare(board,board->lastPlayed.row-i,board->lastPlayed.col) ==
                                                                                                lastPlayer;i++);
    if(seqSize+i>SEQ_LENGTH)
    {
        return lastPlayer;
    }

    //test size horizontally
    for(i=1;getBoardSquare(board,board->lastPlayed.row,board->lastPlayed.col+i)==lastPlayer;i++);
    seqSize=i;
    for(i=1;board->lastPlayed.col>=i && getBoardSquare(board,board->lastPlayed.row,board->lastPlayed.col-i)
                                                                                                ==lastPlayer;i++);
    if(seqSize+i>SEQ_LENGTH)
    {
        return lastPlayer;
    }

    //test size diagonally
    for(i=1;getBoardSquare(board,board->lastPlayed.row+i,board->lastPlayed.col+1)==lastPlayer;i++);
    seqSize=i;
    for(i=1;board->lastPlayed.row>=i && board->lastPlayed.col>=i && getBoardSquare(board,board->lastPlayed.row-i
                                                                       ,board->lastPlayed.col-i)==lastPlayer;i++);
    if(seqSize+i>SEQ_LENGTH)
    {
        return lastPlayer;
    }

    //test size diagonally (reversed)
    for(i=1;board->lastPlayed.row>=i && getBoardSquare(board,board->lastPlayed.row-i,board->lastPlayed.col+i)
                                                                                                ==lastPlayer;i++);
    seqSize=i;
    for(i=1;board->lastPlayed.col>=i && getBoardSquare(board,board->lastPlayed.row+i,board->lastPlayed.col-i)
                                                                                                ==lastPlayer;i++);
    if(seqSize+i>SEQ_LENGTH)
    {
        return lastPlayer;
    }

    return EMPTY_CELL;
}

/*
 * Free all the memory allocated for the board. It's the user responsibility to call this function before
 * exiting the program.
 */
void freeBoard(BoardP board)
{
    int i;
    for(i=0;i<board->size.row;i++)
    {
        free(board->table[i]);
    }
    free(board->table);
    free(board);
}

/*
 * Print the board from position (row,col).
 * If row or col are negative, report OUT_OF_BOUND and do nothing.
 * Squares outside of the current memory location should be printed as empty squares.
 */
void printBoard(ConstBoardP board, int row, int col)
{
    assert(board!=NULL);
    int numSize=MAX(numOfDigits(row+PRINT_WIDTH-1),numOfDigits(col+PRINT_HEIGHT-1))+PRINT_SPACE;
    int i,j;
    if(row<0 || col<0)
    {
        reportError(OUT_OF_BOUND);
        return;
    }

    printf("\nPrinting current state of the board for location (row,col)=(%d,%d)\n\n",row,col);
    printf("%*c",numSize,' ');
    for(i=0;i<PRINT_WIDTH;i++)
    {
        printf("%*d",numSize,col+i);
    }

    for(i=0;i<PRINT_WIDTH;i++)
    {
        printf("\n%-*d",numSize,row+i);
        for(j=0;j<PRINT_HEIGHT;j++)
        {
            printf("%*c",numSize,getBoardSquare(board,row+i,col+j));
        }
    }
    printf("\n\n");
}
