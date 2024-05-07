// If you change anything in this file, your changes will be ignored
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <cmath>
#include <ctime>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <math.h>
#include <string>
#include <cstdlib>

// in order to access private members, we have to defeat the safety
// mechanisms. This is acceptable for unit testing, but not much
// else. It is also not portable because it is not supported by the
// C++ spec, and therefore might not work with all compilers.
#define private public
#include "../code/Edge.h"
#include "../code/Graph.h"
#include "../code/Node.h"
#include "../code/UnionFind.h"

using namespace std;

class test_Graph : public ::testing::Test {
protected:
  // This function runs only once before any TEST_F function
  static void SetUpTestCase() {
    std::ofstream outgrade("./total_grade.txt");
    if (outgrade.is_open()) {
      outgrade.clear();
      outgrade << (int)0;
      outgrade.close();
    }
  }

  // This function runs after all TEST_F functions have been executed
  static void TearDownTestCase() {
    std::ofstream outgrade("./total_grade.txt");
    if (outgrade.is_open()) {
      outgrade.clear();
      outgrade << (int)std::ceil(100 * total_grade / max_grade);
      outgrade.close();
      std::cout << "Total Grade is : "
                << (int)std::ceil(100 * total_grade / max_grade) << std::endl;
    }
  }

  void add_points_to_grade(double points) {
    if (!::testing::Test::HasFailure()) {
      total_grade += points;
    }
  }

  // this function runs before every TEST_F function
  void SetUp() override {}

  // this function runs after every TEST_F function
  void TearDown() override {
    std::ofstream outgrade("./total_grade.txt");
    if (outgrade.is_open()) {
      outgrade.clear();
      outgrade << (int)std::ceil(100 * total_grade / max_grade);
      outgrade.close();
    }
  }

  static double total_grade;
  static double max_grade;
};

double test_Graph::total_grade = 0;
double test_Graph::max_grade = 144;

// forward declaration of helpers. read and learn from them!
Graph* buildGraphToClear();
Graph* mkgraph();
Graph* mkgraph_test();
Graph* mkgraph_test2();
Graph* mkgraph_test3();
Graph* mkgraph_test4();
Node* find(Graph* graph, string label);

// Unit Tests

TEST_F(test_Graph, Graph_UnionFind) {
  Graph* graph = mkgraph_test();
  vector<Edge*> edges = graph->getEdges();
  vector<Node*> nodes = graph->getNodes();
  int N = 10;
  for (auto e: edges) {
    e->setWeight((rand() % N) + 1);
    cout << "Weight: " << e->getWeight() << endl;
  }
  graph->tick("Start");
  Graph* min_tree = graph->mst_kruskal();
  min_tree->tick("Done");
  cout << "MST span = " << min_tree->getSpan() << endl;
  graph->find_path(find(min_tree, "j"), find(min_tree, "i"));
}

TEST_F(test_Graph, Graph_UnionFindSmallGraph) {
  Graph* graph = mkgraph_test2();
  vector<Edge*> edges = graph->getEdges();

  graph->tick("Start");
  Graph* min_tree = graph->mst_kruskal();
  min_tree->tick("Done");

}

TEST_F(test_Graph, Graph_UnionFindTest3) {
  Graph* graph = mkgraph_test3();
  graph->tick("Start");
  Graph* min_tree = graph->mst_kruskal();
  min_tree->tick("Done");

  cout << "MST span = " << min_tree->getSpan() << endl;
  ASSERT_EQ(min_tree->getSpan(), 9);

  vector<Node*> nodes = min_tree->getNodes();
}

TEST_F(test_Graph, Graph_FindPath) {
  Graph* graph = mkgraph_test2();
  graph->tick("Start");
  vector<Node*> nodes = graph->getNodes();
  Node* start = nodes[0];
  Node* finish = nodes[nodes.size() - 1];
  graph->find_path(start, finish);
}

TEST_F(test_Graph, Graph_UnionFindBasic) {
  Graph* graph = mkgraph_test2();
  graph->tick("Start");
  Graph* mst = graph->mst_kruskal();
  mst->tick("End");
}

