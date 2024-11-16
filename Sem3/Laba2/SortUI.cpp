#include "SortUi.h"
#include "DataGenerator.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QTime>
#include "sorting/ISorter.h"
#include "sorting/ShellSorter.h"
#include "sorting/HeapSorter.h"
#include "sorting/QuickSorter.h"
#include "sorting/BubbleSorter.h"


SortUI::SortUI(QWidget *parent) : QMainWindow(parent) {
    setupUI();
}

SortUI::~SortUI() = default;

void SortUI::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    sortTypeComboBox = new QComboBox(this);
    sortTypeComboBox->addItems(
            {"Сортировка пузырьком", "Быстрая сортировка", "Сортировка Шелла", "Пирамидальная сортировка"});
    layout->addWidget(new QLabel("Выберите тип сортировки:", this));
    layout->addWidget(sortTypeComboBox);

    dataSizeSpinBox = new QSpinBox(this);
    dataSizeSpinBox->setRange(10, 10000000);
    dataSizeSpinBox->setValue(1000);
    layout->addWidget(new QLabel("Количество данных:", this));
    layout->addWidget(dataSizeSpinBox);

    manualInputLineEdit = new QLineEdit(this);
    layout->addWidget(new QLabel("Ручной ввод данных (через запятую):", this));
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
    connect(sortButton, &QPushButton::clicked, this, &SortUI::onSortButtonClicked);
    connect(saveToFileButton, &QPushButton::clicked, this, &SortUI::onSaveToFileClicked);
}

void SortUI::onGenerateDataClicked() {
    int size = dataSizeSpinBox->value();

    std::vector<int> data(size);

    generateRandomArray(data.data(), size, -100000, 100000);

    dataTable->setRowCount(size);
    for (int i = 0; i < size; ++i) {
        dataTable->setItem(i, 0, new QTableWidgetItem(QString::number(data[i])));
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

    QVector<int> data;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        data.append(line.toInt());
    }
    file.close();

    dataTable->setRowCount(data.size());
    for (int i = 0; i < data.size(); ++i) {
        dataTable->setItem(i, 0, new QTableWidgetItem(QString::number(data[i])));
    }

    QMessageBox::information(this, "Загрузка завершена", "Данные успешно загружены.");
}

void SortUI::onSortButtonClicked() {
    if (dataTable->rowCount() == 0) {
        QMessageBox::warning(this, "Ошибка", "Данные для сортировки отсутствуют.");
        return;
    }

    DynamicArray<int> data(dataTable->rowCount());
    for (int i = 0; i < dataTable->rowCount(); ++i) {
        bool ok;
        int value = dataTable->item(i, 0)->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Ошибка", "Некорректные данные в таблице.");
            return;
        }
        data.set(i, value);
    }

    QString selectedSort = sortTypeComboBox->currentText();
    std::unique_ptr<ISorter<int>> sorter;

    if (selectedSort == "Быстрая сортировка") {
        sorter = std::make_unique<QuickSorter<int>>();
    } else if (selectedSort == "Пирамидальная сортировка") {
        sorter = std::make_unique<HeapSorter<int>>();
    } else if (selectedSort == "Сортировка Шелла") {
        sorter = std::make_unique<ShellSorter<int>>();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неизвестный тип сортировки.");
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    sorter->sort(data.begin(), data.end(), [](const int &a, const int &b) { return a < b; });
    auto end = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < data.getSize(); ++i) {
        dataTable->setItem(i, 1, new QTableWidgetItem(QString::number(data[i])));
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
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < dataTable->rowCount(); ++i) {
        out << dataTable->item(i, 0)->text() << "\n";
    }
    file.close();

    QMessageBox::information(this, "Сохранение завершено", "Данные успешно сохранены.");
}
