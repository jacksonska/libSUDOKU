# $< - first dependency
# $^ - all dependencies
# $@ - target name (whatever's before colon)
CXX = gcc
CFLAGS = -g -Wall -Wextra
LIBFLAGS = $(CFLAGS) -fPIC -shared

BINDIR=bin
OBJDIR=obj
SRCDIR = .

INC = lib.h libSUDOKU.h solver.hpp
DEP = $(BINDIR)/libSUDOKU.so
TARGET = libtest

# Testing targets
TESTF = $(SRCDIR)/SudokuTest.cpp
TESTRUN = test-run


INCPATH = ./ #/home/dev/source_code/Projects/SudokuPrivate/ # Path to dir of files I made
LIBPATH = bin/ #PATH RELATIVE TO THE MAKEFILE /home/dev/source_code/Projects/SudokuPrivate/bin
all: clean $(DEP)

# Link the shared object with test code
$(TARGET): $(BINDIR) $(DEP) $(TESTF)
	$(CXX) $(CFLAGS) -Wl,-rpath,$(LIBPATH) $(TESTF) -o $@ -L$(LIBPATH) -lSUDOKU 
# Compile Shared object
$(DEP): $(SRCDIR)/Sudoku.cpp $(OBJDIR) $(INC) $(BINDIR)
	$(CXX) $(LIBFLAGS) -I $(INCPATH) $< -o $@ -lc

$(BINDIR):
	mkdir $(BINDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(SRCDIR):
	mkdir $(SRCDIR)

warning:
	@echo "=========Please make sure you have built your shared library object!========="

$(TESTRUN): $(TESTF) warning
	@echo "============================================================================="
	@echo "compiling test file"
	$(CXX) $(LIBFLAGS) -I $(INCPATH) -L$(LIBPATH) -lSUDOKU $< -o $@

test: $(TARGET)
	@echo "============Compiling SudokuTest.cpp and linking to libSUDOKU.so to the exec: libtest============"
	@echo " run ./libtest to run the test program"

clean:
	rm -rf $(OBJDIR) $(BINDIR) $(TARGET) testBoards/solved
	mkdir testBoards/solved