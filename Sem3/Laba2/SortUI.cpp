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


template<typename T>
std::unique_ptr<ISorter<T>> getSorter(const QString &sortType) {
    static const std::map<QString, std::function<std::unique_ptr<ISorter<T>>()>> sorterMap = {
            {"Метод пузырька",           []() { return std::make_unique<BubbleSorter<T>>(); }},
            {"Шейкерная сортировка",     []() { return std::make_unique<ShakerSorter<T>>(); }},
            {"Метод простых вставок",    []() { return std::make_unique<InsertionSorter<T>>(); }},
            {"Сортировка выбором",       []() { return std::make_unique<SelectionSorter<T>>(); }},
            {"Сортировка подсчетом",     []() { return std::make_unique<CountingSorter<T>>(); }},
            {"Метод двоичных вставок",   []() { return std::make_unique<BinaryInsertionSorter<T>>(); }},
            {"Квадратичная сортировка",  []() { return std::make_unique<ImprovedSelectionSorter<T>>(); }},
            {"Сортировка деревом",       []() { return std::make_unique<TreeSorter<T>>(); }},
            {"Сортировка слиянием",      []() { return std::make_unique<MergeSorter<T>>(); }},
            {"Пирамидальная сортировка", []() { return std::make_unique<HeapSorter<T>>(); }},
            {"Быстрая сортировка",       []() { return std::make_unique<QuickSorter<T>>(); }},
            {"Сортировка Шелла",         []() { return std::make_unique<ShellSorter<T>>(); }},
    };

    auto it = sorterMap.find(sortType);
    if (it != sorterMap.end()) {
        return it->second();
    }
    return nullptr;
}

SortUI::SortUI(QWidget *parent) : QMainWindow(parent), intData(nullptr), studentData(nullptr) {
    setupUI();
}

