#ifndef __GAMEHEADER__
#define __GAMEHEADER__

#include <cstdint>
#include <list>
#include <memory>

#include "game.h"
#include "sudoku.h"

class Game {
public:
    static void runMainMenu();

private:
    // helper constructs
    struct Move;

public:
    enum class Difficulty;
    enum class PlayMenuChoice;
    enum class MainMenuChoice;

private:
    // member variables
    std::unique_ptr<Sudoku> sudokuPtr;
    // Sudoku* sudokuPtr;
    std::vector<Game::Move> moveMemoryPtr;
    uint32_t moveCounter;
    // methods
    Game(Game::Difficulty difficulty);
    ~Game();
    // return the number of prefilled cells for a given level of difficulty
    uint16_t getNumCells(Game::Difficulty difficulty);
    static void displayLogo();
    void printGameState() const;
    Game::PlayMenuChoice runAndReturnFromPlayMenu();
    void tryRecSolve();
    // bool isSolvable() const;
    void setUpNewGame(Game::Difficulty difficulty);
    // void finishGame();
    static Game::Difficulty getDifficultyFromPlayer();
    static void startGameLoop();
    void promptEntry();
    static void flushStdin();
};

#endif
