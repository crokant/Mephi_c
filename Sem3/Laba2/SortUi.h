#pragma once

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QSpinBox>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include "../../Sem2/Laba2/LABA2_Mephi/DynamicArray.h"
#include "../Laba1/UniquePtr.h"

class SortUI : public QMainWindow {


public:
    explicit SortUI(QWidget *parent = nullptr);
    ~SortUI();

private:
    QComboBox *sortTypeComboBox;         // Выбор типа сортировки
    QSpinBox *dataSizeSpinBox;           // Выбор размера данных
    QLineEdit *manualInputLineEdit;      // Поле для ручного ввода данных
    QPushButton *generateDataButton;     // Кнопка генерации данных
    QPushButton *loadFromFileButton;     // Кнопка загрузки данных из файла
    QPushButton *sortButton;             // Кнопка запуска сортировки
    QPushButton *saveToFileButton;       // Кнопка сохранения данных
    QTableWidget *dataTable;             // Таблица для отображения данных


    UniquePtr<DynamicArray<int>> data;

    void setupUI();

private slots:
    void onGenerateDataClicked();        // Обработчик генерации данных
    void onLoadFromFileClicked();        // Обработчик загрузки из файла
    void onSortButtonClicked();          // Обработчик сортировки
    void onSaveToFileClicked();          // Обработчик сохранения
};
