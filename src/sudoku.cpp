
#include "sudoku.h"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <exception>
#include <fmt/core.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// constructors & destructors
// ----------

Sudoku::Sudoku()
{
  for (auto& row : board)
    std::fill(row.begin(), row.end(), 0);
}

Sudoku::Sudoku(const Sudoku& sudoku)
{
  std::copy(sudoku.board.begin(), sudoku.board.end(), this->board.begin());
}

Sudoku::~Sudoku() {}

// basic methods
// ----------

void
Sudoku::setCell(uint16_t val, uint16_t row, uint16_t col)
{
  this->board[row][col] = val;
}

uint16_t
Sudoku::getCell(uint16_t row, uint16_t col) const
{
  return (this->board[row][col]);
}

void
Sudoku::clearCell(uint16_t row, uint16_t col)
{
  this->setCell(0, row, col);
}

bool
Sudoku::isPossible(uint16_t val, uint16_t row, uint16_t col) const
{
  // validate args
  if ((val > 9) || ((col > 8) || (row > 8)))
    return false;

  // check row and column
  for (uint16_t idx{ 0 }; idx < 9; ++idx) {
    if ((getCell(row, idx) == val) || (getCell(idx, col) == val))
      return false;
  }
  // check square
  uint16_t rowStart = (row / 3) * 3;
  uint16_t colStart = (col / 3) * 3;
  for (uint16_t rowOffset{ 0 }; rowOffset < 3; ++rowOffset) {
    for (uint16_t colOffset{ 0 }; colOffset < 3; ++colOffset) {
      if (getCell((rowStart + rowOffset), (colStart + colOffset)) == val)
        return false;
    }
  }
  return true;
}

void
Sudoku::resetSudoku()
{
  for (auto& row : board)
    std::fill(row.begin(), row.end(), 0);
}

// randomized methods
// ----------

void
Sudoku::seedRandomEngine()
{
  Sudoku::generator.seed(static_cast<long unsigned int>(time(0)));
}

void
Sudoku::randSet()
{
  for (uint64_t counter{ 0 }; counter < Sudoku::safetyLimit; ++counter) {
    uint16_t row = Sudoku::distribution(Sudoku::generator);
    uint16_t col = Sudoku::distribution(Sudoku::generator);
    uint16_t val = Sudoku::distribution(Sudoku::generator) + 1;
    if (isPossible(val, row, col)) {
      setCell(val, row, col);
      return;
    }
  }
}

void
Sudoku::randClear()
{
  for (uint64_t counter{ 0 }; counter < Sudoku::safetyLimit; ++counter) {
    uint16_t row = Sudoku::distribution(Sudoku::generator);
    uint16_t col = Sudoku::distribution(Sudoku::generator);
    if (getCell(row, col) > 0) {
      clearCell(row, col);
      return;
    }
  }
}

// fills the board with numCells random values - checks that result is solvable
void
Sudoku::randomInit(uint16_t numCells)
{

  for (uint16_t counter{ 0 }; counter < Sudoku::initSeed; ++counter)
    randSet();
  // solve sudoku
  solve();
  // safety check: sudoku must be solvable
  if (!isSolved()) {
    std::cerr
      << "Backtracking failed at solving the current Sudoku!\nRepeating "
         "randomization...\n";
    resetSudoku();
    return randomInit(numCells); // check this: solve / init didnt work properly
  }
  // delete random cells until numCells are left
  for (uint16_t counter{ 9 * 9 }; counter > numCells; --counter)
    randClear();
}

// solving methods
// ----------

bool
Sudoku::solve()
{
  try {
    recursiveSolve();
  } catch (Sudoku::stopRecursion) {
    return true;
  }
  return false;
}

void
Sudoku::recursiveSolve()
{
  for (uint16_t rowIdx{ 0 }; rowIdx < 9; ++rowIdx) {
    for (uint16_t colIdx{ 0 }; colIdx < 9; ++colIdx) {
      if (getCell(rowIdx, colIdx) == 0) {
        for (uint16_t pval{ 1 }; pval < 10; ++pval) {
          if (isPossible(pval, rowIdx, colIdx)) {
            setCell(pval, rowIdx, colIdx);
            recursiveSolve();
            clearCell(rowIdx, colIdx);
          }
        }
        return;
      }
    }
  }
  throw Sudoku::stopRecursion();
}

bool
Sudoku::isSolved() const
{
  uint32_t sum{ 0 };
  for (const auto& row : board) {
    for (const auto& col : row) {
      sum += col;
    }
  }
  return (sum == Sudoku::checkSum);
}

bool
Sudoku::isSolvable() const
{
  Sudoku test = Sudoku(*(this));
  if (test.solve())
    return true;
  else
    return false;
}

// I/O
// ----------

void
Sudoku::printLine()
{
  fmt::print(" +-----------+\n");
}

void
Sudoku::printSudoku() const
{
  uint16_t rowCount{ 0 }, colCount{ 0 }, lineCount{ 0 };
  fmt::print("  123 456 789 \n");
  Sudoku::printLine();

  for (const auto& row : board) {
    if ((rowCount++) == 3) {
      Sudoku::printLine();
      rowCount = 1;
    }
    colCount = 0;
    fmt::print("{}", ++lineCount);
    for (const auto& cell : row) {
      if ((colCount--) == 0) {
        fmt::print("|");
        colCount = 2;
      }
      if (cell == 0)
        fmt::print(" ");
      else
        fmt::print("{}", cell);
    }
    fmt::print("|\n");
  }
  Sudoku::printLine();
  fmt::print("\n");
}

void
Sudoku::writeToFile() const
{
  // construct a timestamped filename
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%d%m%Y%H%M%S.txt");
  std::string path{ "boards/" + oss.str() };

  std::ofstream file;
  file.open(path);
  if (!file.is_open()) {
    throw std::runtime_error("Error while trying to open File: " + path + "\n");
  }
  for (const auto& row : board) {
    for (const auto& cell : row) {
      file << cell << ' ';
    }
    file << '\n';
  }
  file.close();
}

bool
Sudoku::setFromFile(const std::string& filename)
{
  std::ifstream file;
  std::string path{ "boards/" + filename };
  file.open(path);
  if (!file.is_open()) {
    throw std::runtime_error("Error while trying to read from File: " + path +
                             "\n");
  }
  uint16_t buffer;
  for (uint16_t row{ 0 }; row < 9; ++row) {
    for (uint16_t col{ 0 }; col < 9; ++col) {
      file >> buffer;
      if (file.bad()) {
        throw std::runtime_error(
          "Format Error occured while trying to read from File: " + path +
          "\n");
      }
      setCell(buffer, row, col);
    }
  }
  printSudoku();
  std::cin >> buffer;
  if (!isSolvable()) {
    return false;
  }
  return true;
}