#include "UnionFind.h"

#include <iostream>
#include <sstream>

using namespace std;

UnionFind::UnionFind(vector<Node*> nodes) {
    for (auto n: nodes) {
        parent_[n] = n;
        rank_[n] = 1;
    }    
}

UnionFind::~UnionFind(){
}

Node* UnionFind::Find_Parent(Node* node) {
    Node* p = parent_[node];
    //Node* p = node->getParent();
    while (p != parent_[p]) {
    //while (p != p->getParent()) {
        //p->setParent(p->getParent()->getParent());
        //node->setParent(p);
    //}
        parent_[p] = parent_[parent_[p]];
        p = parent_[p];
    }
    //node->setParent(p);
    return p;  
}

bool UnionFind::Union(Node* n1, Node* n2) {
    Node* p1 = Find_Parent(n1);
    Node* p2 = Find_Parent(n2);
    cout << "Before Find: " << endl;
    cout << n1->getData() << " parent = " << p1->getData() << endl;
    cout << "rank = " << rank_[p1] << endl;
    cout << n2->getData() << " parent = " << p2->getData() << endl;
    cout << "rank = " << rank_[p2] << endl;
    if (p1 == p2) {
        return false;
    }

    if (rank_[p1] > rank_[p2]) {
        parent_[p2] = p1;
        //n2->setParent(p1);
    } 
    else if (rank_[p1] < rank_[p2]) {
        parent_[p1] = p2;
        //n1->setParent(p2);
    }
    else {
        parent_[p1] = p2;
        //n2->setParent(n1->getParent());
        rank_[p2] += 1;
        //p2->setRank(p2->getRank() + 1);
    }
    cout << "After Find: " << endl;
    cout << n1->getData() << " parent = " << p1->getData() << endl;
    cout << "rank = " << rank_[p1] << endl;
    cout << n2->getData() << " parent = " << p2->getData() << endl;
    cout << "rank = " << rank_[p2] << endl;
    return true;
}

Node* UnionFind::getParent(Node* node) {
    return parent_[node];
}

