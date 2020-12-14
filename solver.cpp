#include "solver.hpp"
#include <cstring>

// Provide a definition of the vft for the solver to use
SUDOKU_SOLVER_VFT vft = {
    Sudoku_Create,
    Sudoku_Destroy,
    Sudoku_Solve,
    Sudoku_printOutput
};

/** 
 * createSolver - Creates a sudoku board solver, Can solve any board
 * @param
 *    solver - Pointer to the place where Sudoku will be stored
 * @return
 *   S_STATUS - Status of the solver's creation
**/
enum S_STATUS Sudoku_Create (
    OUT SUDOKU_SOLVER ** solver
)
{
    enum S_STATUS status = OK;
    SUDOKU_INSTANCE * instance = NULL;

    if (NULL == *solver)
    {
        status = BAD_PARAM;
    }
    
    if (OK == status)
    {
        //remove the old solver memory and allocate its 'private subclass' : instance
        free(*solver);
        *solver = NULL;

        instance = (SUDOKU_INSTANCE *) malloc(sizeof(SUDOKU_INSTANCE));
        // printf("%lu\n", sizeof(SUDOKU_INSTANCE));


        if (NULL == instance)
        {
            // Ensure the instance's memory allocation was successful
            status = NO_RESOURCES;
            // printf("instance is null\n");
        }
    
    }
    

    if (OK == status)
    {
        // Set the instance's value to 0 
        memset(instance, 0, sizeof(SUDOKU_INSTANCE));

        // Set the instance's vft to the vft defined above.
        instance->vft = &vft;

        // Cast the private instance of the solver 'backwards' to its public format
        *solver = (SUDOKU_SOLVER *) instance;
    }

    return status;
    
}


/*
The contents of this ENTIRE file were written by Jackson Skaaden
*/

/** 
* destroy - Destroys a sudoku board solver
* @param
*    solver - Pointer to the Sudoku Solver
* @return
*   void
**/
void Sudoku_Destroy (
    IN struct SUDOKU_SOLVER ** solver
)
{
    SUDOKU_INSTANCE * instance = NULL;
    
    // Verify the parameter works
    if (NULL != solver)
    {
        instance = (SUDOKU_INSTANCE *) *solver;

        free(instance);

        *solver = NULL;
    }
}

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
)
{
    enum S_STATUS status = OK;
    SUDOKU_INSTANCE * instance = NULL;

    if (NULL == solver)
    {
        status = BAD_PARAM;
    }

    if (OK == status)
    {
        instance = (SUDOKU_INSTANCE *) solver;
    }

    if (NULL == input)
    {
        status = BAD_PARAM;
    }

    if (OK == status)
    {
        if (NULL != instance->board)
        {
            instance->board = NULL;
        }
        instance->board = *input;

        instance->solveHelper(0, 0, instance);
        // Verify the final board's state
        if (!instance->verify(instance))
        {
            instance->board->status = INVALID;
        }
        else
        {
            instance->board->status = SOLVED;
        }
    }
    // The input board should have been solved in place so just return the status
    return status;
}

/**
 * printOutput - Pointer to a function that outputs the solved board to a .txt file
 * @param
 *    output - Pointer to the board that will be output 
 *    filename - Character string to output the board to file 
 * @return
 *    void - Does not return anything despite using status variable
 * @note 
 *    filename must be .txt file format - OR enter "printf" if you want it to print to the
        io stream
      This function will print a formatted version of the board, not raw values
**/
void Sudoku_printOutput (
    IN const char * filename,
    IN SUDOKU_B * output
)
{
    enum S_STATUS status = OK;
    FILE * ofile = NULL;
    S_INT * board = NULL;
    
    // Flag to identify what stream the function should output to.
    // - defaults to filestream
    char out_type = 'f';

    // Check the board param
    if (NULL == output)
    {
        status = BAD_PARAM;
    }

    // Set the temp board variable
    if (OK == status)
    {
        if (NULL != output->board)
        {
            board = output->board;
        }
        else
        {
            status = BAD_PARAM;
        }
    }

    // Verify the filename
    if (OK == status)
    {
        if (NULL == filename)
        {
            status = BAD_PARAM;
        }
        else if (!strncmp("printf", filename, 6))
        {
            // User wants std output print 
            out_type = 's';
        }
        else
        {
            // User wants to output to a file, open it
            ofile = fopen(filename, "w+");
            if (NULL == ofile)
            {
                status = NO_RESOURCES;
            }
        }
    }
    
    
    if (OK == status)
    {
        if ('f' == out_type)
        {
            printf("Printing board to \"%s\".\n", filename);
            
            
            fprintf(ofile, "Board status: ");
            if (output->status == SOLVED)
            {
                fprintf(ofile, "SOLVED\n");
            }
            else if (output->status == UNSOLVED)
            {
                fprintf(ofile, "UNSOLVED\n");
            }
            else
            {
                fprintf(ofile, "INVALID\n");
            }
            
            for (S_INT i = 0; i < 9; i++)
            {
                if (i % 3 == 0)
                    fprintf(ofile, "-------------------------------\n");
                for (S_INT j = 0; j < 9; j++)
                {
                    if (j % 3 == 0)
                        fprintf(ofile, "|");
                    
                    if ( *(board + i*9 + j) != 0)
                        fprintf(ofile, " %d ", *(board + i*9 + j));
                    else
                        fprintf(ofile, " . ");
                    
                }

                fprintf(ofile, "|\n");
            }

            fprintf(ofile, "-------------------------------\n");
        }
        else if ('s' == out_type)
        {
            // User wants to print out to the std io stream
            printf("Printing board to \"%s\".\n", filename);
            printf("Board status: ");
            if (output->status == SOLVED)
            {
                printf("SOLVED\n");
            }
            else if (output->status == UNSOLVED)
            {
                printf("UNSOLVED\n");
            }
            else
            {
                printf("INVALID\n");
            }

            for (S_INT i = 0; i < 9; i++)
            {
                if (i % 3 == 0)
                    printf("-------------------------------\n");
                for (S_INT j = 0; j < 9; j++)
                {
                    if (j % 3 == 0)
                        printf("|");
                    
                    if (0 != *(board + i*9 + j))
                        printf(" %d ", *(board + i*9 + j));
                    else
                        printf(" . ");
                    
                }

                printf("|\n");
            }

            printf("-------------------------------\n");
        }
        else
        {
            printf("printOutput failure\n");
        }
        
    }
}

