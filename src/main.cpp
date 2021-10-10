#include <fmt/core.h>

#include "board.h"
#include "sudoku.h"

int main(int, char**) {
  Sudoku s = Sudoku(Sudoku::Difficulty::medium);
  s.printSudokuState();
  s.autoSolve();
  return 0;
}
