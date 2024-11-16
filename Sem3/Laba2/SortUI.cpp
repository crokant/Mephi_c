#include "SortUI.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QTime>
#include <QTextStream>
#include <chrono>
#include "sorting/ISorter.h"
#include "sorting/ShellSorter.h"
#include "sorting/HeapSorter.h"
#include "sorting/QuickSorter.h"
#include "sorting/BubbleSorter.h"
#include "sorting/CountingSorter.h"
#include "sorting/ImprovedSelectionSorter.h"
#include "sorting/InsertionSorter.h"
#include "sorting/MergeSorter.h"
#include "sorting/SelectionSorter.h"
#include "sorting/ShakerSorter.h"
#include "sorting/TreeSorter.h"
#include "sorting/BinaryInsertionSorter.h"
#include "DataGenerator.h"

SortUI::SortUI(QWidget *parent) : QMainWindow(parent), data(nullptr) {
    setupUI();
}

SortUI::~SortUI() {
    delete data;
}

void SortUI::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    sortTypeComboBox = new QComboBox(this);
    sortTypeComboBox->addItems(
            {"Метод пузырька", "Шейкерная сортировка", "Метод простых вставок", "Сортировка выбором",
             "Сортировка подсчетом", "Метод двоичных вставок", "Квадратичная сортировка", "Сортировка деревом",
             "Сортировка слиянием", "Пирамидальная сортировка", "Быстрая сортировка", "Сортировка Шелла"});
    layout->addWidget(new QLabel("Выберите тип сортировки:", this));
    layout->addWidget(sortTypeComboBox);

    dataSizeSpinBox = new QSpinBox(this);
    dataSizeSpinBox->setRange(10, 1000000);
    dataSizeSpinBox->setValue(1000);
    layout->addWidget(new QLabel("Количество данных:", this));
    layout->addWidget(dataSizeSpinBox);

    minValueSpinBox = new QSpinBox(this);
    minValueSpinBox->setRange(-1000000, 0);
    minValueSpinBox->setValue(-100);

    maxValueSpinBox = new QSpinBox(this);
    maxValueSpinBox->setRange(1, 1000000);
    maxValueSpinBox->setValue(100);

    layout->addWidget(new QLabel("Минимальное значение:", this));
    layout->addWidget(minValueSpinBox);
    layout->addWidget(new QLabel("Максимальное значение:", this));
    layout->addWidget(maxValueSpinBox);

    manualInputLineEdit = new QLineEdit(this);
    layout->addWidget(new QLabel("Ручной ввод данных:", this));
    layout->addWidget(manualInputLineEdit);

    generateDataButton = new QPushButton("Сгенерировать данные", this);
    loadFromFileButton = new QPushButton("Загрузить из файла", this);
    sortButton = new QPushButton("Отсортировать", this);
    saveToFileButton = new QPushButton("Сохранить в файл", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(generateDataButton);
    buttonLayout->addWidget(loadFromFileButton);
    buttonLayout->addWidget(sortButton);
    buttonLayout->addWidget(saveToFileButton);
    layout->addLayout(buttonLayout);

    dataTable = new QTableWidget(this);
    dataTable->setColumnCount(2);
    dataTable->setHorizontalHeaderLabels({"Исходные данные", "Отсортированные данные"});
    dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(dataTable);

    setCentralWidget(centralWidget);

    connect(generateDataButton, &QPushButton::clicked, this, &SortUI::onGenerateDataClicked);
    connect(loadFromFileButton, &QPushButton::clicked, this, &SortUI::onLoadFromFileClicked);
    connect(manualInputLineEdit, &QLineEdit::returnPressed, this, &SortUI::onManualInputEntered);
    connect(sortButton, &QPushButton::clicked, this, &SortUI::onSortButtonClicked);
    connect(saveToFileButton, &QPushButton::clicked, this, &SortUI::onSaveToFileClicked);
}

void SortUI::onGenerateDataClicked() {
    int size = dataSizeSpinBox->value();
    int minValue = minValueSpinBox->value();
    int maxValue = maxValueSpinBox->value();
    delete data;
    data = new DynamicArray<int>(size);
    dataTable->setRowCount(size);

    for (int i = 0; i < size; ++i) {
        data->set(i, generateRandomNumber(minValue, maxValue));
        dataTable->setItem(i, 0, new QTableWidgetItem(QString::number((*data)[i])));
    }
    QMessageBox::information(this, "Генерация завершена", "Данные успешно сгенерированы.");
}

