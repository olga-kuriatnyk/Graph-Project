#include "edge.h"

using namespace std;

Edge::Edge() {
    from = {};
    to = {};
    weight = 0;
}

Edge::Edge(Vertex* vFrom, Vertex* vTo)
{
    this->from = vFrom;
    this->to = vTo;
    this->weight = 0;
}

Edge::Edge(Vertex *vFrom, Vertex *vTo, int wght) {
    this->from = vFrom;
    this->to = vTo;
    this->weight = wght;
}