#ifndef __BOARDHEADER__
#define __BOARDHEADER__

#include <array>
#include <cmath>
#include <cstdint>
#include <exception>
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
    // is thrown to exit recursive backtracking
    class stopRecursion {
    };

    // private methods
    static inline void printLine();
    bool isPossible(uint16_t val, uint16_t row, uint16_t col) const;
    void randSet();
    void randClear();
    bool isSolved() const;
    // implements recursive backtracking algorithm (internal method, must not be called directly)
    void recursiveSolve();
    void printCheckSum() const;

public:
    Board();
    ~Board();
    uint16_t getCell(uint16_t row, uint16_t col) const;
    void setCell(uint16_t val, uint16_t row, uint16_t col);
    void clearCell(uint16_t row, uint16_t col);
    void printBoard() const;
    // triggers recursive backtracking algorithm (calls recursiveSolve())
    bool solve();
};

#endif