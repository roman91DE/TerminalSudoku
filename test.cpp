#include <cstdio>
#include <cstdint>

int main(int, char**)
{
    uint16_t row = 4;
    uint16_t col = 2;
    uint16_t rowStart = (row / 3) * 3;
    uint16_t colStart = (col / 3) * 3;
    for (uint16_t rowOffset { 0 }; rowOffset < 3; ++rowOffset) {
        for (uint16_t colOffset { 0 }; colOffset < 3; ++colOffset) {
            printf("Row: %d Col: %d\n", rowStart + rowOffset, colStart + colOffset);
        }
    }
        return 0;
    }
