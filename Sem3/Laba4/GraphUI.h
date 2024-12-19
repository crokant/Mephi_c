#pragma once

#include <QWidget>
#include <QGraphicsScene>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include "Graph.h"

class GraphUI : public QWidget {
public:
    GraphUI(QWidget *parent = nullptr);

private slots:

    void addVertex();

    void addEdge();

    void generateGraph();

    void colorGraph();

    void removeVertex();

private:
    void layoutGraph();

    Graph<int> *graph;
    QGraphicsScene *scene;
    QLineEdit *vertexNameEdit;
    QLineEdit *fromVertexEdit;
    QLineEdit *toVertexEdit;
    QLineEdit *removeVertexEdit;
    QPushButton *generateGraphButton;
    QPushButton *colorGraphButton;

    QLineEdit *vertexCountEdit;
    QLineEdit *edgeProbabilityEdit;
    QPushButton *removeVertexButton;

    QMap<std::string, QGraphicsEllipseItem *> vertexMap;
};