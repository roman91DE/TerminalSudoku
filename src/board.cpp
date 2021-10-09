
#include "board.h"

#include <fmt/core.h>

#include <algorithm>

Board::Board() {
  for (auto& row : board) std::fill(row.begin(), row.end(), 0);
}

Board::~Board() {}

void Board::printLine() { fmt::print("+-----------+\n"); }

void Board::printBoard() const {
  uint8_t rowCount{0}, colCount{0};
  Board::printLine();

  for (const auto& row : board) {
    if ((rowCount++) == 3) {
      Board::printLine();
      rowCount = 1;
    }
    colCount = 0;
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
}