void SortUI::onLoadFromFileClicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл", "", "Text Files (*.txt)");
    if (filePath.isEmpty()) return;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл.");
        return;
    }

    QTextStream in(&file);
    QVector<int> values;
    while (!in.atEnd()) {
        bool ok;
        int value = in.readLine().toInt(&ok);
        if (ok) {
            values.append(value);
        }
    }
    file.close();

    delete data;
    data = new DynamicArray<int>(values.size());
    dataTable->setRowCount(values.size());

    for (int i = 0; i < values.size(); ++i) {
        data->set(i, values[i]);
        dataTable->setItem(i, 0, new QTableWidgetItem(QString::number(values[i])));
    }
    QMessageBox::information(this, "Загрузка завершена", "Данные успешно загружены.");
}

void SortUI::onManualInputEntered() {
    QString input = manualInputLineEdit->text().trimmed();
    if (input.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поле ввода пустое.");
        return;
    }

    QStringList items = input.split(" ", Qt::SkipEmptyParts);
    QVector<int> values;
    bool conversionOk = true;

    for (const QString &item: items) {
        bool ok;
        int value = item.trimmed().toInt(&ok);
        if (!ok) {
            conversionOk = false;
            break;
        }
        values.append(value);
    }

    if (!conversionOk) {
        QMessageBox::warning(this, "Ошибка", "Некорректные данные. Введите числа, разделённые пробелами.");
        return;
    }

    delete data;
    data = new DynamicArray<int>(values.size());
    dataTable->setRowCount(values.size());

    for (int i = 0; i < values.size(); ++i) {
        data->set(i, values[i]);
        dataTable->setItem(i, 0, new QTableWidgetItem(QString::number(values[i])));
    }
    QMessageBox::information(this, "Данные обработаны", "Данные успешно введены.");
}

void SortUI::onSortButtonClicked() {
    if (!data || data->getSize() == 0) {
        QMessageBox::warning(this, "Ошибка", "Данные для сортировки отсутствуют.");
        return;
    }

    QString selectedSort = sortTypeComboBox->currentText();
    std::unique_ptr<ISorter<int>> sorter;

    if (selectedSort == "Метод пузырька") {
        sorter = std::make_unique<BubbleSorter<int>>();
    } else if (selectedSort == "Шейкерная сортировка") {
        sorter = std::make_unique<ShakerSorter<int>>();
    } else if (selectedSort == "Метод простых вставок") {
        sorter = std::make_unique<InsertionSorter<int>>();
    } else if (selectedSort == "Сортировка выбором") {
        sorter = std::make_unique<SelectionSorter<int>>();
    } else if (selectedSort == "Сортировка подсчетом") {
        sorter = std::make_unique<CountingSorter<int>>();
    } else if (selectedSort == "Метод двоичных вставок") {
        sorter = std::make_unique<BinaryInsertionSorter<int>>();
    } else if (selectedSort == "Квадратичная сортировка") {
        sorter = std::make_unique<ImprovedSelectionSorter<int>>();
    } else if (selectedSort == "Сортировка деревом") {
        sorter = std::make_unique<TreeSorter<int>>();
    } else if (selectedSort == "Сортировка слиянием") {
        sorter = std::make_unique<MergeSorter<int>>();
    } else if (selectedSort == "Пирамидальная сортировка") {
        sorter = std::make_unique<HeapSorter<int>>();
    } else if (selectedSort == "Быстрая сортировка") {
        sorter = std::make_unique<QuickSorter<int>>();
    } else if (selectedSort == "Сортировка Шелла") {
        sorter = std::make_unique<ShellSorter<int>>();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неизвестный тип сортировки.");
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    sorter->sort(data->begin(), data->end(), [](const int &a, const int &b) { return a < b; });
    auto end = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < data->getSize(); ++i) {
        dataTable->setItem(i, 1, new QTableWidgetItem(QString::number((*data)[i])));
    }

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    QMessageBox::information(this, "Сортировка завершена",
                             QString("Данные успешно отсортированы за %1 мс").arg(duration.count()));
}

void SortUI::onSaveToFileClicked() {
    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Text Files (*.txt)");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < data->getSize(); ++i) {
        out << (*data)[i] << '\n';
    }
    file.close();

    QMessageBox::information(this, "Сохранение завершено", "Данные успешно сохранены.");
}
