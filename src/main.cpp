#include <fmt/core.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include "game.h"
#include "sudoku.h"

int main(int, char**) {
  std::ifstream ifs;
  std::string buffer;
  ifs.open("/Users/rmn/code/c/sudoku/src/logo.txt");
  if (ifs.is_open()) {
    while (getline(ifs, buffer)) {
      fmt::print("{}\n", buffer);
    }
  }
  // Game game = Game(Game::getDifficultyFromPlayer());
  // game.printGameState();
  // game.autoSolve();
  return 0;
}
