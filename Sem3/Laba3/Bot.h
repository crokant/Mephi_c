#pragma once

#include "Board.h"
#include "UnorderedMap.h"

class Bot {
private:
    CellState aiPlayer;
    CellState humanPlayer;
    mutable UnorderedMap<std::string, int> memo;

    int minimax(Board &board, int depth, bool isMaximizing);

    [[nodiscard]] int evaluate(const Board &board) const;

    [[nodiscard]] std::pair<int, int> findForcedMove(const Board &board, CellState player) const;

    [[nodiscard]] std::string boardKey(const Board &board) const;

public:
    Bot(CellState ai, CellState human);

    std::pair<int, int> getBestMove(Board &board);
};
