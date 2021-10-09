
#include "board.h"
#include <algorithm>
#include <fmt/core.h>

Board::Board()
{
    for (auto& row : board)
        std::fill(row.begin(), row.end(), 0);
}

Board::~Board() { }

void Board::printBoard const
{
    for (auto& row : board) {
        fmt::print(
            "|{}{}{}[{}{}{}|{}{}{}|",
            row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], )
    }
}