// Graph Project
// Graph.cpp
#include "graph.h"
#include <algorithm>
#include <climits>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

// constructor, empty graph
// directionalEdges defaults to true
Graph::Graph(bool directionalEdges) {
  graph = {};
  dirEdges = directionalEdges;
}

// destructor
Graph::~Graph() {
  auto itr = graph.begin();
  while (!graph.empty()) {
    delete (*itr).second;
    graph.erase((*itr).first);
    itr = graph.begin();
  }
}

// @return total number of vertices
int Graph::verticesSize() const { return graph.size(); }

// @return total number of edges
int Graph::edgesSize() const {
  int result = 0;
  for (const auto &itr : graph) {
    result += itr.second->edges.size();
  }
  return result;
}

// @return number of edges from given vertex, -1 if vertex not found
int Graph::vertexDegree(const string &label) const {
  if (graph.find(label) != graph.end()) {
    return graph.find(label)->second->edges.size();
  }
  return -1;
}

// @return true if vertex added, false if it already is in the graph
bool Graph::add(const string &label) {
  if (this->contains(label)) {
    return false;
  }
  auto *v = new Vertex(label);
  graph.insert({label, v});
  return true;
}

/** return true if vertex already in graph */
bool Graph::contains(const string &label) const {
  return graph.find(label) != graph.end();
}

// @return string representing edges and weights, "" if vertex not found
// A-3->B, A-5->C should return B(3),C(5)
string Graph::getEdgesAsString(const string &label) const {
  string result;
  if (graph.find(label) != graph.end()) {
    map<string, int> map = getEdgesHelper(label);
    int i = 0;
    for (auto it : map) {
      result += it.first;
      result += "(";
      result += to_string(it.second);
      result += ")";
      i++;
      if (i < map.size()) {
        result += ",";
      }
    }
  }
  return result;
}

// takes a label and returns the map<string,int>
// were string is the label of vertex to and int is the weight
map<string, int> Graph::getEdgesHelper(const string &label) const {
  Vertex *vrtx = graph.find(label)->second;
  map<string, int> result;
  for (auto &edge : vrtx->edges) {
    string l = edge->to->label;
    int w = edge->weight;
    result.insert({l, w});
  }
  return result;
}

// @return true if successfully connected
// Add an edge between two vertices, create new vertices if necessary
// A vertex cannot connect to itself, cannot have P->P
// For digraphs (directed graphs), only one directed edge allowed, P->Q
// Undirected graphs must have P->Q and Q->P with same weight
bool Graph::connect(const string &from, const string &to, int weight) {
  bool result = false;
  if (from == to) {
    return result;
  }
  if (graph.find(from) == graph.end()) {
    add(from);
  }
  if (graph.find(to) == graph.end()) {
    add(to);
  }
  // directional graph
  Vertex *vFrom = graph.find(from)->second;
  Vertex *vTo = graph.find(to)->second;
  if (dirEdges) {
    if (vFrom->findEdge(vTo)) {
      return result;
    }
    auto newEdge = new Edge(vFrom, vTo, weight);
    return result = vFrom->addNewEdge(newEdge);
  }
  // non-directional
  if (vFrom->findEdge(vTo) && vTo->findEdge(vFrom)) {
    return result;
  }
  if (!vFrom->findEdge(vTo)) {
    auto newEdge = new Edge(vFrom, vTo, weight);
    result = vFrom->addNewEdge(newEdge);
  }
  if (!vTo->findEdge(vFrom)) {
    auto newEdge = new Edge(vTo, vFrom, weight);
    result = vTo->addNewEdge(newEdge);
  }
  return result;
}

// @return true if edge successfully deleted
bool Graph::disconnect(const string &from, const string &to) {
  // check if both vertexes exist
  if (graph.find(from) == graph.end() || graph.find(to) == graph.end()) {
    return false;
  }
  // check if the edge exists
  Vertex *vFrom = graph.find(from)->second;
  Vertex *vTo = graph.find(to)->second;
  if (dirEdges) {
    for (int i = 0; i < vFrom->edges.size(); i++) {
      if (vFrom->edges[i]->from->label == from &&
          vFrom->edges[i]->to->label == to) {
        delete vFrom->edges[i];
        vFrom->edges.erase(vFrom->edges.begin() + i);
        return true;
      }
    }
    return false;
  }
  for (int i = 0; i < vFrom->edges.size(); i++) {
    if (vFrom->edges[i]->from->label == from &&
        vFrom->edges[i]->to->label == to) {
      delete vFrom->edges[i];
      vFrom->edges.erase(vFrom->edges.begin() + i);
    } else if (vTo->edges[i]->to->label == to &&
               vTo->edges[i]->from->label == from) {
      delete vFrom->edges[i];
      vTo->edges.erase(vTo->edges.begin() + i);
    }
    return true;
  }
  return false;
}

