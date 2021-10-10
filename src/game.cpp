#include "game.h"

#include <fmt/core.h>

Game::Move::Move(uint16_t _row, uint16_t _col, uint16_t _val)
    : row(_row), col(_col), val(_val) {}

Game::Game()
    : moveCounter(0),
      sudokuPtr(new Sudoku()),
      moveMemoryPtr(new std::list<Game::Move>()) {}

Game::Game(Game::Difficulty difficulty)
    : moveCounter(0),
      sudokuPtr(new Sudoku()),
      moveMemoryPtr(new std::list<Game::Move>()) {
  uint16_t numCells{10};

  switch (difficulty) {
    case Game::Difficulty::easy:
      numCells = 20;
      break;
    case Game::Difficulty::medium:
      numCells = 30;
      break;
    case Game::Difficulty::hard:
      numCells = 40;
      break;
    default:
      break;
  }
  sudokuPtr->randomInit(numCells);
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
    fmt::print("The current state of the Game game is not solvable!\n");
    // restart game here
  }
}