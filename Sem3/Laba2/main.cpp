#include "SortUi.h"
#include <QApplication>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SortUI mainWindow;
    mainWindow.setWindowTitle("Сортировщик данных");
    mainWindow.show();

    return app.exec();
}