// Olga Kuriatnyk
// CSS 343
// Graph Project

#include "edge.h"

using namespace std;

// constructor, empty edge
Edge::Edge() {
  this->from = {};
  this->to = {};
  weight = 0;
}

// constructor
Edge::Edge(Vertex *vFrom, Vertex *vTo, int wght) {
  this->from = vFrom;
  this->to = vTo;
  this->weight = wght;
}

// destructor
Edge::~Edge() = default;