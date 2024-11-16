#include "SortUI.h"
#include "tests.h"
#include <QApplication>


int main(int argc, char *argv[]) {
    test();

    QApplication app(argc, argv);
    SortUI mainWindow;
    mainWindow.setWindowTitle("Сортировщик данных");
    mainWindow.show();
    return app.exec();
}

