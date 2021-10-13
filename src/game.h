#ifndef __GAMEHEADER__
#define __GAMEHEADER__

#include "sudoku.h"
#include <cstdint>
#include <memory>
#include <vector>

class Game {

public:
    static void runMainMenu();

private:
    struct Move;

public:
    enum class Difficulty;
    enum class PlayMenuChoice;
    enum class MainMenuChoice;

private:
    // member variables
    std::unique_ptr<Sudoku> sudokuPtr;
    std::vector<Game::Move> moveMemory;
    // methods
    Game(Game::Difficulty difficulty);
    ~Game();
    // return the number of prefilled cells for a given level of difficulty
    uint16_t getNumCells(Game::Difficulty difficulty);
    static void displayLogo();
    void printGameState() const;
    Game::PlayMenuChoice runPlayMenu();
    void tryRecSolve();
    // bool isSolvable() const;
    void setUpNewGame(Game::Difficulty difficulty);
    // void finishGame();
    static Game::Difficulty getDifficultyFromPlayer();
    static void startGameLoop();
    static enum Game::MainMenuChoice getMainMenuChoice();
    static enum Game::PlayMenuChoice getPlayMenuChoice();
    void handleUserCellEntry();
    static void flushStdin();
    void reverseLastMove();
};

#endif
