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
#include "Student.h"

class SortUI : public QMainWindow {
public:
    explicit SortUI(QWidget *parent = nullptr);

    ~SortUI();

private:
    QComboBox *sortTypeComboBox;
    QComboBox *dataTypeComboBox;
    QComboBox *sortByComboBox;
    QSpinBox *dataSizeSpinBox;
    QSpinBox *maxValueSpinBox;
    QSpinBox *minValueSpinBox;
    QLineEdit *manualInputLineEdit;
    QPushButton *generateDataButton;
    QPushButton *loadFromFileButton;
    QPushButton *sortButton;
    QPushButton *saveToFileButton;
    QTableWidget *dataTable;

    DynamicArray<int> *intData;
    DynamicArray<Student> *studentData;

    void setupUI();

private slots:
    void onGenerateDataClicked();

    void onLoadFromFileClicked();

    void onManualInputEntered();

    void onSortButtonClicked();

    void onSaveToFileClicked();

    void addStudentToTable(int row, int column, const Student &student);
};
