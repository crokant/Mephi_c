#include <memory>
#include <iostream>
#include "../Vertex.h"
#include "tests.h"

void testVertex_getName() {
    auto vertex = std::make_shared<Vertex<int>>("A", 10);
    check(vertex->getName() == "A");
}

void testVertex_setData() {
    auto vertex = std::make_shared<Vertex<int>>("A", 10);
    vertex->setData(20);
    check(vertex->getData() == 20);
}

void testVertex_getColor() {
    auto vertex = std::make_shared<Vertex<int>>("A", 10);
    check(vertex->getColor() == "gray");
}

void testVertex_setColor() {
    auto vertex = std::make_shared<Vertex<int>>("A", 10);
    vertex->setColor("red");
    check(vertex->getColor() == "red");
}

void testVertex_hasNeighbor() {
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    vertexA->addOutputEdge(edge);
    vertexB->addInputEdge(edge);

    check(vertexA->hasNeighbor("B"));
    check(!vertexA->hasNeighbor("C"));
}

void testVertex_getNeighbors() {
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto vertexC = std::make_shared<Vertex<int>>("C", 30);
    auto edgeAB = std::make_shared<Edge<int>>(vertexA, vertexB);
    auto edgeAC = std::make_shared<Edge<int>>(vertexA, vertexC);

    vertexA->addOutputEdge(edgeAB);
    vertexA->addOutputEdge(edgeAC);

    auto neighbors = vertexA->getNeighbors();
    check(neighbors.size() == 2);
    check(neighbors[0]->getName() == "B");
    check(neighbors[1]->getName() == "C");
}

void testVertex_setName() {
    auto vertex = std::make_shared<Vertex<int>>("A", 10);
    vertex->setName("B");
    check(vertex->getName() == "B");
}

void testVertex_addInputEdge() {
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    vertexB->addInputEdge(edge);
    check(vertexB->getInputEdges().size() == 1);
}

void testVertex_addOutputEdge() {
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    vertexA->addOutputEdge(edge);
    check(vertexA->getOutputEdges().size() == 1);
}

void testVertex_getInputEdges() {
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    vertexB->addInputEdge(edge);
    check(vertexB->getInputEdges().size() == 1);
    check(vertexB->getInputEdges()[0] == edge);
}

void testVertex_getOutputEdges() {
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    vertexA->addOutputEdge(edge);
    check(vertexA->getOutputEdges().size() == 1);
    check(vertexA->getOutputEdges()[0] == edge);
}

void runVertexTests() {
    testVertex_getName();
    testVertex_setData();
    testVertex_getColor();
    testVertex_setColor();
    testVertex_hasNeighbor();
    testVertex_getNeighbors();
    testVertex_setName();
    testVertex_addInputEdge();
    testVertex_addOutputEdge();
    testVertex_getInputEdges();
    testVertex_getOutputEdges();
    std::cout << "Vertex tests passed!" << std::endl;
}