SortUI::~SortUI() {
    delete intData;
    delete studentData;
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

    dataTypeComboBox = new QComboBox(this);
    dataTypeComboBox->addItems({"Целые числа", "Студенты"});
    layout->addWidget(new QLabel("Тип данных:", this));
    layout->addWidget(dataTypeComboBox);

    minValueSpinBox = new QSpinBox(this);
    minValueSpinBox->setRange(-1000000, 0);
    minValueSpinBox->setValue(-100);

    maxValueSpinBox = new QSpinBox(this);
    maxValueSpinBox->setRange(1, 1000000);
    maxValueSpinBox->setValue(100);

    layout->addWidget(new QLabel("Минимальное значение для целых чисел:", this));
    layout->addWidget(minValueSpinBox);
    layout->addWidget(new QLabel("Максимальное значение для целых чисел:", this));
    layout->addWidget(maxValueSpinBox);

    sortByComboBox = new QComboBox(this);
    sortByComboBox->addItems({"Возраст", "Курс", "Средний балл"});
    layout->addWidget(new QLabel("Сортировать студентов по:", this));
    layout->addWidget(sortByComboBox);

    manualInputLineEdit = new QLineEdit(this);
    layout->addWidget(new QLabel("Ручной ввод целых чисел:", this));
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
    QString selectedDataType = dataTypeComboBox->currentText();
    dataTable->setRowCount(size);
    if (selectedDataType == "Целые числа") {
        int minValue = minValueSpinBox->value();
        int maxValue = maxValueSpinBox->value();
        delete intData;
        intData = new DynamicArray<int>(size);

        for (int i = 0; i < size; ++i) {
            int number = generateRandomNumber(minValue, maxValue);
            intData->set(i, number);
            dataTable->setItem(i, 0, new QTableWidgetItem(QString::number(number)));
        }

    } else if (selectedDataType == "Студенты") {
        delete studentData;
        studentData = new DynamicArray<Student>(size);

        for (int i = 0; i < size; ++i) {
            Student student = generateStudent();
            studentData->set(i, student);
            addStudentToTable(i, 0, student);
        }
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
    QString selectedDataType = dataTypeComboBox->currentText();

    if (selectedDataType == "Целые числа") {
        QVector<int> values;
        while (!in.atEnd()) {
            bool ok;
            int value = in.readLine().toInt(&ok);
            if (ok) {
                values.append(value);
            }
        }
        file.close();

        delete intData;
        intData = new DynamicArray<int>(values.size());
        dataTable->setRowCount(values.size());

        for (int i = 0; i < values.size(); ++i) {
            intData->set(i, values[i]);
            dataTable->setItem(i, 0, new QTableWidgetItem(QString::number(values[i])));
        }
    } else if (selectedDataType == "Студенты") {
        QVector<Student> students;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(" ");
            if (parts.size() == 5) {
                Student student(
                        parts[0].trimmed().toStdString(),
                        parts[1].trimmed().toStdString(),
                        parts[2].toInt(),
                        parts[3].toInt(),
                        parts[4].toDouble()
                );
                students.append(student);
            }
        }
        file.close();

        delete studentData;
        studentData = new DynamicArray<Student>(students.size());
        dataTable->setRowCount(students.size());

        for (int i = 0; i < students.size(); ++i) {
            studentData->set(i, students[i]);
            addStudentToTable(i, 0 , students[i]);
        }
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

    delete intData;
    intData = new DynamicArray<int>(values.size());
    dataTable->setRowCount(values.size());

    for (int i = 0; i < values.size(); ++i) {
        intData->set(i, values[i]);
        dataTable->setItem(i, 0, new QTableWidgetItem(QString::number(values[i])));
    }
    QMessageBox::information(this, "Данные обработаны", "Данные успешно введены.");
}

void SortUI::onSortButtonClicked() {
    QString selectedSort = sortTypeComboBox->currentText();
    QString selectedDataType = dataTypeComboBox->currentText();

    auto start = std::chrono::high_resolution_clock::now();

    if (selectedDataType == "Целые числа") {
        if (!intData || intData->getSize() == 0) {
            QMessageBox::warning(this, "Ошибка", "Данные для сортировки отсутствуют.");
            return;
        }
        auto sorter = getSorter<int>(selectedSort);
        if (!sorter) {
            QMessageBox::warning(this, "Ошибка", "Выбранный метод сортировки не поддерживается.");
            return;
        }
        sorter->sort(intData->begin(), intData->end(), [](const int &a, const int &b) { return a < b; });
        for (int i = 0; i < intData->getSize(); ++i) {
            dataTable->setItem(i, 1, new QTableWidgetItem(QString::number((*intData)[i])));
        }

    } else if (selectedDataType == "Студенты") {
        if (!studentData || studentData->getSize() == 0) {
            QMessageBox::warning(this, "Ошибка", "Данные для сортировки отсутствуют.");
            return;
        }
        auto sorter = getSorter<Student>(selectedSort);
        if (!sorter) {
            QMessageBox::warning(this, "Ошибка", "Выбранный метод сортировки не поддерживается.");
            return;
        }
        std::function<bool(const Student &, const Student &)> comp;
        QString selectedSortBy = sortByComboBox->currentText();
        if (selectedSortBy == "Возраст") {
            comp = Student::compareByAge;
        } else if (selectedSortBy == "Курс") {
            comp = Student::compareByCourse;
        } else if (selectedSortBy == "Средний балл") {
            comp = Student::compareByAverageScore;
        } else {
            QMessageBox::warning(this, "Ошибка", "Выбранное поле для сортировки не поддерживается.");
            return;
        }
        sorter->sort(studentData->begin(), studentData->end(), comp);
        for (int i = 0; i < studentData->getSize(); ++i) {
            addStudentToTable(i, 1, (*studentData)[i]);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
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
    QString selectedDataType = dataTypeComboBox->currentText();

    if (selectedDataType == "Целые числа" && intData) {
        for (int i = 0; i < intData->getSize(); ++i) {
            out << (*intData)[i] << '\n';
        }
    } else if (selectedDataType == "Студенты" && studentData) {
        for (int i = 0; i < studentData->getSize(); ++i) {
            const Student &student = (*studentData)[i];
            out << QString::fromStdString(student.getName()) << " "
                << QString::fromStdString(student.getSurname()) << " "
                << student.getAge() << " "
                << student.getCourse() << " "
                << student.getAverageScore() << '\n';
        }
    }

    file.close();
    QMessageBox::information(this, "Сохранение завершено", "Данные успешно сохранены.");
}

void SortUI::addStudentToTable(int row, int column, const Student &student) {
    QString studentInfo = QString::fromStdString(student.getName()) + " " +
                          QString::fromStdString(student.getSurname()) + "  " +
                          QString::number(student.getCourse()) + "  " +
                          QString::number(student.getAge()) + "  " +
                          QString::number(student.getAverageScore(), 'f', 2);
    dataTable->setItem(row, column, new QTableWidgetItem(studentInfo));
}
