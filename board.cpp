#include "board.h"

Board::Board() : grid(9, ' ') {}

bool Board::isMoveValid(int x, int y) const {
    return x >= 0 && x < 3 && y >= 0 && y < 3 && grid[toIndex(x, y)] == ' ';
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

    grid[toIndex(x, y)] = player;
}

bool Board::isGameOver() const {
    return checkWinner() != ' ' || isDraw();
}

char Board::checkWinner() const {

    for (int i = 0; i < 3; ++i) {
        if (grid[toIndex(i, 0)] != ' ' &&
            grid[toIndex(i, 0)] == grid[toIndex(i, 1)] &&
            grid[toIndex(i, 1)] == grid[toIndex(i, 2)]) {
            return grid[toIndex(i, 0)];
        }
    }


    for (int j = 0; j < 3; ++j) {
        if (grid[toIndex(0, j)] != ' ' &&
            grid[toIndex(0, j)] == grid[toIndex(1, j)] &&
            grid[toIndex(1, j)] == grid[toIndex(2, j)]) {
            return grid[toIndex(0, j)];
        }
    }


    if (grid[toIndex(0, 0)] != ' ' &&
        grid[toIndex(0, 0)] == grid[toIndex(1, 1)] &&
        grid[toIndex(1, 1)] == grid[toIndex(2, 2)]) {
        return grid[toIndex(0, 0)];
    }
    if (grid[toIndex(0, 2)] != ' ' &&
        grid[toIndex(0, 2)] == grid[toIndex(1, 1)] &&
        grid[toIndex(1, 1)] == grid[toIndex(2, 0)]) {
        return grid[toIndex(0, 2)];
    }

    return ' ';
}

bool Board::isDraw() const {
    for (char cell : grid) {
        if (cell == ' ') return false;
    }
    return true;
}

const std::vector<char>& Board::getGrid() const {
    return grid;
}

void Board::reset() {
    grid = std::vector<char>(9, ' ');
}
