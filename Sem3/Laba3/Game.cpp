#include "Game.h"
#include <iostream>

Game::Game(int boardSize) : board(boardSize), bot(CellState::Nought, CellState::Cross), currentPlayer(CellState::Cross) {}

void Game::playerMove() {
    int x, y;
    do {
        std::cout << "Enter your move (row and column): ";
        std::cin >> x >> y;
    } while (x < 0 || x >= board.getSize() || y < 0 || y >= board.getSize() || !board.isCellEmpty(x, y));
    board.setCell(x, y, currentPlayer);
}

void Game::botMove() {
    std::pair<int, int> bestMove = bot.getBestMove(board);
    board.setCell(bestMove.first, bestMove.second, currentPlayer);
}

void Game::start() {
    while (board.checkGameState() == GameState::InProgress) {
        board.printBoard();
        if (currentPlayer == CellState::Cross) {
            playerMove();
        } else {
            botMove();
        }
        currentPlayer = currentPlayer == CellState::Cross ? CellState::Nought : CellState::Cross;
    }

    board.printBoard();
    GameState result = board.checkGameState();
    if (result == GameState::CrossWin) {
        std::cout << "You win!\n";
    } else if (result == GameState::NoughtWin) {
        std::cout << "Bot wins!\n";
    } else {
        std::cout << "It's a draw!\n";
    }
}
