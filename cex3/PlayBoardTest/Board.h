#ifndef BOARD_H
#define BOARD_H

typedef struct Board* BoardP;
typedef const struct Board* ConstBoardP;
typedef enum {FALSE, TRUE} Boolean;


/*
 * Allocate memory for a default empty board (size 10X10) and return it.
 * If run out of memory, free all the memory that was already allocated by the function, 
   report error MEM_OUT to the standard error and return NULL.
 */
BoardP createNewDefaultBoard();


/*
 * Allocate memory for an empty board (size rows X cols) and return it.
 * If run out of memory, free all the memory that was allocate, report error MEM_OUT and return NULL.
 */
BoardP createNewBoard(int rows, int cols);

/*
 * Duplicate the original board and return a new one.
 * The old board stays exactly the same (its memory is not freed etc).
 * In case the function runs out of memory while creating the new board, MEM_OUT error is reported and NULL is returned.
   The old board stays the same. You should free all the memory that was already allocated for the new board.
 */
BoardP duplicateBoard(ConstBoardP originalBoard);


/*
 * Check the value of the square row,col on the board. Assume the squares index is starting from zero.
 * Return 'X' if 'X' owns the square, 'O' (big o, not a zero) if 'O' owns the square, and ' ' (a space) if it's an empty square.
 * If row or col are negative, report an error OUT_OF_BOUND and return 'E'.
 * If (row,col) is out of the current memory allocated area, then it must be an empty square - return ' ' (a space).
 */
char getBoardSquare(ConstBoardP theBoard, int row, int col);


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
 * If everything is OK, return TRUE. Otherwise (an error accure) return FALSE.
 */
Boolean putBoardSquare(BoardP theBoard, int row, int col, char val);


/*
 * Check if there's a winner on the board - a player that owns 5 squares in a line (vertical, horizontal or diagonal).
 * Return the player ('X' / 'O') is such exists, or ' ' (space) otherwise.
 * Should work in O(1) - use information provided by the putBoardSquare() function.
 */
char getWinner(ConstBoardP board);

/*
 * Free all the memory allocated for the board. It's the user responsibility to call this function before
   exiting the program.
 */
void freeBoard(BoardP board);

/*
 * Print the board from position (row,col).
 * If row or col are negative, report OUT_OF_BOUND and do nothing.
 * Squares outside of the current memory location should be printed as empty squares.
 */
void printBoard(ConstBoardP board, int row, int col);


#endif
