#pragma once

#include "Vertex.h"
#include "Edge.h"
#include "../Laba3/UnorderedMap.h"
#include <vector>
#include <stdexcept>
#include <random>
#include <iostream>
#include <unordered_set>

namespace std {
    template<>
    struct hash<std::pair<std::string, std::string>> {
        size_t operator()(const std::pair<std::string, std::string> &pair) const {
            std::hash<std::string> hasher;
            return hasher(pair.first) ^ (hasher(pair.second) << 1);
        }
    };
}

template<typename T>
class Graph {
private:
    UnorderedMap<std::string, std::shared_ptr<Vertex<T>>> vertices;
    UnorderedMap<std::pair<std::string, std::string>, std::shared_ptr<Edge<T>>> edges;

public:
    Graph() : vertices(), edges() {}

    void addVertex(std::shared_ptr<Vertex<T>> vertex) {
        if (vertices.contains(vertex->getName())) return;
        vertices.insert(vertex->getName(), vertex);
    }

    void addEdge(std::shared_ptr<Vertex<T>> from, std::shared_ptr<Vertex<T>> to, std::shared_ptr<Edge<T>> edge) {
        edge->setSource(from);
        edge->setDestination(to);

        from->addOutputEdge(edge);
        to->addInputEdge(edge);

        auto vertexPair = std::make_pair(from->getName(), to->getName());
        edges.insert(vertexPair, edge);
    }

    void addEdgeByName(const std::string &fromName, const std::string &toName, std::shared_ptr<Edge<T>> edge) {
        auto from = getVertexByName(fromName);
        auto to = getVertexByName(toName);
        if (!from || !to || from->getName() == to->getName()) return;
        addEdge(from, to, edge);
    }

    const UnorderedMap<std::pair<std::string, std::string>, std::shared_ptr<Edge<T>>> &getEdges() const {
        return edges;
    }

    std::shared_ptr<Edge<T>>
    getEdgeByVertices(const std::shared_ptr<Vertex<T>> from, const std::shared_ptr<Vertex<T>> to) {
        auto vertexPair = std::make_pair(from->getName(), to->getName());
        std::shared_ptr<Edge<T>> edge;
        if (!edges.find(vertexPair, edge)) return nullptr;
        return edge;
    }

    const UnorderedMap<std::string, std::shared_ptr<Vertex<T>>> &getVertices() const {
        return vertices;
    }

    std::shared_ptr<Vertex<T>> getVertexByName(const std::string &name) {
        std::shared_ptr<Vertex<T>> vertex;
        if (!vertices.find(name, vertex)) return nullptr;
        return vertex;
    }

    std::string getGraphString(bool directed) {
        std::string infix = directed ? " -> " : " -- ";
        std::string result = directed ? "digraph G {\n" : "graph G {\n";
        result += "layout=\"sfdp\" beautify=true;\n";

        for (int i = 0; i < vertices.size(); ++i) {
            std::string vertexName;
            std::shared_ptr<Vertex<T>> vertex;
            if (vertices.findByIndex(i, vertexName, vertex)) {
                result += vertex->getName() + "[color=" + vertex->getColor() + "];\n";
            }
        }

        for (int i = 0; i < edges.size(); ++i) {
            std::pair<std::string, std::string> vertexPair;
            std::shared_ptr<Edge<T>> edge;
            if (edges.findByIndex(i, vertexPair, edge)) {
                result += vertexPair.first + infix + vertexPair.second + ";\n";
            }
        }

        result += "}\n";
        return result;
    }

    void removeVertex(const std::string &name) {
        if (!vertices.contains(name)) return;

        std::vector<std::pair<std::string, std::string>> edgesToRemove;
        for (int i = 0; i < edges.size(); ++i) {
            std::pair<std::string, std::string> vertexPair;
            std::shared_ptr<Edge<T>> edge;
            if (edges.findByIndex(i, vertexPair, edge)) {
                if (vertexPair.first == name || vertexPair.second == name) {
                    edgesToRemove.push_back(vertexPair);
                }
            }
        }

        for (const auto &pair: edgesToRemove) edges.erase(pair);
        vertices.erase(name);
    }

