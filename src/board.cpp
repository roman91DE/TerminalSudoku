
#include "board.h"
#include <algorithm>
#include <fmt/core.h>

Board::Board()
{
    for (auto& row : board)
        std::fill(row.begin(), row.end(), 0);
}

Board::~Board() { }

void Board::printLine() { fmt::print("-------------------\n"); }

void Board::printBoard() const
{
    uint8_t rowCount = 0;

    for (auto& row : board) {
        if (rowCount++ == 3) {
            fmt::print("-------------------\n");
            rowCount = 1;
        }
        fmt::print(
            "|{} {} {}|{} {} {}|{} {} {}|\n",
            row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8]);
    }
    fmt::print("-------------------\n");
}