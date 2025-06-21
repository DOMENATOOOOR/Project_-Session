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
    const std::vector<std::vector<char>>& getGrid() const;
    void reset();

private:
    std::vector<std::vector<char>> grid;
};
