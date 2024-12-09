#include "Board.h"
#include <algorithm>

Board::Board(int boardSize) : size(boardSize), grid(boardSize, std::vector<CellState>(boardSize, CellState::Empty)) {}

bool Board::isFull() const {
    for (const auto& row : grid)
        for (auto cell : row)
            if (cell == CellState::Empty)
                return false;
    return true;
}

bool Board::isCellEmpty(int x, int y) const {
    return grid[x][y] == CellState::Empty;
}

void Board::setCell(int x, int y, CellState state) {
    grid[x][y] = state;
}

CellState Board::getCell(int x, int y) const {
    return grid[x][y];
}

int Board::getSize() const {
    return size;
}

GameState Board::checkGameState() const {
    for (int i = 0; i < size; ++i) {
        if (grid[i][0] != CellState::Empty && std::all_of(grid[i].begin(), grid[i].end(), [this, i](CellState s) { return s == grid[i][0]; }))
            return grid[i][0] == CellState::Cross ? GameState::CrossWin : GameState::NoughtWin;

        if (grid[0][i] != CellState::Empty) {
            bool columnWin = true;
            for (int j = 0; j < size; ++j)
                if (grid[j][i] != grid[0][i]) {
                    columnWin = false;
                    break;
                }
            if (columnWin)
                return grid[0][i] == CellState::Cross ? GameState::CrossWin : GameState::NoughtWin;
        }
    }

    if (grid[0][0] != CellState::Empty) {
        bool diag1Win = true;
        for (int i = 0; i < size; ++i)
            if (grid[i][i] != grid[0][0]) {
                diag1Win = false;
                break;
            }
        if (diag1Win)
            return grid[0][0] == CellState::Cross ? GameState::CrossWin : GameState::NoughtWin;
    }

    if (grid[0][size - 1] != CellState::Empty) {
        bool diag2Win = true;
        for (int i = 0; i < size; ++i)
            if (grid[i][size - 1 - i] != grid[0][size - 1]) {
                diag2Win = false;
                break;
            }
        if (diag2Win)
            return grid[0][size - 1] == CellState::Cross ? GameState::CrossWin : GameState::NoughtWin;
    }

    if (isFull())
        return GameState::Draw;

    return GameState::InProgress;
}

int Board::getEmptyCellsCount() const {
    int count = 0;
    for (const auto& row : grid) {
        count += std::count(row.begin(), row.end(), CellState::Empty);
    }
    return count;
}
