#include "sudoku.h"

Sudoku::Sudoku()
    : board_ptr(new Board())
{
}

Sudoku::~Sudoku()
{
    delete board_ptr;
}