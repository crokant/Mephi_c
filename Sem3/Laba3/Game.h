#pragma once

#include "Board.h"
#include "Bot.h"

class Game {
private:
    Board board;
    Bot bot;
    CellState currentPlayer;

    void playerMove();
    void botMove();

public:
    explicit Game(int boardSize);
    void start();
};


