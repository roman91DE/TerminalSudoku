#include "game.h"

#include <fmt/core.h>
#include <iostream>

struct Game::Move {
    uint16_t row, col, val;
    Move(uint16_t _row, uint16_t _col, uint16_t _val)
    : row(_row), col(_col), val(_val) {}
  };

 enum class Game::Difficulty { easy = 1, medium = 2, hard = 3 };


Game::Game(Game::Difficulty difficulty)
    : moveCounter(0),
      sudokuPtr(new Sudoku()),
      moveMemoryPtr(new std::list<Game::Move>()) {
  sudokuPtr->randomInit(getNumCells(difficulty));
}

Game::~Game() {
  delete sudokuPtr;
  delete moveMemoryPtr;
}

void Game::printGameState() const {
  fmt::print("Number of moves: {}\n\n", moveCounter);
  sudokuPtr->printSudoku();
}

void Game::autoSolve() {
  if (sudokuPtr->solve()) {
    sudokuPtr->printSudoku();
  } else {
    fmt::print("The current state of the game is not solvable!\nStart a new Game? [y/N]\n");
    char usrInput;
    std::cin >> usrInput;
    if ((usrInput == 'y') || (usrInput == 'Y'))
      startNewGame(Game::getDifficultyFromPlayer());
    else {
      finishGame();
    }
  }
}

Game::Difficulty Game::getDifficultyFromPlayer() const {
  fmt::print("Choose Level of Difficulty\n1 - Easy\n2 - Medium\n3 - Hard\n:");
  uint16_t usrInput{42};
  std::cin >> usrInput;
  switch (usrInput){
    case 1:
    return Game::Difficulty::easy;

    case 2:
    return Game::Difficulty::medium;

    case 3: 
    return Game::Difficulty::hard;

    default:
    fmt::print("{} is not a valid Choice!\n", usrInput);
    return Game::getDifficultyFromPlayer();
  }

}

void Game::startNewGame(Game::Difficulty difficulty) {
  moveMemoryPtr->clear();
  moveCounter = 0;
  sudokuPtr->resetSudoku();
  sudokuPtr->randomInit(getNumCells(difficulty));
  sudokuPtr->printSudoku();

}

uint16_t Game::getNumCells(Game::Difficulty difficulty) {
    switch (difficulty) {
    case Game::Difficulty::easy:
      return 20;
    case Game::Difficulty::medium:
      return 30;
    case Game::Difficulty::hard:
      return 40;
    default:
      return 0;
  }
}