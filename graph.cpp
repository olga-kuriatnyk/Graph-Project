#include "graph.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <climits>
#include <utility>
#include <vector>

using namespace std;

// TODO:
// constructor, empty graph
// directionalEdges defaults to true
Graph::Graph(bool directionalEdges) {}

// TODO:
// destructor
Graph::~Graph() {}

// TODO: test->done
// @return total number of vertices
int Graph::verticesSize() const {
	return graph.size();
}

// TODO: test->done
// @return total number of edges
int Graph::edgesSize() const {
  int result = 0;
	for (auto itr = graph.begin(); itr != graph.end(); ++itr) {
		result += itr->second->edges.size();
	}
	return result;
}

// TODO:test->done
// @return number of edges from given vertex, -1 if vertex not found
int Graph::vertexDegree(const string &label) const {
  if (graph.find(label) != graph.end()) {
		return graph.find(label)->second->edges.size();
	}
	return -1;
}

// TODO: test->done
// @return true if vertex added, false if it already is in the graph
bool Graph::add(const string &label) {
	if (this->contains(label)) {
		return false;
	}
	Vertex *v = new Vertex(label);
	graph.insert({ label, v });
	return true;
}

// TODO: test->done
/** return true if vertex already in graph */
bool Graph::contains(const string &label) const {
	if (graph.find(label) != graph.end()) {
		return true;
	}
	return false;
}

// TODO: test->done
// @return string representing edges and weights, "" if vertex not found
// A-3->B, A-5->C should return B(3),C(5)
string Graph::getEdgesAsString(const string &label) const {
  string result = "";
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
map<string, int> Graph::getEdgesHelper(const string& label) const {
	Vertex* vrtx = graph.find(label)->second;
	map<string, int> result;
	for (int i = 0; i < vrtx->edges.size(); i++) {
		string l = vrtx->edges[i]->to->label;
		int w = vrtx->edges[i]->weight;
		result.insert({ l, w });
	}
	return result;
}

// TODO: test for non-directional
// @return true if successfully connected
// Add an edge between two vertices, create new vertices if necessary
// A vertex cannot connect to itself, cannot have P->P
// For digraphs (directed graphs), only one directed edge allowed, P->Q
// Undirected graphs must have P->Q and Q->P with same weight
bool Graph::connect(const string &from, const string &to, int weight) {
	if (from == to) {
		return false;
	}
	if (graph.find(from) == graph.end()) {
		add(from);
	} 
  if (graph.find(to) == graph.end()) {
		add(to);
	}
	// directional graph
	Vertex* vFrom = graph.find(from)->second;
	Vertex* vTo = graph.find(to)->second;
	if (dirEdges == true) {
		if (vFrom->findEdge(vTo)) {
			return false;
		}
		Edge* newEdge = new Edge(vFrom, vTo, weight);
		if (vFrom->edges.size() == 0) {
			vFrom->edges.push_back(newEdge);
			return true;
		}
		for (int i = 0; i < vFrom->edges.size(); i++) {
			auto it = vFrom->edges.begin();
			it++;
			if (newEdge->to->label < vFrom->edges.at(i)->to->label) {
				vFrom->edges.insert(vFrom->edges.begin(), newEdge);
				return true;
			}
			if ((i + 1) != vFrom->edges.size() && newEdge->to->label < vFrom->edges.at(i+1)->to->label) {
				
				vFrom->edges.insert(it, newEdge);
				return true;
			} else {
				vFrom->edges.push_back(newEdge);
				return true;
			}
		}
	}
}

// TODO: test for non-directional
// @return true if edge successfully deleted
bool Graph::disconnect(const string &from, const string &to) {
	// check if both vertexes exist
	if (graph.find(from) == graph.end() || graph.find(to) == graph.end()) {
		return false;
	}
	// check if the edge exists 
	Vertex* vFrom = graph.find(from)->second;
	Vertex* vTo = graph.find(to)->second;
	if (dirEdges == true) {
		for (int i = 0; i < vFrom->edges.size(); i++) {
			if (vFrom->edges[i]->from->label == from && vFrom->edges[i]->to->label == to) {
				vFrom->edges.erase(vFrom->edges.begin() + i);
				return true;
			}
		}
		return false;
	}	else {
		for (int i = 0; i < vFrom->edges.size(); i++) {
			if (vFrom->edges[i]->from->label == from && vFrom->edges[i]->to->label == to) {
				vFrom->edges.erase(vFrom->edges.begin() + i);
			}
			else if (vTo->edges[i]->to->label == to && vTo->edges[i]->from->label == from) {
				vTo->edges.erase(vTo->edges.begin() + i);
			}
			return true;
		}
		return false;
	}
}

// TODO: test
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
		Vertex* v = graph.find(s)->second;
		for (auto it = v->edges.rbegin(); it != v->edges.rend(); it++) {
			if (visited.find((*it)->to->label) == visited.end()) {
				stack.push((*it)->to->label);
				visited.insert((*it)->to->label);
			}
		}
	}
}

// TODO: test
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
		Vertex* v = graph.find(s)->second;
		for (auto it = v->edges.begin(); it != v->edges.end(); it++) {
			if (visited.find((*it)->to->label) == visited.end()) {
				queue.push((*it)->to->label);
				visited.insert((*it)->to->label);
			}
		}
	}
}

// TODO:
// NOTE: if using Adjacency list - unconnected vertices are not represented
// store the weights in a map
// store the previous label in a map
pair<map<string, int>, map<string, string>>
Graph::dijkstra(const string &startLabel) const {
  map<string, int> weights;
  map<string, string> previous;
if (graph.find(startLabel) == graph.end()) {
	return make_pair(weights, previous);
}
Vertex* v = graph.find(startLabel)->second;
map<string, int > q;
weights[startLabel] = 0;
q[startLabel] = 0;
for (auto it = v->edges.begin(); it != v->edges.end(); it++) {
	weights[(*it)->to->label] = INT_MAX;
	q[(*it)->to->label] = INT_MAX;
}
while (!q.empty()) {
	string sMin = v->findMin(q);
	v = graph.find(sMin)->second;
	for (int i = 0; i < v->edges.size(); i++) {
		Vertex* neighbour = v->edges[i]->to;
		if (!neighbour->edges.empty()) {
			for (int i = 0; i < neighbour->edges.size(); i++) {
				if (weights.find(neighbour->edges[i]->to->label) == weights.end()) {
					weights[neighbour->edges[i]->to->label] = INT_MAX; 
					q[neighbour->edges[i]->to->label] = INT_MAX;
				}
			}
		}
		int newWeight = weights.find(v->label)->second + v->edges[i]->weight;
		int oldWeight = weights.find(neighbour->label)->second;
		if (newWeight < oldWeight) {
			weights[neighbour->label] = newWeight;
			previous[neighbour->label] = v->label;
			q[neighbour->label] = newWeight;
		}
	}
}
weights.erase(startLabel);
return make_pair(weights, previous);
}

// TODO:
// minimum spanning tree using Prim's algorithm
int Graph::mstPrim(const string &startLabel,
                   void visit(const string &from, const string &to,
                              int weight)) const {
  return -1;
}

// TODO:
// minimum spanning tree using Prim's algorithm
int Graph::mstKruskal(const string &startLabel,
                      void visit(const string &from, const string &to,
                                 int weight)) const {
  return -1;
}

// TODO:test?
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
