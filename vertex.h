// Olga Kuriatnyk
// CSS 343
// Graph Project

#ifndef VERTEX_H
#define VERTEX_H

#include "edge.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

class Edge;

class Vertex {
    friend class Edge;
    friend class Graph;

public:
    // constructor, empty vertex
    Vertex();

    // copy constructor
    Vertex(const Vertex& vrtx);

    // constructor, given label
    explicit Vertex(const string &l);

    // destructor, revome all edges in the vector of edges
    ~Vertex();

    // move not allowed
    Vertex(Vertex && other) = delete;

    // assignment not allowed
    Vertex &operator=(const Vertex &other) = delete;

    // move assignment not allowed
    Vertex &operator=(Vertex &&other) = delete;

    // if such edge exists return true
    bool findEdge(Vertex* vTo);

    // add new edge to the vector of edges
    // return true if added
    bool addNewEdge(Edge* newEdge);

private:
    // objects for vertex 
    vector<Edge *> edges;
    string label;
};

#endif