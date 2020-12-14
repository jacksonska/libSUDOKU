#include "lib.h"

LIB_SUDOKU * getLibSudoku(void)
{
    enum S_STATUS status = OK;
    struct LIB_SUDOKU * lib = NULL;
    // Allocate the memory for the library structure
    lib = (LIB_SUDOKU *) malloc(sizeof(LIB_SUDOKU));
    memset(lib, 0, sizeof(LIB_SUDOKU));
    if (NULL == lib)
    {
        status = NO_RESOURCES;
    }

    // printf("%d\n", status);

    if (OK == status)
    {
        
        lib->solver = (SUDOKU_SOLVER *) malloc(sizeof(SUDOKU_SOLVER));
        if (NULL != lib->solver)
        {
            // printf("solver memory created\n");
            memset(lib->solver, 0, sizeof(SUDOKU_SOLVER));
            // Note: this vft is define in solver.cpp, able to use because single compilation file
            lib->solver->vft = &vft;
            // printf("set vft mf\n");
            
        }
        
        lib->current_board = NULL;
    }
    return lib;
}

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
)
{
    enum S_STATUS status = OK; 
    FILE * ifile = NULL;
    SUDOKU_B * b = NULL;
    S_INT * tempB = NULL;
    
    // Verify the board was passed correctly
    if (NULL != *board)
    {
        status = BAD_PARAM;
    }

    // Alocate board structs members
    if (OK == status)
    {
        b = (SUDOKU_B *) malloc(sizeof(SUDOKU_B));
        if (NULL == b)
        {
            status = NO_RESOURCES;
        }
        else
        {
            b->board = NULL; // this will be set at the end of the function
            b->status = UNSOLVED;
        }
    }
    // Allocate the board's memory +^ (remove these characters when memory is freed)
    if (OK == status)
    {
        // Allocates a 9x9 block of S_INT's for the board
        tempB = (S_INT *) malloc(9 * 9 * sizeof(S_INT));

        //Verify memory allocation
        if (NULL == tempB)
        {
            status = NO_RESOURCES;
        }
    }

    /*
    The contents of this ENTIRE file were written by Jackson Skaaden
    */


    // try and open the file
    if (OK == status)
    {
        // Try to open the file for reading in the board
        ifile = fopen(filename, "r");
        
        // Verify the file opening went as planned
        if (NULL == ifile)
        {
            // File couldn't open, free the new mem and return failure
            status = FAIL;
            printf("file couldn't open\n");
            free(tempB);
            free(b);
            return status;
        }
    }
    
    // If the file is opened successfully, then read in the board
    if (OK == status)
    {
        for(S_INT i = 0; i < 9; i++)
        {
            for(S_INT j = 0; j < 9; j++)
            {
                //read in the number
                char v = fgetc(ifile);
                // printf("i: %d, j: %d ~~value = %c\n", i,j, v);
                // printf("%c\n", v);
                if (v == '\n')
                {
                    //reached endline, don't want that character get next one
                    v = fgetc(ifile);
                }

                // printf("i: %d, j: %d ~~value = %c\n", i,j, v);
                // Convert character to an int that can be used
                S_INT value = (S_INT) v - 48;
                // If the character is invalid, free the temp board and return
                if (EOF == value)
                {
                    status = FAIL;
                    fclose(ifile);
                    free(tempB);
                    free(b);
                    printf("end of file char reached\n");
                    return status;
                }

                // if this is reached, the value is valid
                // Set the boards value to the one read in -
                // using pointer arithmetic
                *(tempB + i*9 + j) = value; 
                
                
            } 
        }

        // Set the output board's members to the ones you just created/filled
        b->board = tempB;
        *board = b;
    }
    
    // NOTE the board is not freed here, it is up to the user to free that memory block when they're done
    return status;
}


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
)
{
    if (NULL != board)
    {
        SUDOKU_B * remove = *board;
        // Free the board struct's actual board data
        if (NULL != remove->board)
        {
            free(remove->board);
            remove->board = NULL; 
        }

        // Now, free the actual board
        free(remove);
        *board = NULL;
    }
}