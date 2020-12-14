#ifndef __SOLVER_HPP__
#define __SOLVER_HPP__

#include "libSUDOKU.h"


/** 
 * createSolver - Creates a sudoku board solver, Can solve any board
 * @param
 *    solver - Pointer to the place where Sudoku will be stored
 * @return
 *   S_STATUS - Status of the solver's creation
**/
enum S_STATUS Sudoku_Create (
    OUT SUDOKU_SOLVER ** solver
);


/** 
* destroy - Destroys a sudoku board solver
* @param
*    solver - Pointer to the Sudoku Solver
* @return
*   void
**/
void Sudoku_Destroy (
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
enum S_STATUS Sudoku_Solve (
    IN SUDOKU_SOLVER * solver,
    IN OUT SUDOKU_B ** input
);


/**
 * printOutput - Pointer to a function that outputs the solved board to a .txt file
 * @param
 *    output - Pointer to the board that will be output 
 *    filename - Character string to output the board to file 
 * @return
 *    void - Does not return anything despite using status variable
 * @note 
 *    filename must be .txt file format
**/
void Sudoku_printOutput (
    IN const char * filename,
    IN SUDOKU_B * output
);

/**
 * Structure for performing the sudoku solving algorithm.
 * The structure, is not exposed to a user of the library.
 * It has a private inheritance relationship with SUDOKU_SOLVER.
 * It's polymorphic structure is the vft, but the stored board and the
 * isValid() function & the solveHelper() functions are private in nature.
 *  
**/
typedef struct SUDOKU_INSTANCE 
{
    // vft shared with the SUDOKU_SOLVER
    SUDOKU_SOLVER_VFT * vft;

    // Private board structure
    SUDOKU_B * board;

    // /** 
    //  * Sudoku_Solver - Creates a sudoku board solver, Can solve any board
    //  * @param
    //  *    solver - Pointer to the place where Sudoku will be stored
    //  * @return
    //  *   S_STATUS - Status of the solver's creation
    // **/
    // enum S_STATUS (* Sudoku_Create) (
    //     OUT SUDOKU_SOLVER ** solver
    // );
    

    // /** 
    //  * Sudoku_Destroy - Destroys a sudoku board solver
    //  * @param
    //  *    solver - Pointer to the Sudoku Solver
    //  * @return
    //  *   void
    // **/
    // void (* Sudoku_Destroy) (
    //     IN struct SUDOKU_SOLVER ** solver
    // );


    // *
    //  * solve - function Pointer to a Sudoku Puzzle solver
    //  * @param
    //  *    solver - Pointer to solver calling the function
    //  *    input - Pointer to the board that is to be solved. Will be solved in place 
    //  *      (The SUDOKU_B * input will become the output)
    //  *    output - Double pointer to a solved version of the input board
    //  * @return
    //  *    void
    //  *
    // void (* Sudoku_Solve) (
    //     IN SUDOKU_SOLVER * solver,
    //     IN SUDOKU_B ** input,
    //     OUT SUDOKU_B ** output
    // );

    // /**
    //  * printOutput - Pointer to a function that outputs the solved board to a .txt file
    //  * @param
    //  *    output - Pointer to the board that will be output 
    //  *    filename - Character string to output the board to file 
    //  * @note 
    //  *    filename must be .txt file format
    // **/
    // void (* Sudoku_printOutput) (
    //     IN SUDOKU_B * output,
    //     IN const char * filename
    // );

    /*
        The contents of this ENTIRE file were written by Jackson Skaaden
    */


    /**
     * isValid - Private function that checks if the current board 
     * values are a valid solution.
     * @param
     *    row - current row of the solution
     *    col - current col of the solution
     *    instance - pointer to the solver's instace. It stores the board.
     * @return
     *    char - 0 for false, 1 for true. Acts as a bool 
    **/
    char isValid (
        IN S_INT row, 
        IN S_INT col,
        IN SUDOKU_INSTANCE * instance
    );
    
    
    /** solveHelper - Private recursive helper function for solving board.
     * @param
     *    row - current row of the solution 
     *    col - current col of the solution
     *    instance - pointer to the solver's instace. It stores the board.
     * @return
     *    char - 0 for false, 1 for true. Acts as a bool
    **/
    char solveHelper (
        IN S_INT row, 
        IN S_INT col,
        IN SUDOKU_INSTANCE * instance
    );

    /** verify - Private function that will verify the final state of the board after solve()
     * @param
     *    instance - pointer to the instance which holds the board
     * @return
     *    char - 0 for false, 1 for true. If 0 is returned, board solution is invalid.
    **/
    char verify (
        IN SUDOKU_INSTANCE * instance
    );

} SUDOKU_INSTANCE;

#endif // __SOLVER_HPP__