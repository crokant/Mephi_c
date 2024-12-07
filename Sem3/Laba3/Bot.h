#pragma once

#include "Board.h"
#include <limits>

class Bot {
private:
    CellState aiPlayer;
    CellState humanPlayer;

    int minimax(Board& board, int depth, bool isMaximizing);
    [[nodiscard]] int evaluate(const Board& board) const;

public:
    Bot(CellState ai, CellState human);
    std::pair<int, int> getBestMove(Board& board);
};

