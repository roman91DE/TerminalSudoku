#ifndef __SUDOKUHEADER__
#define __SUDOKUHEADER__

#include <cstdint>
#include <list>

#include "board.h"

class Sudoku {
 private:
  // structs/enums
  // ----------
  // represents an individual move by the player
  struct Move {
    uint16_t row, col, val;
    Move(uint16_t _row, uint16_t _col, uint16_t _val);
  };
  // is used to determine the number of prefilled cells
  enum class Difficulty { easy = 0, medium = 1, hard = 2 };
  //  members
  // -------
  // points to current playing board instance
  Board* boardPtr;
  // memory of past moves
  std::list<Sudoku::Move>* moveMemoryPtr;
  //  methods
  // ------

 public:
  // construct an empty Sudoku instance
  Sudoku();
  // construct a partially filled Sudoku
  Sudoku(Difficulty difficulty);
  // free resources
  ~Sudoku();
  void printSudokuState() const;
};

#endif