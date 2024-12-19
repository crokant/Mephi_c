#include <memory>
#include "../Graph.h"
#include "tests.h"

void check(bool condition) {
    if (!condition) {
        throw std::runtime_error("tests failed");
    }
}

void testGraph_addVertex() {
    Graph<int> graph;
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    graph.addVertex(vertexA);

    check(graph.getVertices().size() == 1);
    check(graph.getVertexByName("A") == vertexA);
}

void testGraph_addEdge() {
    Graph<int> graph;
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    graph.addVertex(vertexA);
    graph.addVertex(vertexB);
    graph.addEdge(vertexA, vertexB, edge);

    check(graph.getEdges().size() == 1);
    check(graph.getEdgeByVertices(vertexA, vertexB) == edge);
}

void testGraph_addEdgeByName() {
    Graph<int> graph;
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    graph.addVertex(vertexA);
    graph.addVertex(vertexB);
    graph.addEdgeByName("A", "B", edge);

    check(graph.getEdges().size() == 1);
    check(graph.getEdgeByVertices(vertexA, vertexB) == edge);
}

void testGraph_removeVertex() {
    Graph<int> graph;
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    graph.addVertex(vertexA);
    graph.addVertex(vertexB);
    graph.addEdge(vertexA, vertexB, edge);

    graph.removeVertex("A");

    check(graph.getVertices().size() == 1);
    check(graph.getEdges().size() == 0);
}

void testGraph_generateGraph() {
    Graph<int> graph = Graph<int>::generateGraph(5, 0.5);

    check(graph.getVertices().size() == 5);
    check(graph.getEdges().size() > 0);
}

void testGraph_colorGraph() {
    Graph<int> graph = Graph<int>::generateGraph(5, 0.5);
    graph.colorGraph();

    const auto& vertices = graph.getVertices();
    check(vertices.size() == 5);
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        const std::string& vertexName = it.key();
        const std::shared_ptr<Vertex<int>>& vertex = it.value();

        check(vertex->getColor() != "gray");
    }
}

void testGraph_getEdges() {
    Graph<int> graph;
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    graph.addVertex(vertexA);
    graph.addVertex(vertexB);
    graph.addEdge(vertexA, vertexB, edge);

    check(graph.getEdges().size() == 1);
}

void testGraph_getVertices() {
    Graph<int> graph;
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);

    graph.addVertex(vertexA);
    graph.addVertex(vertexB);

    check(graph.getVertices().size() == 2);
}

void testGraph_getVertexByName() {
    Graph<int> graph;
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    graph.addVertex(vertexA);

    check(graph.getVertexByName("A") == vertexA);
    check(graph.getVertexByName("B") == nullptr);
}

void testGraph_getEdgeByVertices() {
    Graph<int> graph;
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    graph.addVertex(vertexA);
    graph.addVertex(vertexB);
    graph.addEdge(vertexA, vertexB, edge);

    check(graph.getEdgeByVertices(vertexA, vertexB) == edge);
    check(graph.getEdgeByVertices(vertexB, vertexA) == nullptr);
}

void testGraph_getGraphString() {
    Graph<int> graph;
    auto vertexA = std::make_shared<Vertex<int>>("A", 10);
    auto vertexB = std::make_shared<Vertex<int>>("B", 20);
    auto edge = std::make_shared<Edge<int>>(vertexA, vertexB);

    graph.addVertex(vertexA);
    graph.addVertex(vertexB);
    graph.addEdge(vertexA, vertexB, edge);

    std::string graphString = graph.getGraphString(true);
    check(graphString.find("A -> B") != std::string::npos);
}

void runGraphTests() {
    testGraph_addVertex();
    testGraph_addEdge();
    testGraph_addEdgeByName();
    testGraph_removeVertex();
    testGraph_generateGraph();
    testGraph_colorGraph();
    testGraph_getEdges();
    testGraph_getVertices();
    testGraph_getVertexByName();
    testGraph_getEdgeByVertices();
    testGraph_getGraphString();
    std::cout << "Graph tests passed!" << std::endl;
}