#include "game.h"
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <limits>

enum class Game::Difficulty
{
  empty = 0,
  easy = 1,
  medium = 2,
  hard = 3
};

Game::Difficulty
Game::getDifficultyFromPlayer()
{

  fmt::print("Choose Level of Difficulty\n1 - Easy\n2 - Medium\n3 - Hard\n:");
  uint16_t usrInput{ 0 };
  std::cin >> usrInput;
  if (usrInput < static_cast<uint16_t>(Game::Difficulty::easy) ||
      usrInput > static_cast<uint16_t>(Game::Difficulty::hard)) {
    fmt::print("{} is not a valid Choice!\n", usrInput);
    flushStdin();
    return Game::getDifficultyFromPlayer();
  }
  return static_cast<Game::Difficulty>(usrInput);
}

struct Game::Move
{
  uint16_t row, col, val;
  Move(uint16_t _row, uint16_t _col, uint16_t _val)
    : row(_row)
    , col(_col)
    , val(_val)
  {}
};

Game::Game(Game::Difficulty difficulty)

  : sudokuPtr(std::make_unique<Sudoku>(Sudoku()))
  , moveMemory(std::vector<Game::Move>{})

{
  sudokuPtr->randomInit(getNumCells(difficulty));
}

Game::~Game() {}

void
Game::printGameState() const
{
  fmt::print("Number of moves: {}\n\n", moveMemory.size());
  sudokuPtr->printSudoku();
}

