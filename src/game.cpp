#include "game.h"

#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <limits>

enum class Game::Difficulty { easy = 1,
    medium = 2,
    hard = 3 };

Game::Difficulty Game::getDifficultyFromPlayer()
{

    fmt::print("Choose Level of Difficulty\n1 - Easy\n2 - Medium\n3 - Hard\n:");
    uint16_t usrInput { 0 };
    std::cin >> usrInput;
    if (usrInput < static_cast<uint16_t>(Game::Difficulty::easy) || usrInput > static_cast<uint16_t>(Game::Difficulty::hard)) {
        fmt::print("{} is not a valid Choice!\n", usrInput);
        flushStdin();
        return Game::getDifficultyFromPlayer();
    }
    return static_cast<Game::Difficulty>(usrInput);
}

Game::Game(Game::Difficulty difficulty)

    : sudokuPtr(std::make_unique<Sudoku>(Sudoku()))
    , moveMemory(std::vector<Game::Move> {})

{
    sudokuPtr->randomInit(getNumCells(difficulty));
}

Game::~Game() { }

void Game::printGameState() const
{
    fmt::print("Number of moves: {}\n\n", moveMemory.size());
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



void Game::setUpNewGame(Game::Difficulty difficulty)
{
    moveMemory.clear();
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

enum class Game::MainMenuChoice {
    invalid = 0,
    startNewGame,
    // ...
    // insert new options above
    exitTerminalSudoku
};

enum Game::MainMenuChoice Game::getMainMenuChoice()
{ // read from stdin, loops until a valid input for mainMenu is entered
    uint16_t inputVal { 0 };
    std::cin >> inputVal;
    if ((inputVal <= static_cast<uint16_t>(Game::MainMenuChoice::invalid)) || (inputVal > static_cast<uint16_t>(Game::MainMenuChoice::exitTerminalSudoku))) {
        fmt::print("Invalid Choice, please try again!\n");
        flushStdin();
        return Game::getMainMenuChoice();
    }
    return static_cast<Game::MainMenuChoice>(inputVal);
}

void Game::runMainMenu()
{
    Game::displayLogo();
    fmt::print(
        "Please select action:\n1 - Start a new Game\n2 - Exit Terminal "
        "SuDoKu\n:");
    Game::MainMenuChoice usrChoice = Game::getMainMenuChoice();
    switch (usrChoice) {
    case Game::MainMenuChoice::startNewGame:
        Game::startGameLoop();
        break;
    case Game::MainMenuChoice::exitTerminalSudoku:
        return;
    case Game::MainMenuChoice::invalid:
        std::cerr << "An error occurred in function runMainMenu() - Shut down current session!\n";
    }
}

enum class Game::PlayMenuChoice {
    invalid = 0,
    enterValue,
    reverseLast,
    startNewGame,
    // ...
    // insert new options above
    toMainMenu,
};

void Game::startGameLoop()
{
    Game::Difficulty difficulty = Game::getDifficultyFromPlayer();
    Game game = Game(difficulty);
    Game::PlayMenuChoice usersLastChoice { Game::PlayMenuChoice::invalid};
    while (usersLastChoice != Game::PlayMenuChoice::toMainMenu) {
        usersLastChoice = game.runPlayMenu();
    }
}




enum Game::PlayMenuChoice Game::getPlayMenuChoice()
{ // read from stdin, loops until a valid input for playMenu is entered
    uint16_t inputVal { 0 };
    std::cin >> inputVal;
    if ((inputVal <= static_cast<uint16_t>(Game::PlayMenuChoice::invalid)) || (inputVal > static_cast<uint16_t>(Game::PlayMenuChoice::toMainMenu))) {
        fmt::print("Invalid Choice, please try again!\n");
        flushStdin();
        return Game::getPlayMenuChoice();
    }
    return static_cast<Game::PlayMenuChoice>(inputVal);
}


Game::PlayMenuChoice Game::runPlayMenu() // split into displayPlayMenu() and getFromPlayMenu() ?
{
    // display
    printGameState();
    fmt::print("1 - Enter Value\n2 - Reverse last\n3 - Start new Game\n");
    fmt::print("Select action\n:");

    Game::PlayMenuChoice usrChoice = Game::getPlayMenuChoice();

    switch (usrChoice) {
      // implements the interactive play menu
    case Game::PlayMenuChoice::enterValue:
        Game::handleUserCellEntry();
        return usrChoice;
    
    case Game::PlayMenuChoice::reverseLast:
          Game::reverseLastMove();
          return usrChoice;

    case Game::PlayMenuChoice::toMainMenu:
        return usrChoice;

    default:
        return Game::PlayMenuChoice::invalid;
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

void Game::handleUserCellEntry() // make bulletproof
{
    uint16_t row { 0 }, col { 0 }, value { 0 };
    fmt::print("Enter Row: ");
    if ((!(std::cin >> row)) || ((row < 1) || (row > 9))) { // use boolean expression for side effect AND checks ranges
        fmt::print("Invalid Input: Rows are indexed from 1 - 9\n");
        return;
    }
    fmt::print("Enter Column: ");
    if ((!(std::cin >> col)) || ((col < 1) || (col > 9))) { // ...
        fmt::print("Invalid Input: Columns are indexed from 1 - 9\n");
        return;
    }
    fmt::print("Enter Value: ");
    if ((!(std::cin >> value)) || ((value < 1) || (value > 9))) { // ...
        fmt::print("Invalid Input: Values can range from 1 - 9\n");
        return;
    }

    if (sudokuPtr->isPossible(value, row - 1, col - 1)) {
        sudokuPtr->setCell(value, row - 1, col - 1);
        moveMemory.emplace_back(Move(row - 1, col - 1, value));
    } else {
        fmt::print("Illegal operation - Cant assign value {} to position {}/{} [row/col]\n", value, row, col);
    }
}

void Game::reverseLastMove() {
  if (moveMemory.empty()) {
    fmt::print("No more moves to reverse!\n");
    return;
  }
  uint16_t row, col, value;
  row = moveMemory[moveMemory.size()-1].row;
  col = moveMemory[moveMemory.size()-1].col;
  value = moveMemory[moveMemory.size()-1].val;
  moveMemory.pop_back();


}