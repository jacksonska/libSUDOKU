#ifndef __LIB_H__
#define __LIB_H__

#include "libSUDOKU.h"

/**
 * getLibSudoku - Entry point to the library  
 * 
 * @param
 *    void
 * @return
 *    LIB_SUDOKU * - Pointer to the solver object that will solve boards.
 * 
 * example code:
 * LIB_SUDOKU * libsudoku = NULL;
 * SUDOKU_SOLVER * solver = NULL;
 * SUDOKU_B * board1 = NULL;
 * 
 * libsudoku = getLibSudoku();
 * libsudoku->solver->vft(create(&solver)) 
**/
LIB_SUDOKU * getLibSudoku(void);


/**
 * readBoardFromFile - Reads a board from file and returns board
 * @param
 *    filename - name of the file the board is stored in
 *    board - Pointer to the board to be printed
 * @return
 *    enum S_STATUS - status of the board reading
 * @note
 *    -filename needs to be .txt format
 *    -the first character needs to be the dimensions of the board
 *    -board should be NULL to start - ie not allocated
 *    -The board needs to be deallocated by the USER.
 * 
 **/
enum S_STATUS readBoardFromFile (
    IN const char * filename, 
    OUT SUDOKU_B ** board
);

/*
The contents of this ENTIRE file were written by Jackson Skaaden
*/


/**
 * removeBoard - Function that deallocates the given board.
 *   it's a fire and forget, if the board doesn't exist, the funtion
 *   does nothing.
 * @param
 *    board - the board to deallocate
 * @return
 *   void
**/
void removeBoard (
    IN SUDOKU_B ** board
);

#endif /* __LIB_H__ */