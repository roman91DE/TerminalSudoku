#ifndef __SUDOKUHEADER__
#define __SUDOKUHEADER__

#include <array>
#include <cstdint>
#include <random>
#include <string>

// main class to implement representation and associated methods
class Sudoku {
public:
    // constructors & destructors
    // ----------
    Sudoku();
    Sudoku(const Sudoku& sudoku);
    ~Sudoku();

    // basic methods
    // ----------
    void setCell(uint16_t val, uint16_t row, uint16_t col);
    uint16_t getCell(uint16_t row, uint16_t col) const;
    void clearCell(uint16_t row, uint16_t col);
    bool isPossible(uint16_t val, uint16_t row, uint16_t col) const;
    void resetSudoku();

    // randomized methods
    // ----------
    void seedRandomEngine();
    void randClear();
    void randomInit(uint16_t numCells);
    void randSet();

    // solving methods
    // ----------
    bool solve();
    void recursiveSolve();
    bool isSolved() const;
    bool isSolvable() const;

     // I/O
    // ----------
    void printSudoku() const;
    void writeToFile() const;
    bool setFromFile(const std::string& filename);

private:
    std::array<std::array<uint16_t, 9>, 9> board;
    inline static std::default_random_engine generator {
        std::default_random_engine(static_cast<long unsigned int>(time(0)))
    };
    inline static std::uniform_int_distribution<uint16_t> distribution {
        std::uniform_int_distribution<uint16_t>(0, 8)
    };
    static constexpr uint32_t safetyLimit { 1'000'000 }, checkSum { 405 }, initSeed { 20 };
    struct stopRecursion {
    };
    static inline void printLine();
};

#endif