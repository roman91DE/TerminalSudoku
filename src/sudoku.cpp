
#include "sudoku.h"

#include <fmt/core.h>
#include <algorithm>
#include <exception>
#include <iostream>

Sudoku::Sudoku() {
  for (auto& row : board) std::fill(row.begin(), row.end(), 0);
}

Sudoku::~Sudoku() {}

void Sudoku::resetSudoku() {
  for (auto& row : board) std::fill(row.begin(), row.end(), 0);
}

void Sudoku::printLine() { fmt::print(" +-----------+\n"); }

void Sudoku::printSudoku() const {
  uint16_t rowCount{0}, colCount{0}, lineCount{0};
  fmt::print("  123 456 789 \n");
  Sudoku::printLine();

  for (const auto& row : board) {
    if ((rowCount++) == 3) {
      Sudoku::printLine();
      rowCount = 1;
    }
    colCount = 0;
    fmt::print("{}", ++lineCount);
    for (const auto& cell : row) {
      if ((colCount--) == 0) {
        fmt::print("|");
        colCount = 2;
      }
      if (cell == 0)
        fmt::print(" ");
      else
        fmt::print("{}", cell);
    }
    fmt::print("|\n");
  }
  Sudoku::printLine();
  fmt::print("\n");
}

void Sudoku::setCell(uint16_t val, uint16_t row, uint16_t col) {
  this->board[row][col] = val;
}

uint16_t Sudoku::getCell(uint16_t row, uint16_t col) const {
  return (this->board[row][col]);
}

void Sudoku::clearCell(uint16_t row, uint16_t col) {
  this->setCell(0, row, col);
}

bool Sudoku::isPossible(uint16_t val, uint16_t row, uint16_t col) const {
  // validate args
  if ((val > 9) || ((col > 8) || (row > 8))) return false;

  // check row and column
  for (uint16_t idx{0}; idx < 9; ++idx) {
    if ((getCell(row, idx) == val) || (getCell(idx, col) == val)) return false;
  }
  // check square
  uint16_t rowStart = (row / 3) * 3;
  uint16_t colStart = (col / 3) * 3;
  for (uint16_t rowOffset{0}; rowOffset < 3; ++rowOffset) {
    for (uint16_t colOffset{0}; colOffset < 3; ++colOffset) {
      if (getCell((rowStart + rowOffset), (colStart + colOffset)) == val)
        return false;
    }
  }
  return true;
}

void Sudoku::randSet() {
  for (uint64_t counter{0}; counter < Sudoku::safetyLimit; ++counter) {
    uint16_t row = Sudoku::distribution(Sudoku::generator);
    uint16_t col = Sudoku::distribution(Sudoku::generator);
    uint16_t val = Sudoku::distribution(Sudoku::generator) + 1;
    if (isPossible(val, row, col)) {
      setCell(val, row, col);
      return;
    }
  }
}

void Sudoku::randClear() {
  for (uint64_t counter{0}; counter < Sudoku::safetyLimit; ++counter) {
    uint16_t row = Sudoku::distribution(Sudoku::generator);
    uint16_t col = Sudoku::distribution(Sudoku::generator);
    if (getCell(row, col) > 0) {
      clearCell(row, col);
      return;
    }
  }
}


bool Sudoku::isSolved() const {
  uint32_t sum{0};
  for (const auto& row : board) {
    for (const auto& col : row) {
      sum += col;
    }
  }
  return (sum == Sudoku::checkSum);
}

bool Sudoku::solve() {
  try {
    recursiveSolve();
  } catch (Sudoku::stopRecursion) {
    return true;
  }
  return false;
}

void Sudoku::recursiveSolve() {
  for (uint16_t rowIdx{0}; rowIdx < 9; ++rowIdx) {
    for (uint16_t colIdx{0}; colIdx < 9; ++colIdx) {
      if (getCell(rowIdx, colIdx) == 0) {
        for (uint16_t pval{1}; pval < 10; ++pval) {
          if (isPossible(pval, rowIdx, colIdx)) {
            setCell(pval, rowIdx, colIdx);
            recursiveSolve();
            clearCell(rowIdx, colIdx);
          }
        }
        return;
      }
    }
  }
  throw Sudoku::stopRecursion();
}

void Sudoku::randomInit(uint16_t numCells) {
  // fill sudoku with n random values (n = Sudoku::initSeed)
  for (uint16_t counter{0}; counter < Sudoku::initSeed; ++counter) randSet();
  // solve sudoku
  solve();
  // safety check: sudoku must be solvable
  if (!isSolved()) {
    std::cerr
        << "Backtracking failed at solving the current Sudoku!\nRepeating "
           "randomization...\n";
    resetSudoku();
    randomInit(numCells);
  }
  // delete random cells until numCells are left
  for (uint16_t counter{9 * 9}; counter > numCells; --counter) randClear();
}