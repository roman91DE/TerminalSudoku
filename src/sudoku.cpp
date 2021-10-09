#include "sudoku.h"

SudokuMove::SudokuMove(uint16_t _row, uint16_t _col, uint16_t _val)
    : row(_row)
    , col(_col)
    , val(_val)
{
}

Sudoku::Sudoku()
    : boardPtr(new Board())
    , moveMemoryPtr(new std::list<SudokuMove>())
{
}

Sudoku::~Sudoku()
{
    delete boardPtr;
    delete moveMemoryPtr;
}
