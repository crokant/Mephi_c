#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Edge.h"

template<typename T>
class Edge;

template<typename T>
class Vertex {
private:
    std::string name;
    T data;
    std::string color;

    std::vector<std::shared_ptr<Edge<T>>> inputEdges;
    std::vector<std::shared_ptr<Edge<T>>> outputEdges;

public:
    explicit Vertex(const std::string &name, T data = T())
            : name(name), data(std::move(data)), color("gray") {}

    [[nodiscard]] const std::string &getName() const {
        return name;
    }

    void setName(const std::string &newName) {
        name = newName;
    }

    T getData() const {
        return data;
    }

    void setData(const T &newData) {
        data = newData;
    }

    [[nodiscard]] const std::string &getColor() const {
        return color;
    }

    void setColor(const std::string &newColor) {
        color = newColor;
    }

    void addInputEdge(std::shared_ptr<Edge<T>> edge) {
        inputEdges.push_back(edge);
    }

    void addOutputEdge(std::shared_ptr<Edge<T>> edge) {
        outputEdges.push_back(edge);
    }

    const std::vector<std::shared_ptr<Edge<T>>> &getInputEdges() const {
        return inputEdges;
    }

    const std::vector<std::shared_ptr<Edge<T>>> &getOutputEdges() const {
        return outputEdges;
    }

    [[nodiscard]] bool hasNeighbor(const std::string &neighborName) const {
        for (const auto &edge: inputEdges) {
            if (auto source = edge->getSource(); source && source->getName() == neighborName) {
                return true;
            }
        }
        for (const auto &edge: outputEdges) {
            if (auto destination = edge->getDestination(); destination && destination->getName() == neighborName) {
                return true;
            }
        }
        return false;
    }

    std::vector<std::shared_ptr<Vertex<T>>> getNeighbors() const {
        std::vector<std::shared_ptr<Vertex<T>>> neighbors;

        for (const auto &edge: inputEdges) {
            if (auto source = edge->getSource(); source) {
                neighbors.push_back(source);
            }
        }
        for (const auto &edge: outputEdges) {
            if (auto destination = edge->getDestination(); destination) {
                neighbors.push_back(destination);
            }
        }
        return neighbors;
    }
};