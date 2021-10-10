#ifndef __SUDOKUHEADER__
#define __SUDOKUHEADER__

#include <array>
#include <cstdint>
#include <random>

class Sudoku {
 private:
  // structs/enums
  // ---------------
  // is thrown to exit recursive backtracking
  struct stopRecursion {};
  // member variables
  // ---------------
  // represents the current state of sudoku
  std::array<std::array<uint16_t, 9>, 9> sudoku;
  // static variables
  // ---------------
  // random number factory
  inline static std::default_random_engine generator{
      std::default_random_engine()};
  inline static std::uniform_int_distribution<uint16_t> distribution{
      std::uniform_int_distribution<uint16_t>(0, 8)};
  // safety limit to avoid infinite loops (should not be reached)
  static constexpr uint32_t safetyLimit{1'000'000};
  // solved grid needs to sum up to checkSum
  static constexpr uint16_t checkSum{405};
  // is used to randomize sudokus
  static constexpr uint16_t initSeed{20};
  //  member methods
  // ---------------
  static inline void printLine();
  // tries to set a random cell of the grid
  void randSet();
  // tries to clear a random cell of the grid
  void randClear();
  // implements recursive backtracking algorithm (internal method, should not be
  // called directly)
  void recursiveSolve();
  // print current checksum (for debugging)
  void printCheckSum() const;

 public:
  // sudoku interface
  // ---------------
  Sudoku();
  ~Sudoku();
  uint16_t getCell(uint16_t row, uint16_t col) const;
  void setCell(uint16_t val, uint16_t row, uint16_t col);
  void clearCell(uint16_t row, uint16_t col);
  bool isPossible(uint16_t val, uint16_t row, uint16_t col) const;
  bool isSolved() const;
  // empty all cells
  void resetSudoku();
  void printSudoku() const;
  // starts & stops recursive backtracking algorithm
  bool solve();
  // randomizes a sudoku with numCells (only produces solvable sudokus)
  void randomInit(uint16_t numCells);
};

#endif