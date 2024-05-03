#include "UnionFind.h"

#include <iostream>
#include <sstream>

using namespace std;

UnionFind::UnionFind(vector<Node*> nodes) {
    for (auto n: nodes) {
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

bool UnionFind::Union(Node* n1, Node* n2) {
    Node* p1 = Find_Parent(n1);
    Node* p2 = Find_Parent(n2);
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
    
    cout << n1->getData() << " parent = " << p1->getData() << endl;
    cout << "rank = " << rank_[p1] << endl;
    cout << n2->getData() << " parent = " << p2->getData() << endl;
    cout << "rank = " << rank_[p2] << endl;
    return true;
}


