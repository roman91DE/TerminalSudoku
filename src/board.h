#ifndef __BOARDHEADER__
#define __BOARDHEADER__

#include <array>
#include <cmath>
#include <cstdint>
#include <random>

class Board {

    // private member
    std::array<std::array<uint8_t, 9>, 9> board;
    // random number factory
    std::default_random_engine* generator;
    std::uniform_int_distribution<uint8_t>* distribution;
    // safety limit to avoid infinite loops (should not be reached)
    static constexpr uint32_t safetyLimit { 1'000'000 };
    // solved grid needs to sum up to checkSum
    static constexpr uint32_t checkSum { 405 };

    // private methods
    static inline void printLine();
    bool isPossible(uint8_t val, uint8_t row, uint8_t col) const;
    void randSet();
    void randClear();
    bool isSolved() const;

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