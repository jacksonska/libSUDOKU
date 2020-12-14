# Sudoku Solver Library

## Library Info:
  + libSUDOKU is a library that will solve any 9x9 sudoku board; **must be of the form shown in files contained in the directory testBoards/unsolved/ (no spaces, only numbers and newline characters.**
  + Developed and compiles on Ubuntu devices. (I developed it on a Raspberry pi 3 running Raspbian GNU/LINUX 10 (buster) and ran valgrind test on Ubuntu 18.04 due to valgrind not working with raspbian distrubtion)

## To compile and run library:
  1. Clone repository and cd into libSUDOKU folder and run `make`
  2. The libSUDOKU.so shared library will be output in the bin directory & libtest will be in the libSUDOKU directory.
    + `./libtest` will run a test program written in SudokuTest.cpp. It demonstrates how to use the ilbrary on 3 sudoku boards.
      - board1 will have at least one solution
      - board2 will have also have at least one solution
      - board3 will have no solution
    + To link your own files compile your written code, lets call it test.c, with `gcc -Wall -Wextra -g -Wl -rpath,**PATH_TO_LIBRARY_BINARY** test.c -o **TEST_EXECUTABLE** -L**PATH_TO_LIBRARY_BINARY** -lSUDOKU`
      - The bold test above are lines you need to fill in yourself
      - **NOTE:** You can use a relative path to fill out the **PATH_TO_LIBRARY_BINARY** sections if you are coding your test in the same directory as my file "SudokuTest.cpp". However, it is probably best to just use the absolute path for your own clarity.

## Solving Algorithm
  + This library solves sudoku boards using a recursive backtracing algorithm.
    - `solveHelper` is the main recursive function of the library, along with the functions `isValid` and `verify`.
  + Pseudo code describing the algorithm can be found in solver.cpp line 403-417