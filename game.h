#pragma once
#include "board.h"
#include "players.h"

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    Board board;
    Player* player1;
    Player* player2;
    char currentPlayer;

    void selectGameMode();
    void switchPlayer();
    void showGameResult() const;
    void printGrid() const;
};