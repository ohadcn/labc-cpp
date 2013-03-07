#include <assert.h>
#include <stdio.h>
#include <stdlib.h>            /* For exit */
#include "Board.h"

int main()
{
    int curRow = 0, curCol = 0;
    Boolean moveSucc;
    char nextTurn = 'X';
    BoardP theBoard = createNewDefaultBoard();
    if (theBoard == NULL) 
    {
		// createNewDefaultBoard() reports on the error.
		exit(1);
	}
    while (1)
    {
        int sel, selsucc, getRow, getCol;
        printBoard(theBoard, curRow, curCol);
        printf("What do you want to do?\n");
        printf("1. Make a move\n");
        printf("2. Change print location.\n");
        printf("3. Quit.\n");
        selsucc = scanf("%d", &sel);
        if (sel < 1 || sel > 3 || selsucc != 1)
        {
            printf("Illegal selection.\n\n");
            freeBoard(theBoard);
            return 1;
        }
        if (sel == 3)
        {
            freeBoard(theBoard);
            break;
        }
        printf("Choose location (choose row first): (");
        scanf("%d", &getRow);
        printf("Choose location (now choose col): (%d,", getRow);
        scanf("%d", &getCol);
        printf("\n\n\n");
        if (sel == 1)
        {
            moveSucc = putBoardSquare(theBoard, getRow, getCol, nextTurn);
            if (getWinner(theBoard) == 'X')
            {
                printBoard(theBoard, curRow, curCol);
                printf("\n\nX wins the game!!!\n\n");
                freeBoard(theBoard);
                break;
            }
            else
            if (getWinner(theBoard) == 'O')
            {
                printBoard(theBoard, curRow, curCol);
                printf("\n\nO wins the game!!!\n\n");
                freeBoard(theBoard);
                break;
            }
        }
        if (sel == 1 && moveSucc)
        {
            if (nextTurn == 'X')
                nextTurn = 'O';
            else
                nextTurn = 'X';
        }
        if (sel == 2)
        {
            curRow = getRow;
            curCol = getCol;
        }
    }
    return 0;
}