/**
 * isValid - checks if the current board values are valid for the game.
 * @param
 *    row - current row of the solution
 *    col - current col of the solution
 * @return
 *    char - 0 for false, 1 for true. Acts as a bool 
**/
char SUDOKU_INSTANCE::isValid (
    IN S_INT row, 
    IN S_INT col,
    IN SUDOKU_INSTANCE * instance
)
{
    enum S_STATUS status = OK;
    S_INT * board = NULL;
    // S_INT size = 0;
    if (NULL == instance)
    {
        status = BAD_PARAM;
    }

    if (OK == status)
    {
        if (NULL == instance->board)
        {
            status = BAD_PARAM;
        }
        board = instance->board->board;
    }

    if (OK == status)
    {
        // Grab the value at the current position
        S_INT value = *(board + row*9 + col);
        // Iterate through the whole row and check if theres a duplicate
        for (S_INT i = 0; i < 9; i++)
        {
            if (i == row)
                continue;

            S_INT temp = *(board + i*9 + col);
            if (temp == value)
                return 0;
        }
        // Iterate through the whole col and check if theres a duplicate
        for (S_INT i = 0; i < 9; i++)
        {
            if (i == col)
                continue;
            S_INT temp = *(board + row*9 + i);
            if (temp == value)
                return 0;
        }

        int box_row = row / 3;
        int box_col = col / 3;
        // Verify the whole board doesn't have a duplicate
        for (S_INT i = box_row * 3; i < box_row * 3 + 3; i++)
        {
            for (S_INT j = box_col * 3; j < box_col * 3 + 3; j++)
            {
                if (i == row && j == col)
                    continue;
                
                S_INT temp = *(board + i*9 + j);
                if (temp == value)
                    return 0;
            }
        }

        // No duplicates were found, return 1 for valid board
        return 1; 
    }

    // If this is reached, the status was wrong
    return 0;

}

/**
 * solveHelper - Recursive helper function for solving board.
 * @param
 *    row - current row of the solution 
 *    col - current col of the solution
 *    instance - pointer to the solver's instace. It stores the board.
 * @return
 *    char - 0 for false, 1 for true. Acts as a bool
**/
char  SUDOKU_INSTANCE::solveHelper (
    IN S_INT row, 
    IN S_INT col,
    IN SUDOKU_INSTANCE * instance
)
{
    //pseudo code for the algorithm
    //write base conditions
    //if (row == 9)
	    //return true
    // if(col == 9)
	    // what to return??
    /*
    check if the board[row][col] == 0
	    use a for loop to traverse through and fill in numbers from 1-9
		    check if the number is valid using the isValid function
			    if it is make the next recursion call
	    update the board[row][col] to 0
	    return ??
    else
	    make the next recursion call
    */


    // Forgoe checking if instance is null because if this function is
    // called there can't be a null instance. Just check if board is null.
    S_INT * board = NULL;
    enum S_STATUS status = OK;
    if (instance->board == NULL)
    {
        status = BAD_PARAM;
    }
   if (OK == status)
   {
        board = instance->board->board;

        if (9 == row)
            return 1;
        if (9 == col)
            return instance->solveHelper(row+1, 0, instance);

        if (0 == *(board + row*9 + col))
        {
            for (S_INT i = 1; i < 10; i++)
            {
                *(board + row*9 + col) = i;
                if (instance->isValid(row, col, instance))
                {
                    if(instance->solveHelper(row, col+1, instance))
                        return 1;
                }
            }
            // If this point is reached, a valid number was not found
            *(board + row*9 + col) = 0;
            return 0;
        }
        else
        {
            instance->solveHelper(row, col+1, instance);
        }
   }


}

/** verify - Function that will verify the final state of the board after solve()
* @param
*    instance - pointer to the instance which holds the board
* @return
*    char - 0 for false, 1 for true. If 0 is returned, board solution is invalid.
**/
char  SUDOKU_INSTANCE::verify (
IN SUDOKU_INSTANCE * instance
)
{
    enum S_STATUS status = OK;
    S_INT** board = NULL;

    // Do preliminary pointer checks:
    if (NULL == instance)
    {
        status = BAD_PARAM;
    }
    if (OK == status)
    {
        if (NULL == instance->board)
        {
            status = BAD_PARAM;
        }
    }
    if (OK == status)
    {
        board = &instance->board->board;
        if (NULL == board)
        {
            status = BAD_PARAM;
        }
    }

    // End of pointer checks, start alg

    if (OK == status)
    {
        for (S_INT i = 0; i < 9; i++)
        {
            for (S_INT j = 0; j < 9; j++)
            {
                if (!isValid(i, j, instance))
                    return 0;
            }
        }
        // If this line is reached, then the whole puzzle was valid
        return 1;
    }

    // If this line is reached, it means that for whatever reason, the status
    // was not OK
    return 0;
}