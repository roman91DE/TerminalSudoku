#ifndef __SUDOKUHEADER__
#define __SUDOKUHEADER__

#include "board.h"

class Sudoku {
private:
    Board* board_ptr;

    enum Difficulty { easy = 0,
        medium = 1,
        hard = 2 };

public:
    // construct an empty Sudoku instance
    Sudoku();
    // construct a partially filled Sudoku
    Sudoku(Sudoku::Difficulty value);
    // free resources
    ~Sudoku();
};

#endif