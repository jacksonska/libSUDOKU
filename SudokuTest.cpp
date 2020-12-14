#include "libSUDOKU.h"

int main()
{
	LIB_SUDOKU * libsudoku = NULL;
  	SUDOKU_SOLVER * solver = NULL;
	
	// 3 Test boards
	SUDOKU_B * board1 = NULL; // VALID PUZZLE WITH SOLUTION
	SUDOKU_B * board2 = NULL; // VALID PUZZLE WITH SOLUTION
	SUDOKU_B * board3 = NULL; // INVALID


 	enum S_STATUS status = OK;

 	libsudoku = getLibSudoku();
	solver = libsudoku->solver;
	printf("creating solver\n");
 	status = solver->vft->create(&solver);
  	
	// printf("%d\n", status);
	if (OK == status)
	{
	 	// Read a valid sudoku board from a file
	 	printf("\n");
		printf("reading in board1.txt\n");
	 	status = readBoardFromFile("testBoards/unsolved/board1.txt", &board1);
	}


 	if (OK == status)
 	{
 		libsudoku->current_board = board1;
		 //solve the board
 		printf("Solving Board1\n");
		status = solver->vft->solve(solver, &board1);
		
		if (OK == status)
		{
			// Solve ran successfully
			solver->vft->printOutput("testBoards/solved/board1-result.txt", board1);
		}
		else
		{
			printf("error in solve function\n");
			printf("status returned: %d\n", status);
		}

		// deallocate the board
		printf("Deallocating board1\n");
		removeBoard(&board1);
		if (NULL != board1)
		{
			status = FAIL;
		}
 	}

	if (OK == status)
	{
		// read in another board
		printf("\n");
		printf("Reading in board2\n");
		status = readBoardFromFile("testBoards/unsolved/board2.txt", &board2);

		if (OK == status)
		{
			printf("solving board2\n");
			status = solver->vft->solve(solver, &board2);


			if (OK == status)
			{
				// Solve ran successfully
				solver->vft->printOutput("testBoards/solved/board2-result.txt", board2);
			}
			else
			{
				printf("error in solve function\n");
				printf("status returned: %d\n", status);
			}

			printf("deallocating board2\n");
			removeBoard(&board2);
			if (NULL != board2)
			{
				status = FAIL;
			}
		}
		
	}

	if (OK == status)
	{
		printf("\n");
		printf("Reading in board3.txt\n");
		status = readBoardFromFile("testBoards/unsolved/board3.txt", &board3);

		if (OK == status)
		{
			printf("Solving board3\n");
			status = solver->vft->solve(solver, &board3);
			
			if (OK == status)
			{
				// Solve ran successfully
				solver->vft->printOutput("testBoards/solved/board3-result.txt", board3);
			}
			else
			{
				printf("error in solve function\n");
				printf("status returned: %d\n", status);
			}

			printf("deallocating board3\n");
			removeBoard(&board3);
			if (NULL != board3)
			{
				status = FAIL;
			}			
		}
	}

	if (OK == status)
	{
		solver->vft->destroy(&solver);
		solver = NULL;
		libsudoku->solver = NULL;
		free(libsudoku);
	}
	// S_INT * b = board1->board;
	// int v = *(b + 1*9 + 1);
	// printf("%d\n");
 	// if (OK == status)
 	// {
	// 	printf("board status = unsolved\n");
 	// 	libsudoku->solver->vft->printOutput(libsudoku->inputBoard, "printf");
 	// }


 	

	return 0;
}