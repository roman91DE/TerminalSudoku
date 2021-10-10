#include "game.h"
#include <fstream>

#include <fmt/core.h>

#include <iostream>

struct Game::Move {
    uint16_t row, col, val;
    Move(uint16_t _row, uint16_t _col, uint16_t _val)
        : row(_row)
        , col(_col)
        , val(_val)
    {
    }
};

enum class Game::Difficulty { easy = 1,
    medium = 2,
    hard = 3 };

Game::Game(Game::Difficulty difficulty)

    : sudokuPtr(new Sudoku())
    , moveMemoryPtr(new std::list<Game::Move>())
    , moveCounter(0)

{
    sudokuPtr->randomInit(getNumCells(difficulty));
}

Game::~Game()
{
    delete sudokuPtr;
    delete moveMemoryPtr;
}

void Game::printGameState() const
{
    fmt::print("Number of moves: {}\n\n", moveCounter);
    sudokuPtr->printSudoku();
}

void Game::autoSolve()
{
    if (sudokuPtr->solve()) {
        sudokuPtr->printSudoku();
    } else {
        fmt::print(
            "The current state of the game is not solvable!\nStart a new Game? "
            "[y/N]\n");
        char usrInput;
        std::cin >> usrInput;
        if ((usrInput == 'y') || (usrInput == 'Y'))
            startNewGame(Game::getDifficultyFromPlayer());
        else {
            // finishGame();
            return;
        }
    }
}

Game::Difficulty Game::getDifficultyFromPlayer()
{
    fmt::print("Choose Level of Difficulty\n1 - Easy\n2 - Medium\n3 - Hard\n:");
    uint16_t usrInput { 42 };
    std::cin >> usrInput;
    switch (usrInput) {
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

void Game::startNewGame(Game::Difficulty difficulty)
{
    moveMemoryPtr->clear();
    moveCounter = 0;
    sudokuPtr->resetSudoku();
    sudokuPtr->randomInit(getNumCells(difficulty));
    sudokuPtr->printSudoku();
}

uint16_t Game::getNumCells(Game::Difficulty difficulty)
{
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

void Game::displayLogo()
{
    std::ifstream ifs;
    std::string buffer;
    ifs.open("/Users/rmn/code/c/sudoku/src/logo.txt"); // change to relative path
    if (ifs.is_open()) {
        while (getline(ifs, buffer)) {
            fmt::print("{}\n", buffer);
        }
    }
}

void Game::runMainMenu()
{
    Game::displayLogo();
    while (true) {
        fmt::print("Please select action:\n1 - Start a new Game\n2 - Exit Terminal SuDoKu\n-> ");
        uint16_t choice;
        std::cin >> choice;
        switch (choice) {
        case 1:
            Game::runGame();
            break;

        case 2:
            return;

        default:
            fmt::print("Invalid Choice, please try again!\n");
        }
    }
}

enum class Game::PlayMenuChoice {
    init = 0,
    setCell,
    reverseLast,
    autoSolve,
    startNew,
    toMainMenu
};

void Game::runGame()
{
    Game game = Game(Game::getDifficultyFromPlayer());
    Game::PlayMenuChoice userRoundChoice { Game::PlayMenuChoice::init };
    while (userRoundChoice != Game::PlayMenuChoice::toMainMenu) {
        userRoundChoice = game.runPlayMenu();
    }
}

Game::PlayMenuChoice Game::runPlayMenu()
{
    // implement main logic of game (counter, memory, set, restart, solve)
    return Game::PlayMenuChoice::init;
}