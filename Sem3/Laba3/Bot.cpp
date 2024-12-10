#include "Bot.h"
#include <sstream>
#include <limits>

Bot::Bot(CellState ai, CellState human) : aiPlayer(ai), humanPlayer(human), memo(100) {}

int Bot::evaluate(const Board &board) const {
    GameState state = board.checkGameState();
    if (state == GameState::CrossWin) return aiPlayer == CellState::Cross ? 10 : -10;
    if (state == GameState::NoughtWin) return aiPlayer == CellState::Nought ? 10 : -10;
    return 0;
}

std::string Bot::boardKey(const Board &board) const {
    std::ostringstream oss;
    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = 0; j < board.getSize(); ++j) {
            oss << static_cast<int>(board.getCell(i, j)) << ",";
        }
    }
    return oss.str();
}

std::pair<int, int> Bot::findForcedMove(const Board &board, CellState player) const {
    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = 0; j < board.getSize(); ++j) {
            if (board.isCellEmpty(i, j)) {
                Board tempBoard = board;
                tempBoard.setCell(i, j, player);
                if (tempBoard.checkGameState() == (player == aiPlayer ? GameState::CrossWin : GameState::NoughtWin)) {
                    return {i, j};
                }
            }
        }
    }
    return {-1, -1};
}

int Bot::minimax(Board &board, int depth, bool isMaximizing, int alpha, int beta) {
    std::string key = boardKey(board);

    int cachedScore;
    if (memo.find(key, cachedScore)) {
        return cachedScore;
    }

    int score = evaluate(board);
    if (score != 0 || board.checkGameState() == GameState::Draw) {
        memo.insert(key, score);
        return score;
    }

    int bestScore = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = 0; j < board.getSize(); ++j) {
            if (board.isCellEmpty(i, j)) {
                board.setCell(i, j, isMaximizing ? aiPlayer : humanPlayer);
                int currentScore = minimax(board, depth + 1, !isMaximizing, alpha, beta);
                board.setCell(i, j, CellState::Empty);

                if (isMaximizing) {
                    bestScore = std::max(bestScore, currentScore);
                    alpha = std::max(alpha, bestScore);
                } else {
                    bestScore = std::min(bestScore, currentScore);
                    beta = std::min(beta, bestScore);
                }

                if (beta <= alpha) {
                    break;
                }
            }
        }
    }
    memo.insert(key, bestScore);
    return bestScore;
}

std::pair<int, int> Bot::getBestMove(Board &board) {
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    auto forcedMove = findForcedMove(board, aiPlayer);
    if (forcedMove.first != -1) {
        return forcedMove;
    }

    forcedMove = findForcedMove(board, humanPlayer);
    if (forcedMove.first != -1) {
        return forcedMove;
    }

    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = 0; j < board.getSize(); ++j) {
            if (board.isCellEmpty(i, j)) {
                board.setCell(i, j, aiPlayer);
                int score = minimax(board, 0, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
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
