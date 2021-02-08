#include "vertex.h"
#include <vector>
#include <string>
using namespace std;

Vertex::Vertex() {}

Vertex::Vertex(const Vertex& vrtx) {
	this->label = vrtx.label;
	this->edges = vrtx.edges;
}

Vertex::Vertex(const string &l) {
    this->label = l;
    this->edges = {};
}

bool Vertex::findEdge(Vertex* vTo) {
	Edge* e = new Edge(this, vTo);
	for (int i = 0; i < edges.size(); i++) {
		if (edges[i]->from == e->from && edges[i]->to == e->to) {
			//delete e;
			return true;
		}
	}
	//delete e;
	return false;
}

string Vertex::findMin(map<string, int>& q) {
	//auto it = q.begin();
	//string s = (*it).first;
	//int minVal = (*it).second;
	//it++;
	string s = q.begin()->first;
	int minVal = q.begin()->second;
	for (auto it = q.begin(); it != q.end(); it++) {
		if (minVal > (*it).second) {
			s = (*it).first;
			minVal = (*it).second;
		}
	}
	string result = s;
	q.erase(s);
	return result;
}