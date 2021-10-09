
#include "board.h"

#include <fmt/core.h>

#include <algorithm>
#include <random>

Board::Board()
    : generator(new std::default_random_engine),
      distribution(new std::uniform_int_distribution<uint8_t>(0, 8)) {
  for (auto& row : board) std::fill(row.begin(), row.end(), 0);
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(1, 6);
}

Board::~Board() {}

void Board::printLine() { fmt::print(" +-----------+\n"); }

void Board::printBoard() const {
  uint8_t rowCount{0}, colCount{0}, lineCount{0};
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

void Board::setCell(uint8_t val, uint8_t row, uint8_t col) {
  this->board[row][col] = val;
}

int Board::getCell(uint8_t row, uint8_t col) const {
  return (this->board[row][col]);
}

void Board::clearCell(uint8_t row, uint8_t col) { this->setCell(0, row, col); }

void Board::randClear() {}

void Board::randSet() {}