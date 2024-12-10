#include "../Board.h"
#include "tests.h"

void testBoardInitialization() {
    Board board(3);
    check(board.getSize() == 3);
    check(board.getCell(0, 0) == CellState::Empty);
    check(board.getCell(2, 2) == CellState::Empty);
}

void testSetCell() {
    Board board(3);
    board.setCell(0, 0, CellState::Cross);
    check(board.getCell(0, 0) == CellState::Cross);
    board.setCell(1, 1, CellState::Nought);
    check(board.getCell(1, 1) == CellState::Nought);
}

void testIsFull() {
    Board board(3);
    check(!board.isFull());
    board.setCell(0, 0, CellState::Cross);
    board.setCell(0, 1, CellState::Nought);
    board.setCell(0, 2, CellState::Cross);
    board.setCell(1, 0, CellState::Nought);
    board.setCell(1, 1, CellState::Cross);
    board.setCell(1, 2, CellState::Nought);
    board.setCell(2, 0, CellState::Cross);
    board.setCell(2, 1, CellState::Nought);
    board.setCell(2, 2, CellState::Cross);
    check(board.isFull());
}

void testCheckGameStateCrossWin() {
    Board board(3);
    board.setCell(0, 0, CellState::Cross);
    board.setCell(0, 1, CellState::Cross);
    board.setCell(0, 2, CellState::Cross);
    check(board.checkGameState() == GameState::CrossWin);
}

void testCheckGameStateDraw() {
    Board board(3);
    board.setCell(0, 0, CellState::Cross);
    board.setCell(0, 1, CellState::Nought);
    board.setCell(0, 2, CellState::Cross);
    board.setCell(1, 0, CellState::Nought);
    board.setCell(1, 1, CellState::Cross);
    board.setCell(1, 2, CellState::Nought);
    board.setCell(2, 0, CellState::Nought);
    board.setCell(2, 1, CellState::Cross);
    board.setCell(2, 2, CellState::Nought);
    check(board.checkGameState() == GameState::Draw);
}

void testEmptyCellsCount() {
    Board board(3);
    check(board.getEmptyCellsCount() == 9);
    board.setCell(0, 0, CellState::Cross);
    board.setCell(1, 1, CellState::Nought);
    check(board.getEmptyCellsCount() == 7);
}

void runBoardTests() {
    testBoardInitialization();
    testSetCell();
    testIsFull();
    testCheckGameStateCrossWin();
    testCheckGameStateDraw();
    testEmptyCellsCount();

    std::cout << "Board tests completed!" << std::endl;
}