
#include "board.h"
#include <algorithm>
#include <fmt/core.h>

Board::Board() {
  for (auto &row : board)
    std::fill(row.begin(), row.end(), 0);
}

Board::~Board() {}

void Board::printBoard const {}