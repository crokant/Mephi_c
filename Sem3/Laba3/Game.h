#pragma once

#include "Board.h"
#include "Bot.h"

class Game {
public:
    Board board;
    Bot bot;
    CellState currentPlayer;

    void botMove();

    explicit Game(int boardSize);
};


