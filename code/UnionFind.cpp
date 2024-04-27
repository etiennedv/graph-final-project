#include "UnionFind.h"

#include <iostream>
#include <sstream>

using namespace std;

UnionFind::UnionFind(vector<Node*> nodes) {
    for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        Node* n = *it;
        parent_[n] = n;
        rank_[n] = 0;
    }    
}

UnionFind::~UnionFind(){
}

Node* UnionFind::Find_Parent(Node* node) {
    Node* p = parent_[node];
    while (p != parent_[node]) {
        parent_[p] = parent_[parent_[p]];
        p = parent_[p];
    }
    return p;  
}

bool UnionFind::Union(Edge* edge) {
    Node* p1 = Find_Parent(edge->getStart());
    Node* p2 = Find_Parent(edge->getEnd());
    if (p1 == p2) {
        return false;
    }

    if (rank_[p1] > rank_[p2]) {
        parent_[p2] = p1;
    } 
    else if (rank_[p1] < rank_[p2]) {
        parent_[p1] = p2;
    }
    else {
        parent_[p1] = p2;
        rank_[p2] += 1;
    }
    return true;
}

// Kruskal's Algorithm

