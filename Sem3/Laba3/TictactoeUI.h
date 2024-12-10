#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "Game.h"

class TictactoeUI : public QWidget {
private:
    Game game;
    QGridLayout *gridLayout;
    QVector<QPushButton *> buttons;

    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QPushButton *newGameButton;

    void createUI();

    void updateBoard();

    void resetGame();

private slots:

    void handleButtonClick();

    void onNewGameClicked();

public:
    explicit TictactoeUI(QWidget *parent = nullptr);
};
