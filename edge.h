#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

using namespace std;

class Vertex;

class Edge {
    friend class Vertex;
    friend class Graph;

public:
    Edge();
    Edge(Vertex* vFrom, Vertex* vTo);
    Edge(Vertex *vFrom, Vertex *vTo, int wght);

private:
    Vertex *from;
    Vertex *to;
    int weight;
};

#endif