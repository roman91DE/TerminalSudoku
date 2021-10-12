#include "game.h"

#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <limits>

enum class Game::Difficulty { easy = 1,
    medium = 2,
    hard = 3 };

Game::Game(Game::Difficulty difficulty)

    : sudokuPtr(std::make_unique<Sudoku>(Sudoku()))
    , moveMemoryPtr(std::vector<Game::Move> {})
    , moveCounter(0)

{
    sudokuPtr->randomInit(getNumCells(difficulty));
}

Game::~Game() { }

void Game::printGameState() const
{
    fmt::print("Number of moves: {}\n\n", moveCounter);
    sudokuPtr->printSudoku();
}

void Game::tryRecSolve()
{
    if (sudokuPtr->solve()) {
        sudokuPtr->printSudoku();
    } else {
        fmt::print("The game can not be solved in it's current state!\n");
    }
}

Game::Difficulty Game::getDifficultyFromPlayer()
{

    fmt::print("Choose Level of Difficulty\n1 - Easy\n2 - Medium\n3 - Hard\n:");
    uint16_t usrInput { 0 };
    std::cin >> usrInput;
    if (usrInput < static_cast<uint16_t>(Game::Difficulty::easy) || usrInput > static_cast<uint16_t>(Game::Difficulty::hard)) {
        fmt::print("{} is not a valid Choice!\n", usrInput);
        // ignore previous input and reset state of cin
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return Game::getDifficultyFromPlayer();
    }
    return static_cast<Game::Difficulty>(usrInput);
}

void Game::setUpNewGame(Game::Difficulty difficulty)
{
    moveMemoryPtr.clear();
    moveCounter = 0;
    sudokuPtr->resetSudoku();
    sudokuPtr->randomInit(getNumCells(difficulty));
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

enum class Game::MainMenuChoice { startNewGame = 1,
    exitTerminalSudoku };

void Game::runMainMenu()
{
    Game::displayLogo();
    while (true) {
        fmt::print(
            "Please select action:\n1 - Start a new Game\n2 - Exit Terminal "
            "SuDoKu\n:");

        uint16_t inputVal;
        std::cin >> inputVal;
        Game::MainMenuChoice usrChoice = static_cast<Game::MainMenuChoice>(inputVal);
        switch (usrChoice) {
        case Game::MainMenuChoice::startNewGame:
            Game::startGameLoop();
            break;
        case Game::MainMenuChoice::exitTerminalSudoku:
            return;
        default:
            fmt::print("Invalid Choice, please try again!\n");
        }
    }
}

enum class Game::PlayMenuChoice {
    init = 0,
    enterValue,
    reverseLast,
    startNewGame,
    toMainMenu,
    invalidChoice
};

void Game::startGameLoop()
{
    Game game = Game(Game::getDifficultyFromPlayer());
    Game::PlayMenuChoice usersLastChoice { Game::PlayMenuChoice::init };
    while (usersLastChoice != Game::PlayMenuChoice::toMainMenu) {
        usersLastChoice = game.runAndReturnFromPlayMenu();
    }
}

Game::PlayMenuChoice Game::runAndReturnFromPlayMenu()
{
    // display
    printGameState();
    fmt::print("1 - Enter Value\n2 - Reverse last\n3 - Start new Game\n");
    fmt::print("Select action\n:");

    int32_t inputVal;
    std::cin >> inputVal;
    if (inputVal <= (static_cast<int32_t>(Game::PlayMenuChoice::init) || inputVal >= (static_cast<int32_t>(Game::PlayMenuChoice::invalidChoice)))) {
        fmt::print("Invalid Choice - Please try again!\n");
        // ignore previous input and reset state of cin
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return Game::runAndReturnFromPlayMenu();
    }
    Game::PlayMenuChoice usrChoice = static_cast<Game::PlayMenuChoice>(inputVal);

    switch (usrChoice) {
    case Game::PlayMenuChoice::enterValue:
        Game::promptEntry();
        return usrChoice;

    case Game::PlayMenuChoice::toMainMenu:
        return usrChoice;

    default:
        return Game::PlayMenuChoice::invalidChoice;
        ;
    }

    // to do
    // implement main logic of game (counter, memory, set, restart, solve)
}

struct Game::Move {
    uint16_t row, col, val;
    Move(uint16_t _row, uint16_t _col, uint16_t _val)
        : row(_row)
        , col(_col)
        , val(_val)
    {
    }
};

void Game::promptEntry()
{
    uint16_t row, col, value;
    fmt::print("Enter Row    = ");
    std::cin >> row;
    fmt::print("Enter Column = ");
    std::cin >> col;
    fmt::print("Enter Value  = ");
    std::cin >> value;
    // convert row and col to 0 index
    --row;
    --col;
    if (sudokuPtr->isPossible(value, row, col)) {
        sudokuPtr->setCell(value, row, col);
        ++moveCounter;
        moveMemoryPtr.emplace_back(Move(row, col, value));
    } else {
        fmt::print("Illegal operation - Cant assign value {} to position {}/{} [row/col]\n", value, row + 1, col + 1);
    }
}