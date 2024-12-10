#include <QApplication>
#include "TictactoeUI.h"
#include "tests/tests.h"

int main(int argc, char *argv[]) {
    runMapTests();
    runBoardTests();
    runBotTests();

    QApplication app(argc, argv);

    TictactoeUI tictactoeWindow;
    tictactoeWindow.show();

    return app.exec();
}
