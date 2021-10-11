#include "game.h"

// int main() {
//   Game::runMainMenu();
//   return 0;
// }

int main() {
  Sudoku s;
  s.randomInit(60);
  s.printSudoku();
  Sudoku other{s};
  other.printSudoku();
  return 0;

}