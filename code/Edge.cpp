
#include "Edge.h"

Edge::Edge(Node* n1, Node* n2) {
  // DONE FOR YOU
  a = n1;
  b = n2;
}

Edge::~Edge() {
  // "DONE" FOR YOU
}

Node* Edge::getStart() {
  // DONE FOR YOU
  return a;
}

Node* Edge::getEnd() {
  // DONE FOR YOU
  return b;
}

int Edge::getType() {
  // DONE FOR YOU
  return type;
}

void Edge::setType(int edge_type) {
  // TODO
  type = edge_type;
}

// overloading operator << lets you put an Edge object into an output stream.
ostream& operator<<(std::ostream& out, Edge edge) {
  // DONE FOR YOU
  out << *edge.a << " -- " << *edge.b;
  return out;
}

int Edge::getWeight() {
  return weight;
}

void Edge::setWeight(int val) {
  weight = val;
}