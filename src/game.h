#ifndef __GAMEHEADER__
#define __GAMEHEADER__

#include <cstdint>
#include <list>

#include "game.h"
#include "sudoku.h"
#include <memory>

class Game {
 public:
  static void runMainMenu();

 private:
  // helper constructs
  struct Move;
public:
  enum class Difficulty;
  enum class PlayMenuChoice;
 private:
  // member variables
  Sudoku* sudokuPtr;
  std::list<Game::Move>* moveMemoryPtr;
  uint32_t moveCounter;
  // methods
  Game(Game::Difficulty difficulty);
  ~Game();
  // return the number of prefilled cells for a given level of difficulty
  uint16_t getNumCells(Game::Difficulty difficulty);
  static void displayLogo();
  void printGameState() const;
Game::PlayMenuChoice  runAndReturnFromPlayMenu();
  void tryRecSolve();
  // bool isSolvable() const;
  void startNewGame(Game::Difficulty difficulty);
  // void finishGame();
  static Game::Difficulty getDifficultyFromPlayer();
  static void startGameLoop();
};

#endif
