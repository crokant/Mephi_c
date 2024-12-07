#include "Bot.h"

Bot::Bot(CellState ai, CellState human) : aiPlayer(ai), humanPlayer(human) {}

int Bot::evaluate(const Board& board) const {
    GameState state = board.checkGameState();
    if (state == GameState::CrossWin) return aiPlayer == CellState::Cross ? 10 : -10;
    if (state == GameState::NoughtWin) return aiPlayer == CellState::Nought ? 10 : -10;
    return 0;
}

int Bot::minimax(Board& board, int depth, bool isMaximizing) {
    int score = evaluate(board);
    if (score != 0 || board.checkGameState() == GameState::Draw) return score;

    if (isMaximizing) {
        int bestScore = std::numeric_limits<int>::min();
        for (int i = 0; i < board.getSize(); ++i) {
            for (int j = 0; j < board.getSize(); ++j) {
                if (board.isCellEmpty(i, j)) {
                    board.setCell(i, j, aiPlayer);
                    bestScore = std::max(bestScore, minimax(board, depth + 1, false));
                    board.setCell(i, j, CellState::Empty);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = std::numeric_limits<int>::max();
        for (int i = 0; i < board.getSize(); ++i) {
            for (int j = 0; j < board.getSize(); ++j) {
                if (board.isCellEmpty(i, j)) {
                    board.setCell(i, j, humanPlayer);
                    bestScore = std::min(bestScore, minimax(board, depth + 1, true));
                    board.setCell(i, j, CellState::Empty);
                }
            }
        }
        return bestScore;
    }
}

std::pair<int, int> Bot::getBestMove(Board& board) {
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = 0; j < board.getSize(); ++j) {
            if (board.isCellEmpty(i, j)) {
                board.setCell(i, j, aiPlayer);
                int score = minimax(board, 0, false);
                board.setCell(i, j, CellState::Empty);

                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }

    return bestMove;
}
