#include "game.h"
#include <iostream>
#include <stdexcept>

Game::Game() : player1(nullptr), player2(nullptr), currentPlayer('X') {}

Game::~Game() {
    delete player1;
    delete player2;
}

void Game::selectGameMode() {
    std::string input;
    int choices[2] = {0, 0};
    const char* prompts[] = {
        "Выберите режим игры:\n1. Игра против компьютера\n2. Игра против другого игрока\n",
        "Выберите, кто ходит первым:\n1. Я (X)\n2. Противник (O)\nЕсли игра против другого игрока, то без разницы\n"
    };

    for (int i = 0; i < 2; ) {
        std::cout << prompts[i] << "Ваш выбор: ";
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cerr << "\nОшибка: Ввод не может быть пустым.\n\n";
            continue;
        }

        if (input.size() != 1 || input[0] < '1' || input[0] > '2') {
            std::cerr << "\nОшибка: Введите 1 или 2.\n\n";
            continue;
        }

        choices[i] = input[0] - '0';
        i++;

        if (i < 2) std::cout << "\n";
    }

    if (choices[0] == 1) {
        if (choices[1] == 1) {
            player1 = new HumanPlayer();
            player2 = new AIPlayer();
        } else {
            player1 = new AIPlayer();
            player2 = new HumanPlayer();
        }
    } else {
        player1 = new HumanPlayer();
        player2 = new HumanPlayer();
    }
}

void Game::run() {
    try {
        selectGameMode();

        if (currentPlayer == 'O' && dynamic_cast<AIPlayer*>(player1)) {
            player1->makeMove(board, 'O');
            switchPlayer();
        }

        while (true) {
            printGrid();

            if (board.isGameOver()) {
                break;
            }

            try {
                if (currentPlayer == 'X') {
                    player1->makeMove(board, 'X');
                } else {
                    player2->makeMove(board, 'O');
                }
                switchPlayer();
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при выполнении хода: " << e.what() << "\n";
            }
        }

        printGrid();
        showGameResult();
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
    }
}



void Game::showGameResult() const {
    char winner = board.checkWinner();
    if (winner == 'X') {
        std::cout << "Игрок X победил!\n";
    } else if (winner == 'O') {
        std::cout << "Игрок O победил!\n";
    } else {
        std::cout << "Ничья!\n";
    }
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void Game::printGrid() const {
    const auto& grid = board.getGrid();
    std::cout << "\n  0 1 2\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < 3; ++j) {
            char cell = grid[i * 3 + j];
            std::cout << (cell == ' ' ? '.' : cell) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