void
Game::flushStdin()
{
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void
Game::setUpNewGame(Game::Difficulty difficulty)
{
  moveMemory.clear();
  sudokuPtr->resetSudoku();
  sudokuPtr->randomInit(getNumCells(difficulty));
}

uint16_t
Game::getNumCells(Game::Difficulty difficulty)
{
  switch (difficulty) {
    case Game::Difficulty::empty:
      return 0;
    case Game::Difficulty::easy:
      return 8;
    case Game::Difficulty::medium:
      return 12;
    case Game::Difficulty::hard:
      return 16;
    default:
      return 8; 
  }
}

void
Game::displayLogo()
{
  std::ifstream ifs;
  std::string buffer;
  ifs.open("media/logo.txt");
  if (ifs.is_open()) {
    while (getline(ifs, buffer)) {
      fmt::print("{}\n", buffer);
    }
  }
}

enum class Game::MainMenuChoice
{
  invalid = 0,
  startNewGame,
  loadGame,
  // ...
  // insert new options above
  exitTerminalSudoku
};

// read from stdin, loops until a valid input for mainMenu is entered
enum Game::MainMenuChoice
Game::getMainMenuChoice()
{
  uint16_t inputVal{ 0 };
  std::cin >> inputVal;
  if ((inputVal <= static_cast<uint16_t>(Game::MainMenuChoice::invalid)) ||
      (inputVal >
       static_cast<uint16_t>(Game::MainMenuChoice::exitTerminalSudoku))) {
    fmt::print("Invalid Choice, please try again!\n");
    flushStdin();
    return Game::getMainMenuChoice();
  }
  return static_cast<Game::MainMenuChoice>(inputVal);
}

// dummy function - needs to get path from stdin prompt
const std::string
Game::getBoardPath()
{
  return std::string{ "example.txt" };
}

void
Game::runMainMenu()
{
  Game::displayLogo();
  fmt::print("Please select action:\n1 - Start a new Game\n2 - Load Game\n3 - "
             "Exit Terminal "
             "SuDoKu\n:");
  Game::MainMenuChoice usrChoice = Game::getMainMenuChoice();
  switch (usrChoice) {

    case Game::MainMenuChoice::startNewGame:
      Game::startGameLoop(Game::getDifficultyFromPlayer(), std::string{});
      break;
    case Game::MainMenuChoice::loadGame:
      Game::startGameLoop(Game::Difficulty::empty, Game::getBoardPath());
      break;
    case Game::MainMenuChoice::exitTerminalSudoku:
      return;
    default:
      std::cerr << "An error occurred in function runMainMenu() - Shut down "
                   "current session!\n";
  }
}

enum class Game::PlayMenuChoice
{
  invalid = 0,
  enterValue,
  reverseLast,
  autoSolve,
  startNewGame,
  saveGame,
  // ...
  // insert new options above
  toMainMenu,
};

void
Game::startGameLoop(Game::Difficulty difficulty, std::string boardPath)
{
  Game game = Game(difficulty);
  if (boardPath.size() > 0) { // if boardPath string not empty, try to read it
    // Game game{ Game::Difficulty::easy };   ->  Bug???
    game.loadSavedGame(boardPath);
  }
  Game::PlayMenuChoice usersLastChoice{ Game::PlayMenuChoice::invalid };
  while (usersLastChoice != Game::PlayMenuChoice::toMainMenu) {
    usersLastChoice = game.runPlayMenu();
  }
  game.runMainMenu();
}

enum Game::PlayMenuChoice
Game::getPlayMenuChoice()
{ // read from stdin, loops until a valid input for playMenu is entered
  uint16_t inputVal{ 0 };
  std::cin >> inputVal;
  if ((inputVal <= static_cast<uint16_t>(Game::PlayMenuChoice::invalid)) ||
      (inputVal > static_cast<uint16_t>(Game::PlayMenuChoice::toMainMenu))) {
    fmt::print("Invalid Choice, please try again!\n");
    flushStdin();
    return Game::getPlayMenuChoice();
  }
  return static_cast<Game::PlayMenuChoice>(inputVal);
}

Game::PlayMenuChoice
Game::runPlayMenu() // split into displayPlayMenu() and getFromPlayMenu() ?
{
  // display
  printGameState();
  fmt::print("1 - Enter Value\n2 - Reverse last\n3 - Show Solution (finishes "
             "current game)\n4 - Start new Game\n5 - Save current Game\n6 - "
             "Back to main Menu\n");
  fmt::print("Select action\n:");

  Game::PlayMenuChoice usrChoice = Game::getPlayMenuChoice();

  switch (usrChoice) {
      // interactive play menu
    case Game::PlayMenuChoice::enterValue:
      Game::handleUserCellEntry();
      return usrChoice;

    case Game::PlayMenuChoice::reverseLast:
      Game::reverseLastMove();
      return usrChoice;

    case Game::PlayMenuChoice::autoSolve:
      Game::tryRecSolve();
      return usrChoice;

    case Game::PlayMenuChoice::startNewGame:
      Game::setUpNewGame(Game::getDifficultyFromPlayer());
      return usrChoice;

    case Game::PlayMenuChoice::saveGame:
      Game::saveCurrentGame();
      return usrChoice;

    case Game::PlayMenuChoice::toMainMenu:
      return usrChoice;

    default:
      return Game::PlayMenuChoice::invalid;
      ;
  }
}

void
Game::handleUserCellEntry() // make bulletproof
{
  uint16_t row{ 0 }, col{ 0 }, value{ 0 };
  fmt::print("Enter Row: ");
  if ((!(std::cin >> row)) ||
      ((row < 1) ||
       (row > 9))) { // use boolean expression for side effect AND checks ranges
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
    fmt::print(
      "Illegal operation - Cant assign value {} to position {}/{} [row/col]\n",
      value,
      row,
      col);
  }
}

void
Game::reverseLastMove()
{
  if (moveMemory.empty()) {
    fmt::print("No more moves to reverse!\n");
  } else {
    sudokuPtr->clearCell(moveMemory[moveMemory.size() - 1].row,
                         moveMemory[moveMemory.size() - 1].col);
    moveMemory.pop_back();
  }
}

void
Game::tryRecSolve()
{
  if (sudokuPtr->solve()) {
    fmt::print("Found this possible Solution to the current Board: \n");
    sudokuPtr->printSudoku();
  } else {
    fmt::print("Board is unsolvable in its current state!\n");
  }
}

void
Game::saveCurrentGame() const
{
  try {
    sudokuPtr->writeToFile();
    fmt::print("Current Board has been successfully written to file\n");
  } catch (const std::runtime_error& err) {
    std::cerr << "Error occured: " << err.what()
              << "\nGame could not be saved!";
  }
}

void
Game::loadSavedGame(const std::string path)
{
  try {
    if (sudokuPtr->setFromFile(path)) {
      fmt::print("Succesfully loaded {}\n", path);
    } else {
      fmt::print(
        "The provided file {} is unsolvable!\nStarted new Game instead!\n",
        path);
    }
  } catch (const std::runtime_error& err) {
    fmt::print("An Error occured: {}\nStarted new Game instead!\n", err.what());
  }
}