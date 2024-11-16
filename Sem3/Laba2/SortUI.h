#pragma once

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QSpinBox>
#include <QLabel>
#include <QVBoxLayout>
#include "../../Sem2/Laba2/LABA2_Mephi/DynamicArray.h"

class SortUI : public QMainWindow {
public:
    explicit SortUI(QWidget *parent = nullptr);

    ~SortUI();

private:
    QComboBox *sortTypeComboBox;
    QSpinBox *dataSizeSpinBox;
    QSpinBox *maxValueSpinBox;
    QSpinBox *minValueSpinBox;
    QLineEdit *manualInputLineEdit;
    QPushButton *generateDataButton;
    QPushButton *loadFromFileButton;
    QPushButton *sortButton;
    QPushButton *saveToFileButton;
    QTableWidget *dataTable;

    DynamicArray<int> *data;

    void setupUI();

private slots:

    void onGenerateDataClicked();

    void onLoadFromFileClicked();

    void onManualInputEntered();

    void onSortButtonClicked();

    void onSaveToFileClicked();
};
