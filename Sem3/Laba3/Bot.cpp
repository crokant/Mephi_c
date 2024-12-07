#include "Bot.h"

Bot::Bot(CellState ai, CellState human) : aiPlayer(ai), humanPlayer(human) {}

int Bot::evaluate(const Board& board) const {
    GameState state = board.checkGameState();
    if (state == GameState::CrossWin) return aiPlayer == CellState::Cross ? 10 : -10;
    if (state == GameState::NoughtWin) return aiPlayer == CellState::Nought ? 10 : -10;
    return 0;
}

int Bot::positionWeight(int x, int y, const Board& board) const {
    int centerWeight = 1;
    int edgeWeight = 2;
    int cornerWeight = 3;

    int size = board.getSize();

    if (x == size / 2 && y == size / 2) return centerWeight;

    if ((x == 0 && y == 0) || (x == 0 && y == size - 1) ||
        (x == size - 1 && y == 0) || (x == size - 1 && y == size - 1)) {
        return cornerWeight;
    }

    if (x == 0 || x == size - 1 || y == 0 || y == size - 1) {
        return edgeWeight;
    }

    return 1;
}

int Bot::minimax(Board& board, int depth, bool isMaximizing, int alpha, int beta, int maxDepth) {

    if (depth >= maxDepth) {
        return 0;
    }

    int score = evaluate(board);
    if (score != 0 || board.checkGameState() == GameState::Draw) return score;

    if (isMaximizing) {
        int bestScore = std::numeric_limits<int>::min();
        for (int i = 0; i < board.getSize(); ++i) {
            for (int j = 0; j < board.getSize(); ++j) {
                if (board.isCellEmpty(i, j)) {
                    board.setCell(i, j, aiPlayer);
                    bestScore = std::max(bestScore, minimax(board, depth + 1, false, alpha, beta, maxDepth));
                    board.setCell(i, j, CellState::Empty);
                    alpha = std::max(alpha, bestScore);
                    if (beta <= alpha) break;
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
                    bestScore = std::min(bestScore, minimax(board, depth + 1, true, alpha, beta, maxDepth));
                    board.setCell(i, j, CellState::Empty);
                    beta = std::min(beta, bestScore);
                    if (beta <= alpha) break;
                }
            }
        }
        return bestScore;
    }
}

std::pair<int, int> Bot::getBestMove(Board& board) {
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    int maxDepth = 4;

    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = 0; j < board.getSize(); ++j) {
            if (board.isCellEmpty(i, j)) {
                int moveWeight = positionWeight(i, j, board);
                board.setCell(i, j, aiPlayer);
                int score = minimax(board, 0, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), maxDepth);
                board.setCell(i, j, CellState::Empty);
                score += moveWeight;
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }

    return bestMove;
}
