
#include "board.h"
#include <algorithm>
#include <fmt/core.h>
#include <random>

Board::Board()
    : generator(new std::default_random_engine)
    , distribution(new std::uniform_int_distribution<uint8_t>(0, 8))
{
    for (auto& row : board)
        std::fill(row.begin(), row.end(), 0);
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 6);
}

Board::~Board()
{
    delete generator;
    delete distribution;
}

void Board::printLine() { fmt::print(" +-----------+\n"); }

void Board::printBoard() const
{
    uint8_t rowCount { 0 }, colCount { 0 }, lineCount { 0 };
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

void Board::setCell(uint8_t val, uint8_t row, uint8_t col)
{
    this->board[row][col] = val;
}

int Board::getCell(uint8_t row, uint8_t col) const
{
    return (this->board[row][col]);
}

void Board::clearCell(uint8_t row, uint8_t col) { this->setCell(0, row, col); }

bool Board::isPossible(uint8_t val, uint8_t row, uint8_t col) const
{
    // check args
    if ((val > 9) | ((col > 8) | (row > 8)))
        return false;

    // check row and column
    for (u_int8_t idx { 0 }; idx < 8; ++idx) {
        if ((getCell(row, idx) == val) || (getCell(idx, col) == val))
            return false;
    }
    // check square
    uint8_t rowStart = (row / 3) * 3;
    uint8_t colStart = (col / 3) * 3;
    for (u_int8_t rowIdx { rowStart }; rowIdx < (rowStart + 3); ++rowIdx) {
        for (u_int8_t colIdx { 0 }; colIdx < (colStart + 3); ++colIdx) {
            if (getCell(rowIdx, colIdx) == val)
                return false;
        }
    }
    return true;
}

void Board::randSet()
{
    for (uint64_t counter { 0 }; counter < safetyLimit; ++counter) {
        uint8_t row = (*distribution)((*generator));
        uint8_t col = (*distribution)((*generator));
        uint8_t val = (*distribution)((*generator)) + 1;
        if (isPossible(val, row, col)) {
            setCell(val, row, col);
            return;
        }
    }
}

void Board::randClear()
{
    for (uint64_t counter { 0 }; counter < safetyLimit; ++counter) {
        uint8_t row = (*distribution)((*generator));
        uint8_t col = (*distribution)((*generator));
        if (getCell(row, col) == 0) {
            clearCell(row, col);
            return;
        }
    }
}