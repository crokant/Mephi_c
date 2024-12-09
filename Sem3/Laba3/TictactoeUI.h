#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include "Game.h"

class TictactoeUI : public QWidget {
private:
    Game game;
    QGridLayout* gridLayout;
    QVector<QPushButton*> buttons;

    QVBoxLayout* mainLayout;
    QHBoxLayout* controlsLayout;
    QPushButton* newGameButton;
    QSpinBox* sizeSelector;

    void createUI();
    void updateBoard();
    void resetGame(int boardSize);

private slots:
    void handleButtonClick();
    void onNewGameClicked();

public:
    explicit TictactoeUI(QWidget* parent = nullptr);
};
