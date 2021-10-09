#ifndef __BOARDHEADER__
#define __BOARDHEADER__

#include <array>
#include <cstdint>

struct Board {
 private:
  std::array<std::array<uint8_t, 9>, 9> board;
  static inline void printLine();
  bool isZero(uint8_t cell) const;

 public:
  Board();
  ~Board();
  // int getCell(uint8_t row, uint8_t col) const;
  // void setCell(uint8_t val, uint8_t row, uint8_t col);
  // void clearCell(uint8_t row, uint8_t col);
  void printBoard() const;
};

#endif