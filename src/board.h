#ifndef __BOARDHEADER__
#define __BOARDHEADER__

#include <array>
#include <cmath>
#include <cstdint>
#include <random>

class Board {

    // private member
    std::array<std::array<uint16_t, 9>, 9> board;
    // random number factory
    std::default_random_engine* generator;
    std::uniform_int_distribution<uint16_t>* distribution;
    // safety limit to avoid infinite loops (should not be reached)
    static constexpr uint32_t safetyLimit { 1'000'000 };
    // solved grid needs to sum up to checkSum
    static constexpr uint32_t checkSum { 405 };
    // boolean variable to end recursion
    bool breakRecursion;

    // private methods
    static inline void printLine();
    bool isPossible(uint16_t val, uint16_t row, uint16_t col) const;
    void randSet();
    void randClear();
    bool isSolved() const;
    void recSolve();
    void printCheckSum() const;

public:
    Board();
    ~Board();
    uint16_t getCell(uint16_t row, uint16_t col) const;
    void setCell(uint16_t val, uint16_t row, uint16_t col);
    void clearCell(uint16_t row, uint16_t col);
    void printBoard() const;
    // triggers recursive backtracking algorithm
    bool solve();
};

#endif