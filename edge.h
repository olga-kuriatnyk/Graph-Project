// Olga Kuriatnyk
// CSS 343
// Graph Project

#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

//using namespace std;

class Vertex;

class Edge {
    friend class Vertex;
    friend class Graph;

public:

    // constructor, empty edge
    Edge();

    // constructor
    Edge(Vertex *vFrom, Vertex *vTo, int wght);
    
    // destructor
    ~Edge();

    // copy constructor not allowed
    Edge(const Edge &edge) = delete;

    // move not allowed
    Edge(Edge && other) = delete;

    // assignment not allowed
    Edge &operator=(const Edge &other) = delete;

    // move assignment not allowed
    Edge &operator=(Edge &&other) = delete;

private:
    // objects for Edge
    Vertex *from;
    Vertex *to;
    int weight;
};

#endif