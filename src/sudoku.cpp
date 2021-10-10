#include "sudoku.h"

Sudoku::Move::Move(uint16_t _row, uint16_t _col, uint16_t _val)
    : row(_row), col(_col), val(_val) {}

Sudoku::Sudoku()
    : boardPtr(new Board()), moveMemoryPtr(new std::list<Sudoku::Move>()) {}

Sudoku::Sudoku(Sudoku::Difficulty difficulty) {
  uint16_t numCells{10};

  switch (difficulty) {
    case Sudoku::Difficulty::easy:
      numCells = 20;
      break;
    case Sudoku::Difficulty::medium:
      numCells = 30;
      break;
    case Sudoku::Difficulty::hard:
      numCells = 40;
      break;
    default:
      break;
  }
  boardPtr->randomInit(numCells);
}

Sudoku::~Sudoku() {
  delete boardPtr;
  delete moveMemoryPtr;
}