TEST_F(test_Graph, Graph_buildGraph) {
  Graph* graph(new Graph());
  graph->buildGraph(10, 20);
  vector<Node*> nodes = graph->getNodes();
  for (auto n: nodes) {
    cout << "Node: " << n->getData() << endl;
  }
  graph->tick("Finish");
  Graph* min_tree = graph->mst_kruskal();
  min_tree->tick("Min Tree");
  graph->tick("MST original Graph");
}
// ---------------------------------------------------------------- Helpers ---

Graph* buildGraphToClear() {
  // make a Graph with wonky metadata. it is intended test clear().
  Graph* g(new Graph());
  g->clock = 42;

  Node* a(new Node("a"));
  a->color = GRAY;
  a->discovery_time = 1;
  a->completion_time = 4;
  a->rank = 0;
  Node* b(new Node("b"));
  b->color = BLACK;
  b->discovery_time = 2;
  b->completion_time = 5;
  b->rank = 1;
  Node* c(new Node("c"));
  c->color = WHITE;
  c->discovery_time = 3;
  c->completion_time = 6;
  c->rank = -1;

  Edge* ab(new Edge(a, b));
  ab->type = TREE_EDGE;
  Edge* bc(new Edge(b, c));
  bc->type = CROSS_EDGE;
  Edge* ac(new Edge(a, c));
  bc->type = BACK_EDGE;

  a->predecessor = NULL;
  b->predecessor = a;
  c->predecessor = b;

  g->addNode(a);
  g->addNode(b);
  g->addNode(c);
  g->addEdge(ab);
  g->addEdge(bc);
  g->addEdge(ac);

  return g;
}
Graph* mkgraph_test() {
  Graph* ret(new Graph());
  Node* a(new Node("a"));
  Node* b(new Node("b"));
  Node* c(new Node("c"));
  Node* d(new Node("d"));
  Node* e(new Node("e"));
  Node* f(new Node("f"));
  Node* g(new Node("g"));
  Node* h(new Node("h"));
  Node* i(new Node("i"));
  Node* j(new Node("j"));
  Node* k(new Node("k"));
 

  Edge* ab(new Edge(a, b));
  Edge* ac(new Edge(a, c));
  Edge* bc(new Edge(b, c));
  Edge* ae(new Edge(a, e));
  Edge* ce(new Edge(c, e));
  Edge* cd(new Edge(c, d));
  Edge* dg(new Edge(d, g));
  Edge* eg(new Edge(e, g));
  Edge* df(new Edge(d, f));
  Edge* fb(new Edge(f, b));

  Edge* fh(new Edge(f, h));
  Edge* ha(new Edge(h, a));
  Edge* hi(new Edge(h, i));
  Edge* kf(new Edge(k, f));
  Edge* jk(new Edge(j, k));
  Edge* jb(new Edge(j, b));
  Edge* gh(new Edge(g, h));


  ret->addNode(a);
  ret->addNode(b);
  ret->addNode(c);
  ret->addNode(d);
  ret->addNode(e);
  ret->addNode(f);
  ret->addNode(g);
  ret->addNode(h);
  ret->addNode(i);
  ret->addNode(j);
  ret->addNode(k);


  ret->addEdge(ab);
  ret->addEdge(ac);
  ret->addEdge(bc);
  ret->addEdge(ae);
  ret->addEdge(ce);
  ret->addEdge(cd);
  ret->addEdge(dg);
  ret->addEdge(eg);
  ret->addEdge(df);
  ret->addEdge(fb);

  ret->addEdge(fh);
  ret->addEdge(ha);
  ret->addEdge(hi);
  ret->addEdge(kf);
  ret->addEdge(jk);
  ret->addEdge(jb);
  ret->addEdge(gh);

  return ret;
}
Graph* mkgraph_test2() {
  Graph* ret(new Graph());
  Node* a(new Node("a"));
  Node* b(new Node("b"));
  Node* c(new Node("c"));
  Node* d(new Node("d"));
  Node* e(new Node("e"));

  Edge* ab(new Edge(a, b));
  Edge* ac(new Edge(a, c));
  Edge* bc(new Edge(b, c));
  Edge* cd(new Edge(c, d));
  Edge* bd(new Edge(b, d));
  Edge* de(new Edge(d, e));
  Edge* ec(new Edge(e, c));
  Edge* ad(new Edge(a, d));

  ret->addNode(a);
  ret->addNode(b);
  ret->addNode(c);
  ret->addNode(d);
  ret->addNode(e);

  ret->addEdge(ab);
  ret->addEdge(ac);
  ret->addEdge(bc);
  ret->addEdge(ad);
  ret->addEdge(cd);
  ret->addEdge(bd);
  ret->addEdge(de);
  ret->addEdge(ec);

  ab->setWeight(10);
  ac->setWeight(8);
  bc->setWeight(4);
  bd->setWeight(4);
  cd->setWeight(4);
  ad->setWeight(4);
  de->setWeight(2);
  ec->setWeight(1);

  return ret;
}

