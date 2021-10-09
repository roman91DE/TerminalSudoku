
#include "board.h"

#include <fmt/core.h>

#include <algorithm>

Board::Board()
    : generator(new std::default_random_engine),
      distribution(new std::uniform_int_distribution<uint16_t>(0, 8)) {
  for (auto& row : board)
    std::fill(row.begin(), row.end(), 0);
}

Board::~Board() {
  delete generator;
  delete distribution;
}

void Board::printLine() {
  fmt::print(" +-----------+\n");
}

void Board::printBoard() const {
  uint16_t rowCount{0}, colCount{0}, lineCount{0};
  fmt::print("  123 456 789 \n");
  Board::printLine();

  for (const auto& row : board) {
    if ((rowCount++) == 3) {
      Board::printLine();
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
  Board::printLine();
  fmt::print("\n");
}

void Board::setCell(uint16_t val, uint16_t row, uint16_t col) {
  this->board[row][col] = val;
}

uint16_t Board::getCell(uint16_t row, uint16_t col) const {
  return (this->board[row][col]);
}

void Board::clearCell(uint16_t row, uint16_t col) {
  this->setCell(0, row, col);
}

bool Board::isPossible(uint16_t val, uint16_t row, uint16_t col) const {
  // validate args
  if ((val > 9) || ((col > 8) || (row > 8)))
    return false;

  // check row and column
  for (uint16_t idx{0}; idx < 9; ++idx) {
    if ((getCell(row, idx) == val) || (getCell(idx, col) == val))
      return false;
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

void Board::randSet() {
  for (uint64_t counter{0}; counter < Board::safetyLimit; ++counter) {
    uint16_t row = (*distribution)((*generator));
    uint16_t col = (*distribution)((*generator));
    uint16_t val = (*distribution)((*generator)) + 1;
    if (isPossible(val, row, col)) {
      setCell(val, row, col);
      return;
    }
  }
}

void Board::randClear() {
  for (uint64_t counter{0}; counter < Board::safetyLimit; ++counter) {
    uint16_t row = (*distribution)((*generator));
    uint16_t col = (*distribution)((*generator));
    if (getCell(row, col) > 0) {
      clearCell(row, col);
      return;
    }
  }
}

void Board::printCheckSum() const {
  uint32_t checkSum{0};
  for (const auto& row : board) {
    for (const auto& col : row) {
      checkSum += col;
    }
  }
  fmt::print("Checksum = {}\n", checkSum);
}

bool Board::isSolved() const {
  uint32_t sum{0};
  for (const auto& row : board) {
    for (const auto& col : row) {
      sum += col;
    }
  }
  return (sum == Board::checkSum);
}

bool Board::solve() {
  try {
    recursiveSolve();
  } catch (Board::stopRecursion) {
    return true;
  }
  return false;
}

void Board::recursiveSolve() {
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
  throw Board::stopRecursion();
}
