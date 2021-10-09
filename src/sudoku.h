#ifndef __SUDOKUHEADER__
#define __SUDOKUHEADER__

#include <memory>

#include "board.h"

enum class Difficulty { easy = 0, medium = 1, hard = 2 };

class Sudoku {
private:
  Board *board_ptr;

public:
  // construct an empty Sudoku instance
  Sudoku();
  // construct a partially filled Sudoku
  Sudoku(Difficulty value);
  // free resources
  ~Sudoku();
};

#endif