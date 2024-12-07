#pragma once

#include "Board.h"
#include <limits>
#include <utility>

class Bot {
private:
    CellState aiPlayer;
    CellState humanPlayer;

    int minimax(Board& board, int depth, bool isMaximizing, int alpha, int beta, int maxDeapth);

    [[nodiscard]] int positionWeight(int x, int y, const Board& board) const;

    [[nodiscard]] int evaluate(const Board& board) const;

public:
    Bot(CellState ai, CellState human);

    std::pair<int, int> getBestMove(Board& board);
};
