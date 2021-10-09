#ifndef __BOARDHEADER__
#define __BOARDHEADER__

#include <array>
#include <cstdint>
#include <random>

class Board {

    // private member
    std::array<std::array<uint8_t, 9>, 9> board;
    // random number factory
    std::default_random_engine* generator;
    std::uniform_int_distribution<uint8_t>* distribution;
    // safety limit to avoid infinite loops (should not be reached)
    const uint32_t safetyLimit { 1'000'000 };

    // private methods
    static inline void printLine();
    bool isPossible(uint8_t val, uint8_t row, uint8_t col) const;
    void randSet();
    void randClear();

public:
    Board();
    ~Board();
    uint8_t getCell(uint8_t row, uint8_t col) const;
    void setCell(uint8_t val, uint8_t row, uint8_t col);
    void clearCell(uint8_t row, uint8_t col);
    void printBoard() const;
    void solve();
};

#endif