#include "Node.h"

Node::Node(string s) {
  // DONE FOR YOU
  data = s;
  rank = 1;
}

Node::~Node() {
  // "DONE" FOR YOU
  //
  // This is equivalent to the default destructor the compiler will
  // generate for you. As a rule of thumb, you only need to `delete`
  // member variables that were created with `new` inside this
  // class. So, you don't need to do anything here. It could have been
  // left out of the header/impl file entirely.
}

string Node::getData() {
  // DONE FOR YOU
  return data;
}

void Node::setRank(int r) {
  // DONE FOR YOU
  rank = r;
}

void Node::clear() {
  // TODO
  color = WHITE;
  discovery_time = -1;
  completion_time = -1;
  rank = 0;
  predecessor = NULL;
}

void Node::setColor(int search_color, int time) {
  // TODO
  color = search_color;
  if (search_color == GRAY) {
    discovery_time = time;
  }
  else if (search_color == BLACK) {
    completion_time = time;
  }
  else {
    clear();
  }
}

void Node::getDiscoveryInformation(int& thecolor, int& disco_time,
                                   int& finish_time, int& bfs_rank) {
  // TODO
  thecolor = color;
  disco_time = discovery_time;
  finish_time = completion_time;
  bfs_rank = rank;
}

bool Node::isAncestor(Node* other) {
  // TODO
  Node* cursor = this->predecessor;
  while (cursor != NULL) {
    if (cursor == other) {
      return true;
    }
    cursor = cursor->predecessor;
  }
  return false;
}

void Node::setPredecessor(Node* other) {
  // TODO
  this->predecessor = other;
}

Node* Node::getPredecessor() {
  return predecessor;
}

int Node::getColor() {
  return color;
}

int Node::getRank() {
  return rank;
}

void Node::add_neighbor(Node* n) {
  this->neighbors.push_back(n);
}

vector<Node*> Node::get_neighbors() {
  return neighbors;
}

// overloading operator << lets you put a Node object into an output
// stream.
ostream& operator<<(std::ostream& out, Node node) {
  // DONE FOR YOU
  out << node.data;
  return out;
}
