#include "players.h"
#include <limits>
#include <iostream>

void HumanPlayer::makeMove(Board& board, char symbol) {
    int x, y;
    while (true) {
        try {
            std::cout << "Игрок " << symbol << ", ваш ход (строка и столбец от 0 до 2): ";
            if (!(std::cin >> x >> y)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Некорректный ввод. Введите два числа от 0 до 2.");
            }

            if (x < 0 || x > 2 || y < 0 || y > 2) {
                throw std::out_of_range("Координаты должны быть от 0 до 2.");
            }

            if (!board.isMoveValid(x, y)) {
                throw std::logic_error("Эта клетка уже занята.");
            }

            board.makeMove(x, y, symbol);
            break;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
void AIPlayer::makeMove(Board& board, char symbol) {

    char opponent = (symbol == 'O') ? 'X' : 'O';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.isMoveValid(i, j)) {
                Board temp = board;
                temp.makeMove(i, j, symbol);
                if (temp.checkWinner() == symbol) {
                    board.makeMove(i, j, symbol);
                    return;
                }
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.isMoveValid(i, j)) {
                Board temp = board;
                temp.makeMove(i, j, opponent);
                if (temp.checkWinner() == opponent) {
                    board.makeMove(i, j, symbol);
                    return;
                }
            }
        }
    }

    const std::vector<std::pair<int, int>> priorityMoves = {
        {1, 1},
        {0, 0}, {0, 2}, {2, 0}, {2, 2},
        {0, 1}, {1, 0}, {1, 2}, {2, 1}
    };

    for (const auto& move : priorityMoves) {
        if (board.isMoveValid(move.first, move.second)) {
            board.makeMove(move.first, move.second, symbol);
            return;
        }
    }
}
