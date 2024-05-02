#include "Graph.h"

#include <iostream>
#include <sstream>

using namespace std;
using std::cout;

// fwd declarations
string make_dot(Graph* g);
string what(int& v);

Graph::Graph() {
  // DONE FOR YOU
  directed = false; // graphs are undirected by default
}

Graph::~Graph() {
  // "DONE" FOR YOU
  // no implementation needed
}

vector<Node*> Graph::getNodes() {
  // DONE FOR YOU
  return nodes;
}

vector<Edge*> Graph::getEdges() {
  // DONE FOR YOU
  return edges;
}

int Graph::getSize() {
  return this->getNodes().size();
  
}
int Graph::getClock() {
  // DONE FOR YOU
  return clock;
}

void Graph::addNode(Node* n) {
  // DONE FOR YOU
  nodes.push_back(n);
}

void Graph::addEdge(Edge* e) {
  // DONE FOR YOU
  edges.push_back(e);
}

void Graph::removeNode(Node* n) {
  // DONE FOR YOU
  for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    if (n == *it) {
      nodes.erase(it);
      break;
    }
  }
}

void Graph::removeEdge(Edge* e) {
  // DONE FOR YOU
  for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    if (e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  // DONE FOR YOU
  directed = val;
}

bool Graph::isDirected() {
  // DONE FOR YOU
  return directed;
}

set<Edge*> Graph::getAdjacentEdges(Node* n) {
  // DONE FOR YOU
  set<Edge*> ret;
  for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    Edge* edge = *it;
    if (edge->getStart() == n) {
      ret.insert(edge);
    }
    if (!directed && (edge->getEnd() == n)) {
      ret.insert(edge);
    }
  }
  return ret;
}

void Graph::clear() {
  // TODO
  for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    Node* node = *it;
    node->clear();
  }
  for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    Edge* edge = *it;
    edge->setType(UNDISCOVERED_EDGE);
  }
  clock = 0;
}

void Graph::tick(string message) {
  // DONE FOR YOU
  //
  // optional debugging function, disabled with if(false) to prevent
  // unused var warning. Change this however you want.
  //
  // recommended use: call it just after incrementing the clock.
  if (true) {
    cout << "// " << message << endl << make_dot(this) << endl;
  }
}

void Graph::dfs(Node* start) {
  // TODO
  // mark node gray
  start->setColor(GRAY, getClock());
  clock++;
  search_nodes.push_back(start);
  
  set<Edge*> node_edges = getAdjacentEdges(start);
  
  for (set<Edge*>::iterator it = node_edges.begin(); it != node_edges.end(); it++) {
    Edge* a = *it;
    Node* cursor = a->getEnd();
    if (cursor->getColor() == 1) {
      cursor->setPredecessor(start);
      a->setType(10);
      dfs(cursor);
    }
    else if (cursor->getColor() == 2) {
      a->setType(11);
    }
    else if (cursor->getColor() == 3 && cursor->isAncestor(start)) {
      a->setType(12);
    }
    else {
      a->setType(13);
    }
  }
  start->setColor(BLACK, getClock());
  clock++; 
}

void Graph::bfs(Node* start) {
  // TODO
  Node* finish = NULL;
  bfs(start, finish);
}

void Graph::bfs(Node* start, Node* finish) {
  // TODO
  // mark start gray
  start->setColor(GRAY, getClock());
  clock++;
  queue<Node*> node_q;
  node_q.push(start);
  start->setRank(0);
  while (node_q.size() > 0) {
    Node* curr = node_q.front();
    node_q.pop();
    
    curr->setColor(BLACK, getClock());
    clock++;

    if (curr == finish) {
      if (!isDirected()) {
        curr->setRank(1);
      }
      
      break;
    }
    //vector<Node*> neighbors = get_neighbors(curr);

    for (auto n : curr->get_neighbors()) {
      if (n->getColor() == 1) {
        n->setRank(curr->getRank() + 1);
        n->setColor(GRAY, getClock());
        n->setPredecessor(curr);
        clock++;
        node_q.push(n);
      }
    }
  }
}

vector<Edge*> Graph::adj_edges(Node* node) {
  vector<Edge*> neighbors;
  for (auto e: this->getEdges()) {
    if (e->getStart() == node || e->getEnd() == node) {
      neighbors.push_back(e);
    }
  }
  return neighbors;
}

void Graph::add_neighbors(Node* node) {
  vector<Edge*> edges = getEdges();
  //vector<Node*> neighbors;
  for (auto e: edges) {
    if (e->getStart() == node) {
      e->getEnd()->setPredecessor(node);
      //neighbors.push_back(e->getEnd());
      node->add_neighbor(e->getEnd());
    }
  }
  //return neighbors;
}

