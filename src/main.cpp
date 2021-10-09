#include <fmt/core.h>

#include "board.h"

int
main(int, char**)
{
  Board b;
  b.solve();
  b.printBoard();
  return 0;
}
