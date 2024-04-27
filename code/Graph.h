
#ifndef GRAPH_H__
#define GRAPH_H__

#include "Edge.h"
#include "Node.h"
#include "UnionFind.h"
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph {
public:
  // The first block of public members are implemented for you.
  Graph();
  ~Graph();
  vector<Node*> getNodes();
  vector<Edge*> getEdges();
  int getSize();
  int getClock();
  void addNode(Node* n);
  void addEdge(Edge* e);
  void removeNode(Node* n);
  void removeEdge(Edge* e);
  bool isDirected();
  void setDirected(bool val);
  set<Edge*> getAdjacentEdges(Node* n);
  friend std::ostream& operator<<(std::ostream& out, Graph graph);

  // clear resets all nodes to have WHITE color, with -1 discovery and finish
  // times and rank. Resets all edges to type UNDISCOVERED_EDGE. It resets the
  // graph clock to 0.
  void clear();

  // tick is an OPTIONAL debugging method. Use this after incrementing the
  // clock. You might pass in a string to describe what just happened. If you
  // are having trouble, consider using this function as a place to track your
  // algorithm's progress. Print out your graph on each tick. If you want to get
  // very fancy, you can output your graph in 'dot' format. This is the same
  // format we used in the B-Tree assignment for debugging.
  //
  // This function is 100% optional, though.
  void tick(string message);

  // dfs(start) runs a depth-first search from the indicated start node, and
  // explores all reachable nodes. This ignores unreachable nodes. When this
  // function returns, all explored nodes are colored BLACK, all unreachable
  // nodes are WHITE. All explored nodes have correct discovery/exit time
  // information. All edges have correct edge types (unfollowed edges should
  // remain UNDISCOVERED).
  //
  // For a DFS, mark nodes GRAY when we first discover them, and BLACK when we
  // exit (finish) them.
  void dfs(Node*);

  // bfs(start) runs a breadth-first search starting from the given node. It
  // sets the 'rank' value on all nodes to something appropriate: -1 for
  // unreachable nodes, 0 for the start node, 1 for nodes that are one edge from
  // the start node, and so forth.
  //
  // For a BFS, mark nodes GRAY when they are enqueued, and BLACK when they are
  // dequeued.
  void bfs(Node* start);

  // bfs(start, target) has the same requirements as the other version of `bfs`,
  // except this one stops after the target node is reached. If found, the
  // target node is marked BLACK, and its rank should be correctly set on exit.
  // If it is not found, the target node should remain WHITE with a rank of -1.
  void bfs(Node* start, Node* target);

  vector<Node*> get_neighbors(Node* node);
  Graph* mst_kruskal();
  Graph* mkgraph();
  Graph* mkgraph_test();
  Graph* mkgraph_test2();
private:
  bool directed;
  vector<Node*> nodes;
  vector<Edge*> edges;
  // The next two vectors may be used in your search algorithms.
  vector<Edge*> search_edges;
  vector<Node*> search_nodes;
  // The clock is used to set discovery/finish times. Increment it by one every
  // time a Node color changes to GRAY or BLACK.
  int clock;
};

#endif // GRAPH_H__