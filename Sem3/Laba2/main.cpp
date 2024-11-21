#include "SortUI.h"
#include "tests.h"
#include "Student.h"
#include <QApplication>


int main(int argc, char *argv[]) {
    runTests<int>();
    runTests<Student>();
    runTests<int>(true);

    QApplication app(argc, argv);
    SortUI mainWindow;
    mainWindow.setWindowTitle("Сортировщик данных");
    mainWindow.show();
    return app.exec();
}