// depth-first traversal starting from given startLabel
void Graph::dfs(const string &startLabel, void visit(const string &label)) {
  if (graph.find(startLabel) == graph.end()) {
    return;
  }
  stack<string> stack;
  stack.push(startLabel);
  set<string> visited;
  visited.insert(startLabel);
  while (!stack.empty()) {
    string s = stack.top();
    stack.pop();
    visit(s);
    Vertex *v = graph.find(s)->second;
    for (auto it = v->edges.rbegin(); it != v->edges.rend(); it++) {
      if (visited.find((*it)->to->label) == visited.end()) {
        stack.push((*it)->to->label);
        visited.insert((*it)->to->label);
      }
    }
  }
}

// breadth-first traversal starting from startLabel
void Graph::bfs(const string &startLabel, void visit(const string &label)) {
  if (graph.find(startLabel) == graph.end()) {
    return;
  }
  queue<string> queue;
  queue.push(startLabel);
  set<string> visited;
  visited.insert(startLabel);
  while (!queue.empty()) {
    string s = queue.front();
    queue.pop();
    visit(s);
    Vertex *v = graph.find(s)->second;
    for (auto &edge : v->edges) {
      if (visited.find(edge->to->label) == visited.end()) {
        queue.push(edge->to->label);
        visited.insert(edge->to->label);
      }
    }
  }
}

// NOTE: using Adjacency list - unconnected vertices are not represented
// store the weights in a map
// store the previous label in a map
pair<map<string, int>, map<string, string>>
Graph::dijkstra(const string &startLabel) const {
  map<string, int> weights;
  map<string, string> previous;
  if (graph.find(startLabel) == graph.end()) {
    return make_pair(weights, previous);
  }
  Vertex *v = graph.find(startLabel)->second;
  using IV = pair<int, Vertex *>;
  priority_queue<IV, vector<IV>, greater<IV>> q;
  set<string> set;
  q.push({0, v});
  weights[startLabel] = 0;
  for (auto &edge : v->edges) {
    weights[edge->to->label] = INT_MAX;
    q.push({INT_MAX, edge->to});
  }
  while (!q.empty()) {
    IV curr = q.top(); // take the vertex with smales weight
    q.pop();
    Vertex *currV = curr.second;
    for (int i = 0; i < currV->edges.size(); i++) {
      Vertex *neighbour = currV->edges[i]->to;
      if (!neighbour->edges.empty()) {
        for (auto &edge : neighbour->edges) {
          if (weights.find(edge->to->label) == weights.end()) {
            weights[edge->to->label] = INT_MAX;
            q.push({INT_MAX, edge->to});
          }
        }
      }
      int newWeight =
          weights.find(currV->label)->second + currV->edges[i]->weight;
      int oldWeight = weights.find(neighbour->label)->second;
      if (newWeight < oldWeight) {
        weights[neighbour->label] = newWeight;
        previous[neighbour->label] = currV->label;
        q.push({newWeight, neighbour});
      }
    }
  }
  weights.erase(startLabel);
  return make_pair(weights, previous);
}

// minimum spanning tree using Prim's algorithm
int Graph::mstPrim() const {
  if (graph.empty()) {
    return -1;
  }
  int result = 0;
  using IE = pair<int, Edge *>;
  priority_queue<IE, vector<IE>, greater<IE>> q;
  set<string> set;
  Vertex *v = graph.begin()->second;
  for (auto &edge : v->edges) {
    q.push({edge->weight, edge});
  }
  while (!q.empty()) {
    IE curr = q.top();
    q.pop();
    int currW = curr.first;
    Edge *currE = curr.second;
    string currEdgeFromLabel = currE->from->label;
    string currEdgeToLabel = currE->to->label;
    set.insert(currEdgeFromLabel);
    if (set.find(currEdgeToLabel) == set.end()) {
      set.insert(currEdgeToLabel);
      result += currW;
      for (auto &edge : graph.find(currEdgeToLabel)->second->edges) {
        if (set.find(edge->to->label) == set.end()) {
          q.push({edge->weight, edge});
        }
      }
    }
  }
  return result;
}

// read a text file and create the graph
bool Graph::readFile(const string &filename) {
  ifstream myfile(filename);
  if (!myfile.is_open()) {
    cerr << "Failed to open " << filename << endl;
    return false;
  }
  int edges = 0;
  int weight = 0;
  string fromVertex;
  string toVertex;
  myfile >> edges;
  for (int i = 0; i < edges; ++i) {
    myfile >> fromVertex >> toVertex >> weight;
    connect(fromVertex, toVertex, weight);
  }
  myfile.close();
  return true;
}
