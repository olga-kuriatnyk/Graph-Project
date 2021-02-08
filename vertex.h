#ifndef VERTEX_H
#define VERTEX_H

#include "edge.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

class Edge;

class Vertex {
    friend class Edge;
    friend class Graph;

public:
    Vertex();
    Vertex(const Vertex& vrtx);
    Vertex(const string &l);

    bool findEdge(Vertex* vTo);
    string findMin(map<string, int>& q);
private:
    vector<Edge *> edges;
    string label;

};

#endif