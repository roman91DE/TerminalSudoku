#ifndef __SUDOKUHEADER__
#define __SUDOKUHEADER__

#include "board.h"
#include <list>

// represents an individual move by the player
struct SudokuMove {
    uint16_t row, col, val;
    SudokuMove(uint16_t _row, uint16_t _col, uint16_t _val);
};

// is used to determine the number of prefilled cells
enum class SudokuDifficulty {
    easy = 0,
    medium = 1,
    hard = 2
};

class Sudoku {
private:
    //  members
    // ------
    Board* board_ptr;
    // memory of past moves
    std::list<SudokuMove> moveMemory;
    //  methods
    // ------

public:
    // construct an empty Sudoku instance
    Sudoku();
    // construct a partially filled Sudoku
    Sudoku(SudokuDifficulty difficulty);
    // free resources
    ~Sudoku();
};

#endif