Graph* mkgraph_test3() {
  Graph* ret(new Graph());
  Node* a(new Node("a"));
  Node* b(new Node("b"));
  Node* c(new Node("c"));
  Node* d(new Node("d"));
  Node* e(new Node("e"));
  Node* f(new Node("f"));

  Edge* ab(new Edge(a, b));
  ab->setWeight(1);
  Edge* bc(new Edge(b, c));
  bc->setWeight(6);
  Edge* ad(new Edge(a, d));
  ad->setWeight(3);
  Edge* bd(new Edge(b, d));
  bd->setWeight(5);
  Edge* de(new Edge(d, e));
  de->setWeight(1);
  Edge* be(new Edge(b, e));
  be->setWeight(1);
  Edge* ce(new Edge(c, e));
  ce->setWeight(5);
  Edge* ef(new Edge(e, f));
  ef->setWeight(4);
  Edge* cf(new Edge(c, f));
  cf->setWeight(2);

  ret->addNode(a);
  ret->addNode(b);
  ret->addNode(c);
  ret->addNode(d);
  ret->addNode(e);
  ret->addNode(f);

  ret->addEdge(ab);
  ret->addEdge(ad);
  ret->addEdge(bc);
  ret->addEdge(bd);
  ret->addEdge(de);
  ret->addEdge(be);
  ret->addEdge(ce);
  ret->addEdge(ef);
  ret->addEdge(cf);

  return ret;
}
Graph* mkgraph() {
  Graph* ret(new Graph());
  Node* a(new Node("a"));
  Node* b(new Node("b"));
  Node* c(new Node("c"));
  Node* d(new Node("d"));
  Node* e(new Node("e"));
  Node* f(new Node("f"));
  Node* g(new Node("g"));

  Edge* ab(new Edge(a, b));
  Edge* ac(new Edge(a, c));
  Edge* bc(new Edge(b, c));
  Edge* ae(new Edge(a, e));
  Edge* ce(new Edge(c, e));
  Edge* cd(new Edge(c, d));
  Edge* dg(new Edge(d, g));
  Edge* eg(new Edge(e, g));
  Edge* df(new Edge(d, f));
  Edge* fb(new Edge(f, b));
  // if graph is undirected, these could cause trouble. see that it doesn't
  Edge* gd(new Edge(g, d));
  Edge* ge(new Edge(g, e));

  ret->addNode(a);
  ret->addNode(b);
  ret->addNode(c);
  ret->addNode(d);
  ret->addNode(e);
  ret->addNode(f);
  ret->addNode(g);

  ret->addEdge(ab);
  ret->addEdge(ac);
  ret->addEdge(bc);
  ret->addEdge(ae);
  ret->addEdge(ce);
  ret->addEdge(cd);
  ret->addEdge(dg);
  ret->addEdge(eg);
  ret->addEdge(df);
  ret->addEdge(fb);
  ret->addEdge(gd);
  ret->addEdge(ge);

  ret->setDirected(true);

  return ret;
}

Node* find(Graph* graph, string label) {
  for (auto it = graph->nodes.begin(); it != graph->nodes.end(); ++it) {
    Node* n = *it;
    if (n->data == label) {
      return n;
    }
  }
  return NULL;
}
