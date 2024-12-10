#include "Game.h"

Game::Game(int boardSize) : board(boardSize), bot(CellState::Nought, CellState::Cross),
                            currentPlayer(CellState::Cross) {}

void Game::botMove() {
    std::pair<int, int> bestMove = bot.getBestMove(board);
    board.setCell(bestMove.first, bestMove.second, currentPlayer);
}


