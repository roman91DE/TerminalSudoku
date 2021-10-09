#include <fmt/core.h>

#include "board.h"

int main(int, char**) {
  Board b;
  b.printBoard();
  b.setCell(2, 3, 8);
  b.setCell(5, 3, 9);
  b.setCell(8, 8, 1);
  b.printBoard();
  return 0;
}
