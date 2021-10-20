#include "game.h"
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

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

void
Game::listSavedGames()
{
  uint32_t idx{ 0 };
  std::string path{ "boards" };
  for (const auto& entry : std::filesystem::directory_iterator(path))
    fmt::print("{}. - {}\n", ++idx, entry.path().string());
}

std::string
Game::getGamePath()
{
  fmt::print("Saved games:\n");
  Game::listSavedGames();
  fmt::print("Load game number = ");

  uint16_t usrChoice{ 0 };
  std::cin >> usrChoice;
  uint32_t idx{ 0 };

  std::string path = "boards";
  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    if ((++idx) == usrChoice) {
      return entry.path().string();
    }
  }
  if (idx <= 1) { // ok???
    throw std::runtime_error("No saved games - Starting new game!\n");
  }
  fmt::print("Invalid Choice - Pick a number between {} and {} to select an "
             "existing game!\n",
             1,
             idx);
  Game::flushStdin();
  return Game::getGamePath();
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
      try {
        Game::Game::startGameLoop(Game::Difficulty::empty, Game::getGamePath());
        break;
      } catch (const std::runtime_error& err) {
        fmt::print("Error - {}", err.what());
        Game::startGameLoop(Game::getDifficultyFromPlayer(), std::string{});
        break;
      }

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

bool
Game::isSolved() const
{
  return sudokuPtr->isSolved();
}

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

    if (game.isSolved()) {
      if (game.newOrMain()) {
        game.setUpNewGame(Game::getDifficultyFromPlayer());
      } else {
        usersLastChoice = Game::PlayMenuChoice::toMainMenu;
      }
    }
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

// // returns true if user chooses another game and false if he wants back to
// main menu
bool
Game::newOrMain() const
{
  fmt::print("The current Board has been solved, what do you want to do "
             "next?\n1 - Start new game\n2 - Return to main menu\n:");
  uint16_t usrChoice{};
  std::cin >> usrChoice;
  if ((std::cin.bad() || ((usrChoice < 1) || (usrChoice > 2)))) {
    fmt::print("Invalid Input - Please try again!\n");
    Game::flushStdin();
    return newOrMain();
  }
  if (usrChoice == 1)
    return true;
  else if (usrChoice == 2)
    return false;
  else {
    throw std::runtime_error("Something went wrong after a board was solved!");
  }
}

void
Game::handleUserCellEntry() // make bulletproof
{
  uint16_t rowUsr{ 0 }, colUsr{ 0 }, value{ 0 };
  fmt::print("Enter Row: ");
  if ((!(std::cin >> rowUsr)) ||
      ((rowUsr < 1) ||
       (rowUsr >
        9))) { // use boolean expression for side effect AND checks ranges
    fmt::print("Invalid Input: Rows are indexed from 1 - 9\n");
    return;
  }
  fmt::print("Enter Column: ");
  if ((!(std::cin >> colUsr)) || ((colUsr < 1) || (colUsr > 9))) { // ...
    fmt::print("Invalid Input: Columns are indexed from 1 - 9\n");
    return;
  }
  fmt::print("Enter Value: ");
  if ((!(std::cin >> value)) || ((value < 1) || (value > 9))) { // ...
    fmt::print("Invalid Input: Values can range from 1 - 9\n");
    return;
  }
  // adjust index for row and col user input
  uint16_t row = rowUsr - 1;
  uint16_t col = colUsr - 1;

  // check if cell is empty
  if (sudokuPtr->getCell(row, col)) {
    fmt::print("Illegal operation - Cell at {}. row and {}. column is already "
               "filled with value {}!\n",
               rowUsr,
               colUsr,
               sudokuPtr->getCell(row, col));
    return;
  }

  if (sudokuPtr->isPossible(value, row, col)) {
    sudokuPtr->setCell(value, row, col);
    moveMemory.emplace_back(Move(row, col, value));
  } else {
    fmt::print(
      "Illegal operation - Cant assign value {} to position {}/{} [row/col]\n",
      value,
      rowUsr,
      colUsr);
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
    fmt::print("Found a possible Solution to the current Board: \n");
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