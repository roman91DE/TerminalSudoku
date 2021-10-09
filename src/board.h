#include <array>
#include <cstdint>

struct Board {
private:
  std::array<std::array<uint8_t, 10>, 10> board;

public:
  Board();
  int getCell(uint8_t row, uint8_t col) const;
};