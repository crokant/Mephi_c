#pragma once

#include <vector>
#include <iostream>

enum class CellState { Empty, Cross, Nought };
enum class GameState { InProgress, CrossWin, NoughtWin, Draw };

class Board {
private:
    int size;
    std::vector<std::vector<CellState>> grid;

public:
    explicit Board(int boardSize);
    [[nodiscard]] bool isFull() const;
    [[nodiscard]] bool isCellEmpty(int x, int y) const;
    void setCell(int x, int y, CellState state);
    [[nodiscard]] CellState getCell(int x, int y) const;
    [[nodiscard]] GameState checkGameState() const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] int getEmptyCellsCount() const;
};

