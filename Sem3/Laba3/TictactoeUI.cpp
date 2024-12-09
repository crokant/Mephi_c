#include "TictactoeUI.h"
#include <QMessageBox>

TictactoeUI::TictactoeUI(QWidget* parent)
        : QWidget(parent),
          game(3),
          gridLayout(new QGridLayout()),
          mainLayout(new QVBoxLayout(this)),
          controlsLayout(new QHBoxLayout()),
          newGameButton(new QPushButton("Новая игра")),
          sizeSelector(new QSpinBox()) {
    setWindowTitle("Tic-Tac-Toe");

    createUI();
    resetGame(3);
}

void TictactoeUI::createUI() {
    QLabel* sizeLabel = new QLabel("Размер поля:");
    sizeSelector->setRange(3, 10);
    sizeSelector->setValue(3);

    controlsLayout->addWidget(sizeLabel);
    controlsLayout->addWidget(sizeSelector);
    controlsLayout->addWidget(newGameButton);

    mainLayout->addLayout(controlsLayout);
    mainLayout->addLayout(gridLayout);

    connect(newGameButton, &QPushButton::clicked, this, &TictactoeUI::onNewGameClicked);
}

void TictactoeUI::resetGame(int boardSize) {
    while (QLayoutItem* item = gridLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    game = Game(boardSize);
    buttons.clear();
    for (int i = 0; i < boardSize * boardSize; ++i) {
        auto button = new QPushButton(".");
        button->setFixedSize(100, 100);
        button->setFont(QFont("Arial", 24));
        buttons.append(button);
        connect(button, &QPushButton::clicked, this, &TictactoeUI::handleButtonClick);
        gridLayout->addWidget(button, i / boardSize, i % boardSize);
    }
    updateBoard();
}

void TictactoeUI::handleButtonClick() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    int index = buttons.indexOf(clickedButton);

    if (index == -1 || !game.board.isCellEmpty(index / game.board.getSize(), index % game.board.getSize())) {
        return;
    }

    game.board.setCell(index / game.board.getSize(), index % game.board.getSize(), CellState::Cross);
    game.currentPlayer = CellState::Nought;
    updateBoard();

    if (game.board.checkGameState() != GameState::InProgress) {
        QString resultMessage;
        if (game.board.checkGameState() == GameState::CrossWin) {
            resultMessage = "Вы победили!";
        } else if (game.board.checkGameState() == GameState::NoughtWin) {
            resultMessage = "Бот победил!";
        } else {
            resultMessage = "Ничья!";
        }
        QMessageBox::information(this, "Результат", resultMessage);
        return;
    }

    game.botMove();
    game.currentPlayer = CellState::Cross;
    updateBoard();

    if (game.board.checkGameState() != GameState::InProgress) {
        QString resultMessage;
        if (game.board.checkGameState() == GameState::CrossWin) {
            resultMessage = "Вы победили!";
        } else if (game.board.checkGameState() == GameState::NoughtWin) {
            resultMessage = "Бот победил!";
        } else {
            resultMessage = "Ничья!";
        }
        QMessageBox::information(this, "Результат", resultMessage);
    }
}

void TictactoeUI::updateBoard() {
    for (int i = 0; i < buttons.size(); ++i) {
        CellState cell = game.board.getCell(i / game.board.getSize(), i % game.board.getSize());
        QString text = ".";
        if (cell == CellState::Cross) text = "X";
        if (cell == CellState::Nought) text = "O";
        buttons[i]->setText(text);
        buttons[i]->setEnabled(cell == CellState::Empty);
    }
}

void TictactoeUI::onNewGameClicked() {
    int newSize = sizeSelector->value();
    resetGame(newSize);
}
