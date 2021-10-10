#ifndef __GAMEHEADER__
#define __GAMEHEADER__

#include <cstdint>
#include <list>

#include "game.h"
#include "sudoku.h"

class Game {
 private:
  // structs
  // -------------
  // represents an individual move by the player
  struct Move {
    uint16_t row, col, val;
    Move(uint16_t _row, uint16_t _col, uint16_t _val);
  };
  //  member variables
  // -----------------
  // points to current playing sudoku instance
  Sudoku* sudokuPtr;
  // memory of past moves
  std::list<Game::Move>* moveMemoryPtr;
  uint32_t moveCounter;
  //  methods
  // ------

 public:
  // structs
  // -------
  // is used to determine the number of prefilled cells
  enum class Difficulty { easy = 0, medium = 1, hard = 2 };
  // interface
  // ---------
  // construct an empty Game instance
  Game();
  // construct a partially filled Game
  Game(Game::Difficulty difficulty);
  // free resources
  ~Game();
  void printGameState() const;
  // try to solve current board
  void autoSolve();
};

#endif