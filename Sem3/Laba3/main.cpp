#include <QApplication>
#include "TictactoeUI.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    TictactoeUI tictactoeWindow;
    tictactoeWindow.show();

    return app.exec();
}
