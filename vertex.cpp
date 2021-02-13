// Olga Kuriatnyk
// CSS 343
// Graph Project

#include "vertex.h"
#include <string>
#include <vector>

using namespace std;

// constructor, empty vertex
Vertex::Vertex() = default;

// copy constructor
Vertex::Vertex(const Vertex &vrtx) {
  this->label = vrtx.label;
  this->edges = vrtx.edges;
}

// constructor, given label
Vertex::Vertex(const string &l) {
  this->label = l;
  this->edges = {};
}

// destructor
Vertex::~Vertex() {
  auto itr = edges.begin();
  while (!edges.empty()) {
    delete *itr;
    edges.erase(itr);
    itr = edges.begin();
  }
}

// if such edge exists return true
bool Vertex::findEdge(Vertex *vTo) {
  auto e = new Edge(this, vTo, 0);
  for (auto &edge : edges) {
    if (edge->from == e->from && edge->to == e->to) {
      delete e;
      return true;
    }
  }
  delete e;
  return false;
}

// add new edge to the vector of edges
// return true if added
bool Vertex::addNewEdge(Edge *newEdge) {
  if (this->edges.empty()) {
    this->edges.push_back(newEdge);
    return true;
  }
  for (int i = 0; i < this->edges.size(); i++) {
    auto it = this->edges.begin();
    it++;
    if (newEdge->to->label < this->edges.at(i)->to->label) {
      this->edges.insert(this->edges.begin(), newEdge);
      return true;
    }
    if ((i + 1) != this->edges.size() &&
        newEdge->to->label < this->edges.at(i + 1)->to->label) {
      this->edges.insert(it, newEdge);
      return true;
    }
    this->edges.push_back(newEdge);
    return true;
  }
  return false;
}