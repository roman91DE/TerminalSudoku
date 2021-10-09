
#include "board.h"

#include <fmt/core.h>

#include <algorithm>

Board::Board() {
  for (auto& row : board) std::fill(row.begin(), row.end(), 0);
}

Board::~Board() {}

void Board::printLine() { fmt::print("+-----------------+\n"); }

void Board::printBoard() const {
  uint8_t rowCount = 0;
  Board::printLine();

  for (auto& row : board) {
    if (rowCount++ == 3) {
      Board::printLine();
      rowCount = 1;
    }
    fmt::print("|{} {} {}|{} {} {}|{} {} {}|\n", row[0], row[1], row[2], row[3],
               row[4], row[5], row[6], row[7], row[8]);
  }
  Board::printLine();
}