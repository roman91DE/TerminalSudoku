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

Sudoku::Sudoku(SudokuDifficulty difficulty)
{

    uint16_t numCells { 30 };

    switch (difficulty) {
    case SudokuDifficulty::easy:
        numCells = 20;
        break;
    case SudokuDifficulty::medium:
        numCells = 30;
        break;
    case SudokuDifficulty::hard:
        numCells = 40;
        break;
    default:
        break;
    }
    boardPtr->randomInit(numCells);
}

Sudoku::~Sudoku()
{
    delete boardPtr;
    delete moveMemoryPtr;
}
