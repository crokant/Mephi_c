#include "GraphUI.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QMessageBox>
#include <QDebug>
#include <cmath>
#include <QIntValidator>
#include <QGroupBox>
#include <QFormLayout>

GraphUI::GraphUI(QWidget *parent) : QWidget(parent) {
    graph = new Graph<int>();
    auto *mainLayout = new QGridLayout(this);
    scene = new QGraphicsScene(this);
    auto *graphView = new QGraphicsView(scene);
    graphView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(graphView, 0, 0, 5, 1);

    auto *addVertexGroup = new QGroupBox("Add Vertex");
    auto *addVertexLayout = new QFormLayout();
    vertexNameEdit = new QLineEdit();
    addVertexLayout->addRow("Vertex Name:", vertexNameEdit);
    auto *addVertexButton = new QPushButton("Add Vertex");
    addVertexLayout->addWidget(addVertexButton);
    addVertexGroup->setLayout(addVertexLayout);
    mainLayout->addWidget(addVertexGroup, 0, 1);

    auto *addEdgeGroup = new QGroupBox("Add Edge");
    auto *addEdgeLayout = new QFormLayout();
    fromVertexEdit = new QLineEdit();
    toVertexEdit = new QLineEdit();
    addEdgeLayout->addRow("From:", fromVertexEdit);
    addEdgeLayout->addRow("To:", toVertexEdit);
    auto *addEdgeButton = new QPushButton("Add Edge");
    addEdgeLayout->addWidget(addEdgeButton);
    addEdgeGroup->setLayout(addEdgeLayout);
    mainLayout->addWidget(addEdgeGroup, 1, 1);

    auto *generateGraphGroup = new QGroupBox("Generate Graph");
    auto *generateGraphLayout = new QFormLayout();
    vertexCountEdit = new QLineEdit();
    vertexCountEdit->setPlaceholderText("5");
    vertexCountEdit->setValidator(new QIntValidator(1, 10, this));
    edgeProbabilityEdit = new QLineEdit();
    edgeProbabilityEdit->setPlaceholderText("0.5");
    edgeProbabilityEdit->setValidator(new QDoubleValidator(0.0, 1.0, 2, this));
    generateGraphLayout->addRow("Vertex Count:", vertexCountEdit);
    generateGraphLayout->addRow("Edge Probability:", edgeProbabilityEdit);
    generateGraphButton = new QPushButton("Generate Graph");
    generateGraphLayout->addWidget(generateGraphButton);
    generateGraphGroup->setLayout(generateGraphLayout);
    mainLayout->addWidget(generateGraphGroup, 2, 1);

    auto *removeVertexGroup = new QGroupBox("Remove Vertex");
    auto *removeVertexLayout = new QFormLayout();
    removeVertexEdit = new QLineEdit();
    removeVertexLayout->addRow("Vertex Name:", removeVertexEdit);
    removeVertexButton = new QPushButton("Remove Vertex");
    removeVertexLayout->addWidget(removeVertexButton);
    removeVertexGroup->setLayout(removeVertexLayout);
    mainLayout->addWidget(removeVertexGroup, 3, 1);

    colorGraphButton = new QPushButton("Color Graph");
    mainLayout->addWidget(colorGraphButton, 4, 1);

    connect(addVertexButton, &QPushButton::clicked, this, &GraphUI::addVertex);
    connect(addEdgeButton, &QPushButton::clicked, this, &GraphUI::addEdge);
    connect(generateGraphButton, &QPushButton::clicked, this, &GraphUI::generateGraph);
    connect(colorGraphButton, &QPushButton::clicked, this, &GraphUI::colorGraph);
    connect(removeVertexButton, &QPushButton::clicked, this, &GraphUI::removeVertex);
    setLayout(mainLayout);
    setStyleSheet(
            "QGroupBox { border: 1px solid gray; border-radius: 5px; margin-top: 10px; padding: 10px; }"
            "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }"
            "QLineEdit { padding: 5px; border: 1px solid gray; border-radius: 3px; }"
            "QPushButton { padding: 5px 10px; background-color: #4CAF50; color: white; border: none; border-radius: 3px; }"
            "QPushButton:hover { background-color: #45a049; }"
            "QCheckBox { spacing: 5px; }"
    );
}


void GraphUI::addVertex() {
    QString vertexName = vertexNameEdit->text();
    if (vertexName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Vertex name cannot be empty!");
        return;
    }

    if (vertexMap.contains(vertexName.toStdString())) {
        QMessageBox::warning(this, "Error", "Vertex with this name already exists!");
        return;
    }

    std::shared_ptr<Vertex<int>> vertex = std::make_shared<Vertex<int>>(vertexName.toStdString());
    graph->addVertex(vertex);
    QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 30, 30, QPen(Qt::darkGray), QBrush(Qt::gray));
    QGraphicsTextItem *text = scene->addText(vertexName);
    text->setPos(15, 15);

    node->setPos(scene->items().size() * 50, 50);
    text->setPos(node->pos().x() + 10, node->pos().y() + 10);

    vertexMap[vertexName.toStdString()] = node;
    layoutGraph();

    vertexNameEdit->clear();
}

