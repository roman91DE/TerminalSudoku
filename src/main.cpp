#include <fmt/core.h>

#include "board.h"
#include <cstdint>

int main(int, char**)
{
    Board b;
    uint16_t row = 4;
    uint16_t col = 2;
    uint16_t rowStart = (row / 3) * 3;
    uint16_t colStart = (col / 3) * 3;
    for (uint16_t rowOffset { 0 }; rowOffset < 4; ++rowOffset) {
        for (uint16_t colOffset { 0 }; colOffset < 4; ++colOffset) {
            fmt::print("Row: {} Col: {}\n", rowStart + rowOffset, colStart + colOffset);
        }
        return 0;
    }