    static Graph<T> generateGraph(size_t vertexCount, double edgeProbability) {
        Graph<T> graph;
        std::string prefix = "V";
        std::random_device rd;
        std::mt19937 generator(rd());

        std::uniform_real_distribution<double> dist(0.0, 1.0);
        for (size_t i = 1; i <= vertexCount; ++i) {
            std::string name = prefix + std::to_string(i);
            std::shared_ptr<Vertex<T>> vertex = std::make_shared<Vertex<T>>(name);
            graph.addVertex(vertex);
        }
        for (size_t i = 1; i <= vertexCount; ++i) {
            auto fromVertex = graph.getVertexByName(prefix + std::to_string(i));
            for (size_t j = 1; j <= vertexCount; ++j) {
                if (i == j) continue;
                auto toVertex = graph.getVertexByName(prefix + std::to_string(j));
                if (dist(generator) < edgeProbability) {
                    auto edge = std::make_shared<Edge<T>>(fromVertex, toVertex);
                    graph.addEdgeByName(prefix + std::to_string(i), prefix + std::to_string(j), edge);

                }
            }
        }
        return graph;
    }

    void colorGraph() {
        const std::vector<std::string> colors = {
                "red", "blue", "green", "yellow", "orange", "purple", "cyan", "magenta", "lime", "pink",
                "teal", "brown", "gray", "olive", "navy", "maroon", "aqua", "silver", "gold", "indigo"
        };

        std::vector<std::shared_ptr<Vertex<T>>> vertexList;
        for (int i = 0; i < vertices.size(); ++i) {
            std::string vertexName;
            std::shared_ptr<Vertex<T>> vertex;
            if (vertices.findByIndex(i, vertexName, vertex)) {
                vertexList.push_back(vertex);
            }
        }
        std::sort(vertexList.begin(), vertexList.end(),
                  [](const std::shared_ptr<Vertex<T>> &a, const std::shared_ptr<Vertex<T>> &b) {
                      return a->getInputEdges().size() + a->getOutputEdges().size() >
                             b->getInputEdges().size() + b->getOutputEdges().size();
                  });

        int upperBound = 0;
        std::unordered_map<std::string, std::string> greedyColorAssignment;

        for (const auto &vertex: vertexList) {
            std::unordered_set<std::string> usedColors;
            for (const auto &neighbor: vertex->getNeighbors()) {
                if (greedyColorAssignment.find(neighbor->getName()) != greedyColorAssignment.end()) {
                    usedColors.insert(greedyColorAssignment[neighbor->getName()]);
                }
            }
            for (int colorIndex = 0; colorIndex < colors.size(); ++colorIndex) {
                const std::string &color = colors[colorIndex];
                if (usedColors.find(color) == usedColors.end()) {
                    greedyColorAssignment[vertex->getName()] = color;
                    upperBound = std::max(upperBound, colorIndex + 1);
                    break;
                }
            }
        }
        auto canColorGraph = [&](int numColors) -> bool {
            std::unordered_map<std::string, std::string> colorAssignment;

            std::function<bool(size_t)> colorVertex = [&](size_t vertexIndex) -> bool {
                if (vertexIndex == vertexList.size()) {
                    return true;
                }
                const auto &vertex = vertexList[vertexIndex];
                std::unordered_set<std::string> usedColors;
                for (const auto &neighbor: vertex->getNeighbors()) {
                    if (colorAssignment.find(neighbor->getName()) != colorAssignment.end()) {
                        usedColors.insert(colorAssignment[neighbor->getName()]);
                    }
                }
                for (int colorIndex = 0; colorIndex < numColors; ++colorIndex) {
                    const std::string &color = colors[colorIndex];
                    if (usedColors.find(color) == usedColors.end()) {
                        colorAssignment[vertex->getName()] = color;
                        if (colorVertex(vertexIndex + 1)) {
                            return true;
                        }
                        colorAssignment.erase(vertex->getName());
                    }
                }

                return false;
            };
            return colorVertex(0);
        };

        int minColors = upperBound;
        if (upperBound > 1 && canColorGraph(upperBound - 1)) {
            minColors = upperBound - 1;
        }
        std::unordered_map<std::string, std::string> bestColorAssignment;
        if (minColors == upperBound) {
            bestColorAssignment = greedyColorAssignment;
        } else {
            canColorGraph(minColors);
        }
        for (const auto &vertex: vertexList) {
            vertex->setColor(bestColorAssignment[vertex->getName()]);
        }
    }
};