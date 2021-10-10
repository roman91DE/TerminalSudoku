#include <fmt/core.h>

#include "game.h"
#include "sudoku.h"

int main(int, char**) {
  Game game = Game(Game::Difficulty::medium);
  game.printGameState();
  game.autoSolve();
  return 0;
}
