#ifndef __BOARDHEADER__
#define __BOARDHEADER__

#include <array>
#include <cstdint>

struct Board {
 private:
  std::array<std::array<uint8_t, 9>, 9> board;
  static inline void printLine();

 public:
  Board();
  ~Board();
  int inline getCell(uint8_t row, uint8_t col) const;
  void inline setCell(uint8_t val, uint8_t row, uint8_t col);
  void inline clearCell(uint8_t row, uint8_t col);
  void printBoard() const;
};

#endif