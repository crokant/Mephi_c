#include <QApplication>
#include "GraphUI.h"
#include "tests/tests.h"

int main(int argc, char *argv[]) {
    runVertexTests();
    runEdgeTests();
    runGraphTests();
    QApplication app(argc, argv);

    GraphUI window;
    window.setWindowTitle("GraphUI");
    window.resize(1400, 700);
    window.show();

    return app.exec();
}
