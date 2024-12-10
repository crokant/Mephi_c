#include "TictactoeUI.h"
#include <QMessageBox>
#include <QFont>

TictactoeUI::TictactoeUI(QWidget *parent)
        : QWidget(parent),
          game(3),
          gridLayout(new QGridLayout()),
          mainLayout(new QVBoxLayout(this)),
          titleLabel(new QLabel("Крестики-нолики")),
          newGameButton(new QPushButton("Новая игра")) {
    setWindowTitle("TicTacToe");
    setFixedSize(340, 440);

    createUI();
    resetGame();
}

void TictactoeUI::createUI() {
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Arial", 24, QFont::Bold));
    titleLabel->setStyleSheet("color: #555;");
    newGameButton->setFont(QFont("Arial", 16));
    newGameButton->setStyleSheet("background-color: #4CAF50; color: white; padding: 10px; border-radius: 7px;");

    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(newGameButton);

    connect(newGameButton, &QPushButton::clicked, this, &TictactoeUI::onNewGameClicked);
}

void TictactoeUI::resetGame() {
    while (QLayoutItem *item = gridLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    game = Game(3);
    buttons.clear();

    for (int i = 0; i < 9; ++i) {
        auto button = new QPushButton(".");
        button->setFixedSize(100, 100);
        button->setFont(QFont("Arial", 24, QFont::Bold));
        button->setStyleSheet("background-color: #F0F0F0; border: 2px solid #CCC; border-radius: 10px;");
        buttons.append(button);
        connect(button, &QPushButton::clicked, this, &TictactoeUI::handleButtonClick);
        gridLayout->addWidget(button, i / 3, i % 3);
    }
    updateBoard();
}

void TictactoeUI::handleButtonClick() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
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
        QString text = "";
        if (cell == CellState::Cross) text = "X";
        if (cell == CellState::Nought) text = "O";

        buttons[i]->setText(text);

        if (cell == CellState::Cross) {
            buttons[i]->setStyleSheet("background-color: #FFEBEE; border: 2px solid #E91E63; border-radius: 10px;");
        } else if (cell == CellState::Nought) {
            buttons[i]->setStyleSheet("background-color: #E8F5E9; border: 2px solid #4CAF50; border-radius: 10px;");
        } else {
            buttons[i]->setStyleSheet("background-color: #F0F0F0; border: 2px solid #CCC; border-radius: 10px;");
        }

        buttons[i]->setEnabled(cell == CellState::Empty);
    }
}

void TictactoeUI::onNewGameClicked() {
    resetGame();
}

