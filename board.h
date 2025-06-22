#pragma once
#include <vector>

class Board {
public:
    Board();
    bool isMoveValid(int x, int y) const;
    void makeMove(int x, int y, char player);
    bool isGameOver() const;
    char checkWinner() const;  // 'X', 'O' или ' ' (ничья)
    bool isDraw() const;
    const std::vector<char>& getGrid() const;
    void reset();

private:
    std::vector<char> grid;
    int toIndex(int x, int y) const { return x * 3 + y; }  // Преобразование 2D в 1D
};
