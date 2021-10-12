#ifndef __SUDOKUHEADER__
#define __SUDOKUHEADER__

#include <array>
#include <cstdint>
#include <random>
class Sudoku {
 public:
  Sudoku();
  Sudoku(const Sudoku &sudoku);
  ~Sudoku();
  uint16_t getCell(uint16_t row, uint16_t col) const;
  void setCell(uint16_t val, uint16_t row, uint16_t col);
  void clearCell(uint16_t row, uint16_t col);
  bool isPossible(uint16_t val, uint16_t row, uint16_t col) const;
  bool isSolved() const;
  void resetSudoku();
  void printSudoku() const;
  bool solve();
  void randomInit(uint16_t numCells);

 private:
  std::array<std::array<uint16_t, 9>, 9> board;
  // random number factory
  inline static std::default_random_engine generator{
      std::default_random_engine()};
  inline static std::uniform_int_distribution<uint16_t> distribution{
      std::uniform_int_distribution<uint16_t>(0, 8)};
  // control variables
  static constexpr uint32_t safetyLimit{1'000'000}, checkSum{405}, initSeed{20};
  // manipulate random cells of the board
  void randSet();
  void randClear();
  // backtrack solution
  void recursiveSolve();
  struct stopRecursion {};
  static inline void printLine();
};

#endif