void Graph::set_neighbors() {
  vector<Node*> nodes = this->getNodes();
  for (auto n: nodes) {
    add_neighbors(n);
  }
}
// overloading operator << lets you put a Graph object into an output
// stream.
ostream& operator<<(ostream& out, Graph graph) {
  // DONE FOR YOU
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (vector<Node*>::iterator it = graph.nodes.begin();
       it != graph.nodes.end(); it++) {
    Node* n = *it;
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (vector<Edge*>::iterator it = graph.edges.begin();
       it != graph.edges.end(); it++) {
    Edge* e = *it;
    out << *e << ", ";
  }
  out << "]";
  return out;
}

// what is a helper function that turns a constant (e.g. WHITE or
// FORWARD_EDGE) into a string for debugging goodness.
string what(int& v) {
  // DONE FOR YOU
  string ret = "Unknown";
  if (v == WHITE) {
    ret = "white";
  } else if (v == GRAY) {
    ret = "gray";
  } else if (v == BLACK) {
    ret = "black";
  } else if (v == UNDISCOVERED_EDGE) {
    ret = "undiscovered";
  } else if (v == TREE_EDGE) {
    ret = "tree";
  } else if (v == BACK_EDGE) {
    ret = "back";
  } else if (v == FORWARD_EDGE) {
    ret = "forward";
  } else if (v == CROSS_EDGE) {
    ret = "cross";
  }
  return ret;
}

// make_dot generates a dotfile string for viewing your graph. Have
// tick() print out the results of this function, and then use
// http://www.webgraphviz.com/ (or get a copy of GraphViz) to view the
// result. If you're stuck, this can help you get un-stuck.
string make_dot(Graph* g) {
  // DONE FOR YOU
  stringstream ss;
  vector<Node*> nodes = g->getNodes();
  vector<Edge*> edges = g->getEdges();
  string gt = "graph";
  string con = "--";
  if (g->isDirected()) {
    con = "->";
    gt = "digraph";
  }
  ss << gt << " weighted {" << endl;
  int c, dt, ft, r;
  string textColor = "black";
  for (auto it = nodes.begin(); it != nodes.end(); ++it) {
    Node* n = *it;
    n->getDiscoveryInformation(c, dt, ft, r);
    if (c == BLACK) {
      textColor = "white";
    } else {
      textColor = "black";
    }
    ss << "  " << n->getData() << " [ style=\"filled\" fontcolor=\""
       << textColor << "\" ]" << endl;
      // "\" fillcolor=\"" << what(c) << "\""
       //<< " ]" << endl;
  }

  string edgeColor = "black";
  for (auto it = edges.begin(); it != edges.end(); ++it) {
    Edge* e = *it;
    if (e->getType() == TREE_EDGE) {
      edgeColor = "black";
    } else if (e->getType() == FORWARD_EDGE) {
      edgeColor = "purple";
    } else if (e->getType() == BACK_EDGE) {
      edgeColor = "blue";
    } else if (e->getType() == CROSS_EDGE) {
      edgeColor = "green";
    } else {
      edgeColor = "gray";
    }
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData()
       << " [color=\"" << edgeColor << "\" weight=" << e->getWeight() << "]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}

Graph* Graph::mst_kruskal() {
    priority_queue <Edge, vector<Edge*>, myComparator> minHeap;
    vector<Edge*> edges = this->getEdges();
    vector<Node*> nodes = this->getNodes();
    int n = nodes.size();
    for (auto e: edges) {
        minHeap.push(e);
    }
    cout << "Pq size: " << minHeap.size() << endl;
    unordered_set<Node*> added;
    UnionFind unionFind(this->getNodes());
    Graph* mst(new Graph());
    int mst_edges = 0;
    while(mst_edges < n - 1) {
        Edge* minEdge = minHeap.top();
        cout << "Edge Weight: " << minEdge->getWeight() << endl;
        minHeap.pop();

        if (!unionFind.Union(minEdge)) {
          continue;
        }

        mst->addEdge(minEdge);
        mst_edges++;
        mst->addSpan(minEdge->getWeight());
        Node* n1 = minEdge->getStart();
        Node* n2 = minEdge->getEnd();
        
        if (added.count(n1) == 0) {
          mst->addNode(n1);
          added.insert(n1);
        }
        if (added.count(n2) == 0) {
          mst->addNode(n2);
          added.insert(n2);
        }
    }
    
    return mst;
}

// Prim's algorithm
Graph* Graph::mst_prim() {
  priority_queue <Edge, vector<Edge*>, myComparator> minHeap;
  //this->set_neighbors();
  vector<Node*> nodes = this->getNodes();
  Node* start = nodes[0];
  cout << start->getData();
  for (auto e: adj_edges(start)) {
    minHeap.push(e);
  }
  Graph* mst(new Graph());
  unordered_set<Node*> added;
  unordered_set<Edge*> added_edges;
  added.insert(start);
  mst->addNode(start);
  while (added.size() < this->getSize()) {
    Edge* minEdge = minHeap.top();
    Node* node1 = minEdge->getStart();
    Node* node2 = minEdge->getEnd();
    minHeap.pop();

    if (added.count(node2) > 0) {
      continue;
    }
    
    mst->addEdge(minEdge);
    added_edges.insert(minEdge);
    mst->addSpan(minEdge->getWeight());
    if (added.count(node1) == 0) {
      mst->addNode(node1);
      cout << node1->getData();
      added.insert(node1);
    }
    if (added.count(node2) == 0) {
      mst->addNode(node2);
      cout << node2->getData();
      added.insert(node2);
    }
    
    for (auto e: adj_edges(node2)) {
      if (added_edges.count(e) == 0) {
        minHeap.push(e);
      }
    }
  }

  return mst;
}

void Graph::find_path(Node* start, Node* finish) {
  vector<Node*> nodes = this->getNodes();
  set<Node*> path;
  deque<Node*> q;
  q.push_back(start);
  std::cout << "Path from " << start->getData() << " to " << finish->getData() << ":" << endl;
  
  while (q.size() > 0) {
    Node* curr = q.front();
    q.pop_front();
    if (path.count(curr) == 0) {
      path.insert(curr);
    }
    if (curr == finish) {
      for (auto node: path) {
        std::cout << node->getData();
      }
      cout << endl;
      return;
    }
    for (auto node: nodes) {
      if (path.count(node) == 0) {
        q.push_back(node);
      }
    }
  }
}

void Graph::addSpan(int weight) {
  span = span + weight;
}

int Graph::getSpan() {
  return span;
}