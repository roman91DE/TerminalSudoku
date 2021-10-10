#ifndef __GAMEHEADER__
#define __GAMEHEADER__

#include <cstdint>
#include <list>

#include "game.h"
#include "sudoku.h"

class Game
{
private:
  // structs/classes
  // -------------
  // represents an individual move by the player
  struct Move;
  // is used to determine the number of prefilled cells
  enum class Difficulty;
  //  member variables
  // -----------------
  // points to current playing sudoku instance
  Sudoku* sudokuPtr;
  // memory of past moves
  std::list<Game::Move>* moveMemoryPtr;
  uint32_t moveCounter;
  //  methods
  // ------
  // construct a game with a partially filled sudoku board
  Game(Game::Difficulty difficulty);
  // free resources
  ~Game();
  // return the number of prefilled cells for a given level of difficulty
  uint16_t getNumCells(Game::Difficulty difficulty);
  static void displayLogo();
  void printGameState() const;
  // try to solve current board
  void autoSolve();
  void startNewGame(Game::Difficulty difficulty);
  // void finishGame();
  static Game::Difficulty getDifficultyFromPlayer();
  enum class PlayMenuChoice;
  PlayMenuChoice runPlayMenu();
  static void startGame();

public:
  static void runMainMenu();
};

#endif