void GraphUI::addEdge() {
    QString fromName = fromVertexEdit->text();
    QString toName = toVertexEdit->text();

    if (fromName.isEmpty() || toName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Both 'From' and 'To' fields must be filled!");
        return;
    }

    if (!vertexMap.contains(fromName.toStdString()) || !vertexMap.contains(toName.toStdString())) {
        QMessageBox::warning(this, "Error", "One or both vertices do not exist!");
        return;
    }

    std::shared_ptr<Vertex<int>> fromVertex = graph->getVertexByName(fromName.toStdString());
    std::shared_ptr<Vertex<int>> toVertex = graph->getVertexByName(toName.toStdString());

    if (!fromVertex || !toVertex) {
        QMessageBox::warning(this, "Error", "One or both vertices do not exist!");
        return;
    }

    std::shared_ptr<Edge<int>> edge = std::make_shared<Edge<int>>(fromVertex, toVertex);
    graph->addEdge(fromVertex, toVertex, edge);

    layoutGraph();
    fromVertexEdit->clear();
    toVertexEdit->clear();
}

void GraphUI::generateGraph() {
    int vertexCount = vertexCountEdit->text().toInt();
    double edgeProbability = edgeProbabilityEdit->text().toDouble();

    if (vertexCount <= 0 || edgeProbability < 0.0 || edgeProbability > 1.0) {
        QMessageBox::warning(this, "Error", "Invalid parameters for graph generation!");
        return;
    }

    *graph = Graph<int>::generateGraph(vertexCount, edgeProbability);

    vertexMap.clear();

    for (int i = 0; i < graph->getVertices().size(); ++i) {
        std::string vertexName;
        std::shared_ptr<Vertex<int>> vertex;
        if (graph->getVertices().findByIndex(i, vertexName, vertex)) {
            QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 30, 30, QPen(Qt::darkGray), QBrush(Qt::gray));
            QGraphicsTextItem *text = scene->addText(QString::fromStdString(vertexName));
            text->setPos(15, 15);
            vertexMap[vertexName] = node;
        }
    }

    layoutGraph();
}

void GraphUI::colorGraph() {
    graph->colorGraph();
    layoutGraph();
}

void GraphUI::removeVertex() {
    QString vertexName = removeVertexEdit->text();
    if (vertexName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Vertex name cannot be empty!");
        return;
    }
    if (!vertexMap.contains(vertexName.toStdString())) {
        QMessageBox::warning(this, "Error", "Vertex does not exist!");
        return;
    }
    graph->removeVertex(vertexName.toStdString());
    vertexMap.remove(vertexName.toStdString());
    layoutGraph();

    removeVertexEdit->clear();
}

void GraphUI::layoutGraph() {
    scene->clear();

    const int width = 600;
    const int height = 600;
    const int radius = std::min(width, height) / 2;
    const int centerX = width / 2;
    const int centerY = height / 2;

    int vertexCount = vertexMap.size();

    QMap<std::string, QPointF> positions;
    int index = 0;
    for (auto it = vertexMap.begin(); it != vertexMap.end(); ++it) {
        double angle = 2 * M_PI * index / vertexCount;
        double x = centerX + radius * std::cos(angle);
        double y = centerY + radius * std::sin(angle);
        positions[it.key()] = QPointF(x, y);
        ++index;
    }

    for (auto it = vertexMap.begin(); it != vertexMap.end(); ++it) {
        std::string vertexName = it.key();
        QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 30, 30, QPen(Qt::darkGray));
        std::shared_ptr<Vertex<int>> vertex = graph->getVertexByName(vertexName);
        if (vertex) {
            QString color = QString::fromStdString(vertex->getColor());
            node->setBrush(QBrush(QColor(color)));
        }

        node->setPos(positions[vertexName].x() - 15, positions[vertexName].y() - 15);
        QGraphicsTextItem *text = scene->addText(QString::fromStdString(vertexName));
        text->setPos(positions[vertexName].x() - 15, positions[vertexName].y() - 35);
    }

    for (auto it = graph->getEdges().begin(); it != graph->getEdges().end(); ++it) {
        std::string from = it.key().first;
        std::string to = it.key().second;
        QPointF fromPos = positions[from];
        QPointF toPos = positions[to];
        QGraphicsLineItem *line = scene->addLine(
                fromPos.x(), fromPos.y(),
                toPos.x(), toPos.y(),
                QPen(Qt::black)
        );
    }
}