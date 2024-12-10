#include "../Board.h"
#include "../Bot.h"
#include "tests.h"

void testBotMove() {
    Board board(3);
    Bot bot(CellState::Cross, CellState::Nought);
    std::pair<int, int> move = bot.getBestMove(board);

    check(board.isCellEmpty(move.first, move.second));
    board.setCell(move.first, move.second, CellState::Cross);
    check(!board.isCellEmpty(move.first, move.second));
}

void testBotWin() {
    Board board(3);
    board.setCell(0, 0, CellState::Cross);
    board.setCell(0, 1, CellState::Cross);
    Bot bot(CellState::Cross, CellState::Nought);
    std::pair<int, int> move = bot.getBestMove(board);

    check(move == std::make_pair(0, 2));
}

void testBotForcedMove() {
    Board board(3);
    board.setCell(0, 0, CellState::Nought);
    board.setCell(0, 1, CellState::Nought);

    Bot bot(CellState::Cross, CellState::Nought);
    std::pair<int, int> move = bot.getBestMove(board);

    check(move == std::make_pair(0, 2));
}

void testBotDraw() {
    Board board(3);
    board.setCell(0, 0, CellState::Cross);
    board.setCell(0, 1, CellState::Nought);
    board.setCell(1, 1, CellState::Cross);
    board.setCell(1, 0, CellState::Nought);
    board.setCell(2, 0, CellState::Cross);
    board.setCell(2, 1, CellState::Nought);
    board.setCell(2, 2, CellState::Cross);

    Bot bot(CellState::Nought, CellState::Cross);
    std::pair<int, int> move = bot.getBestMove(board);

    check(board.isCellEmpty(move.first, move.second));
}

void runBotTests() {
    testBotMove();
    testBotWin();
    testBotForcedMove();
    testBotDraw();

    std::cout << "Bot tests completed!" << std::endl;
}
