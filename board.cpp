#include "board.h"

Board::Board() {
    grid.resize(3, std::vector<char>(3, ' '));
}

bool Board::isMoveValid(int x, int y) const {
    return x >= 0 && x < 3 && y >= 0 && y < 3 && grid[x][y] == ' ';
}

void Board::makeMove(int x, int y, char player) {
    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        throw std::out_of_range("Неверные координаты клетки.");
    }

    if (!isMoveValid(x, y)) {
        throw std::logic_error("Недопустимый ход: клетка уже занята.");
    }

    if (player != 'X' && player != 'O') {
        throw std::invalid_argument("Неверный символ игрока. Допустимы только 'X' и 'O'.");
    }

    grid[x][y] = player;
}

bool Board::isGameOver() const {
    return checkWinner() != ' ' || isDraw();
}

char Board::checkWinner() const {
    for (int i = 0; i < 3; ++i) {
        if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
            return grid[i][0];
        }
    }

    for (int j = 0; j < 3; ++j) {
        if (grid[0][j] != ' ' && grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j]) {
            return grid[0][j];
        }
    }

    if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
        return grid[0][0];
    }
    if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
        return grid[0][2];
    }

    return ' ';
}

bool Board::isDraw() const {
    for (const auto& row : grid) {
        for (char cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
}

const std::vector<std::vector<char>>& Board::getGrid() const {
    return grid;
}

void Board::reset() {
    grid = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
}