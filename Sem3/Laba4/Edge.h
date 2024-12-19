#pragma once

#include "Vertex.h"
#include <memory>

template<typename T>
class Vertex;

template<typename T>
class Edge {
protected:
    std::shared_ptr<Vertex<T>> source;
    std::shared_ptr<Vertex<T>> destination;

public:
    Edge() = default;

    Edge(std::shared_ptr<Vertex<T>> source, std::shared_ptr<Vertex<T>> destination)
            : source(source), destination(destination) {}

    virtual ~Edge() = default;

    std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>> getEndpoints() const {
        return std::make_pair(source, destination);
    }

    void setSource(std::shared_ptr<Vertex<T>> newSource) {
        source = newSource;
    }

    std::shared_ptr<Vertex<T>> getSource() const {
        return source;
    }

    void setDestination(std::shared_ptr<Vertex<T>> newDestination) {
        destination = newDestination;
    }

    std::shared_ptr<Vertex<T>> getDestination() const {
        return destination;
    }

    virtual std::string toString() const {
        return source->getName() + " -- " + destination->getName();
    }
};
