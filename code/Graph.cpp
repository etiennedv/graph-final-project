#include "Graph.h"

#include <iostream>
#include <sstream>
#include <utility>
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

void Graph::createNode(string name) {
  Node* node(new Node(name));
  this->addNode(node);
}

void Graph::createEdge(Node* n1, Node* n2) {
  Edge* edge(new Edge(n1, n2));
  edge->setWeight((rand() % 9) + 1);
  this->addEdge(edge);
}

void Graph::buildGraph(int num_nodes, int num_edges) {
  unordered_set<Edge*> edges;
  for (int i = 1; i < num_nodes + 1; i++) {
    createNode(to_string(i));
  }
  vector<Node*> nodes = this->getNodes();
  int edge_count = 0;
  while (edge_count < num_edges + 1) {
    int k = rand() % num_nodes;
    int l = rand() % num_nodes;
    
    createEdge(nodes[k], nodes[l]);
    edge_count++;
  }
    
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
    } else if (e->getType() == MIN_EDGE) {
      edgeColor = "red";
    } else {
      edgeColor = "gray";
    }
    string label = to_string(e->getWeight());
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData()
       << " [color=\"" << edgeColor <<  "\" weight=" << e->getWeight() << " label=" << label << " ]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}

// Kruskal's Algorithm for finding the minimum spanning tree (mst)
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
    UnionFind UnionFind(this->getNodes());
    Graph* mst(new Graph());
    int mst_edges = 0;
    while(mst->getEdges().size() < n - 1) {
        Edge* minEdge = minHeap.top();
        minHeap.pop();
        Node* n1 = minEdge->getStart();
        Node* n2 = minEdge->getEnd();
        cout << "Checking Edge: " << n1->getData() << "_" << n2->getData() << endl;
        if (!UnionFind.Union(n1, n2)) {
          cout << "Can't Union" << endl;
          continue;
        }

        mst->addEdge(minEdge);
        mst->addSpan(minEdge->getWeight());
        mst_edges++;
        minEdge->setType(14);
      
        string edge_label = minEdge->getStart()->getData() + minEdge->getEnd()->getData();
    
        if (added.count(n1) < 1) {
          mst->addNode(n1);
          added.insert(n1);
        }
        if (added.count(n2) < 1) {
          mst->addNode(n2);
          added.insert(n2);
        }
        //mst->tick(edge_label);
    }
    return mst;
}


void Graph::find_path(Node* start, Node* finish) {
  //vector<Node*> nodes = this->getNodes();
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
    else if (curr == finish) {
      for (auto node: path) {
        std::cout << node->getData();
      }
      cout << endl;
      return;
    }
    vector<Node*> nodes = curr->get_neighbors();
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