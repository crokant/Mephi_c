#include <memory>
#include <iostream>
#include "../Edge.h"
#include "tests.h"

void testEdge_getEndpoints() {
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    auto endpoints = edge->getEndpoints();
    check(endpoints.first->getName() == "A");
    check(endpoints.second->getName() == "B");
}

void testEdge_setSource() {
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    auto vertexC = std::make_shared<Vertex<int>>("C", 30);
    edge->setSource(vertexC);

    check(edge->getSource()->getName() == "C");
}

void testEdge_setDestination() {
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    auto vertexC = std::make_shared<Vertex<int>>("C", 30);
    edge->setDestination(vertexC);

    check(edge->getDestination()->getName() == "C");
}

void testEdge_toString() {
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    check(edge->toString() == "A -- B");
}

void testEdge_getSource() {
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    check(edge->getSource()->getName() == "A");
}

void testEdge_getDestination() {
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    check(edge->getDestination()->getName() == "B");
}

void runEdgeTests() {
    testEdge_getEndpoints();
    testEdge_setSource();
    testEdge_setDestination();
    testEdge_toString();
    testEdge_getSource();
    testEdge_getDestination();
    std::cout << "Edge tests passed!" << std::endl;
}