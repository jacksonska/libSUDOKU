#ifndef __SUDOKU_H__ 
#define __SUDOKU_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define IN
#define OUT
#define S_INT int

enum S_STATUS {OK = 1, FAIL = 0, NO_RESOURCES = -1, BAD_PARAM = -2};
enum B_STATUS {SOLVED = 1, UNSOLVED = 0, INVALID = -1};


/**
 * Structure to store the state of a sudoku board.
 * @note 
 *  -The board must be of size NxN
 *  -Stores the board double array
 *  -Size variable for the length of the board
**/
typedef struct SUDOKU_B
{
    /**
     * Board's loction in memory - Treat as 2D array
    **/
    S_INT * board;

    /**
     * Status of the board - i.e. "SOLVED", "INVALID", "UNSOLVED"
    **/
    enum B_STATUS status;

} SUDOKU_B;

typedef struct SUDOKU_SOLVER_VFT 
{
    /** 
     * create - Creates a sudoku board solver, Can solve any board
     * @param
     *    solver - Pointer to the calling Sudoku Solver
     * @return
     *   S_STATUS - Status of the solver's creation
    **/
    enum S_STATUS (* create) (
        IN struct SUDOKU_SOLVER ** solver
    );

    /** 
     * destroy - Destroys a sudoku board solver
     * @param
     *    solver - Pointer to the Sudoku Solver
     * @return
     *   void
    **/
    void (* destroy) (
        IN struct SUDOKU_SOLVER ** solver
    );

    /**
     * solve - function Pointer to a Sudoku Puzzle solver
     * @param
     *    solver - Pointer to solver calling the function
     *    input - Pointer to the board that is to be solved. Will be solved in place 
     *      (The SUDOKU_B * input will become the output)
     * @return
     *    S_STATUS - status of the solving algorithm
     **/
    enum S_STATUS (* solve) (
        IN struct SUDOKU_SOLVER * solver,
        IN SUDOKU_B ** input
    );

    /**
     * printOutput - Pointer to a function that outputs the solved board to a .txt file
     * @param
     *    output - Pointer to the board that will be output 
     *    filename - Character string to output the board to file
     * @note 
     *    filename must be .txt file format - OR enter "printf" if you want it to print to the
          io stream
    **/
    void (* printOutput) (
        IN const char * filename,
        IN SUDOKU_B * output
    );
 
} SUDOKU_SOLVER_VFT;

/**
 * Solver Struct
 * Will have a virtual function table to solve the board - acts like the "engine"
**/
typedef struct SUDOKU_SOLVER 
{
    struct SUDOKU_SOLVER_VFT * vft;
} SUDOKU_SOLVER;

/*
The contents of this ENTIRE file were written by Jackson Skaaden
*/


/**
 * Structure that stores pointer to engine which can create  
**/
typedef struct LIB_SUDOKU 
{
    struct SUDOKU_SOLVER * solver;

    struct SUDOKU_B * current_board;

} LIB_SUDOKU;

/**
 * Virtual function table for the sudoku solver, contains function pointer for solver
**/


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
 * libsudoku->solver->vft(create(&solver));
 * 
 * // Read a valid sudoku board from a file
 * readBoardFromFile("board1.txt", &board1);
 * libsudoku->inputBoard = board1;
 * 
**/
LIB_SUDOKU * getLibSudoku(void);


/**
 * removeBoard - Function that deallocates the given board.
 *   it's a fire and forget, it the instance doesn't exist or its board doesn't exist the funtion
 *   does nothing.
 * @param
 *    board - the board to deallocate
 * @return
 *   void
**/
void removeBoard (
    IN SUDOKU_B ** board
);


/**
 * readBoardFromFile - Reads a board from file and returns board
 * @param
 *    filename - name of the file the board is stored in
 *    board - Pointer to the board to be printed
 * @return
 *    enum S_STATUS - status of the board reading
 * @note
 *    -filename needs to be .txt format
 *    -the boad in the input file must be a 9x9
 *    -board should be NULL to start...This function will turn this pointer
 *      into a block of 9x9 memory for the board - MUST CALL "removeBoard" to 
 *      deallocate the board.
 * **/
enum S_STATUS readBoardFromFile (
    IN const char * filename, 
    OUT SUDOKU_B ** board
    );

#endif /* __SUDOKU_H__ */