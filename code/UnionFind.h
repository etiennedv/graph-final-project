#ifndef UNIONFIND_H__
#define UNIONFIND_H__

#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

class UnionFind {    
public:
    unordered_map<Node*, Node*> parent_;
    unordered_map<Node*, int> rank_;

    UnionFind(vector<Node*> nodes); 
    ~UnionFind();
    Node* Find_Parent(Node* node);
    bool Union(Node* n1, Node* n2);
    Node* getParent(Node* node);
    
};
 
#endif