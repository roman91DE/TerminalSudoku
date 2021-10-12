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

void Game::flushStdin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Game::Difficulty Game::getDifficultyFromPlayer()
{

    fmt::print("Choose Level of Difficulty\n1 - Easy\n2 - Medium\n3 - Hard\n:");
    uint16_t usrInput { 0 };
    std::cin >> usrInput;
    if (usrInput < static_cast<uint16_t>(Game::Difficulty::easy) || usrInput > static_cast<uint16_t>(Game::Difficulty::hard)) {
        fmt::print("{} is not a valid Choice!\n", usrInput);
        Game::flushStdin();

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
    fmt::print(
        "Please select action:\n1 - Start a new Game\n2 - Exit Terminal "
        "SuDoKu\n:");

    uint16_t inputVal { 0 };
    std::cin >> inputVal;
    if ((inputVal < static_cast<uint16_t>(Game::MainMenuChoice::startNewGame)) || (inputVal > static_cast<uint16_t>(Game::MainMenuChoice::exitTerminalSudoku))) {
        fmt::print("Invalid Choice, please try again!\n");
        Game::flushStdin();
        Game::runMainMenu();
    }
    Game::MainMenuChoice usrChoice = static_cast<Game::MainMenuChoice>(inputVal);
    switch (usrChoice) {
    case Game::MainMenuChoice::startNewGame:
        Game::startGameLoop();
        break;
    case Game::MainMenuChoice::exitTerminalSudoku:
        return;        
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
    if (std::cin.bad())
        Game::flushStdin();
    fmt::print("1 - Enter Value\n2 - Reverse last\n3 - Start new Game\n");
    fmt::print("Select action\n:");

    int32_t inputVal;
    std::cin >> inputVal;
    if (inputVal <= (static_cast<int32_t>(Game::PlayMenuChoice::init) || inputVal >= (static_cast<int32_t>(Game::PlayMenuChoice::invalidChoice)))) {
        fmt::print("Invalid Choice - Please try again!\n");
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

void Game::promptEntry() // make bulletproof
{
    uint16_t row { 0 }, col { 0 }, value { 0 };
    fmt::print("Enter Row: ");
    if ((!(std::cin >> row)) || ((row < 1) || (row > 9))) {   // use boolean expression for side effect AND checks ranges
        fmt::print("Invalid Input: Rows are indexed from 1 - 9\n");
        return;
    }
    fmt::print("Enter Column: ");
    if ((!(std::cin >> col)) || ((col < 1) || (col > 9))) {     // ...
        fmt::print("Invalid Input: Columns are indexed from 1 - 9\n");
        return;
    }
    fmt::print("Enter Value: ");
    if ((!(std::cin >> value)) || ((value < 1) || (value > 9))) {   // ...
        fmt::print("Invalid Input: Values can range from 1 - 9\n");
        return;
    }

    if (sudokuPtr->isPossible(value, row-1, col-1)) {
        sudokuPtr->setCell(value, row-1, col-1);
        ++moveCounter;
        moveMemoryPtr.emplace_back(Move(row-1, col-1, value));
    } else {
        fmt::print("Illegal operation - Cant assign value {} to position {}/{} [row/col]\n", value, row, col);
    }
}