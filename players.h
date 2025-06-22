#pragma once
#include "board.h"

class Player {
public:
    virtual void makeMove(Board& board, char symbol) = 0;
    virtual ~Player() = default;
};

class HumanPlayer : public Player {
public:
    void makeMove(Board& board, char symbol) override;
};

class AIPlayer : public Player {
public:
    void makeMove(Board& board, char symbol) override;
};
