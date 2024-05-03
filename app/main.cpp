#include <iostream>
#include "../code/Graph.h"
#include "../code/Node.h"
#include "../code/Edge.h"
#include "../code/UnionFind.h"

using namespace std;
Graph* mkgraph() {
  Graph* ret(new Graph());
  Node* ATL(new Node("ATL"));
  Node* DFW(new Node("DFW"));
  Node* DEN(new Node("DEN"));
  Node* LAX(new Node("LAX"));
  Node* JFK(new Node("JFK"));
  Node* ORD(new Node("ORD"));
  Node* LAS(new Node("LAS"));
  Node* MCO(new Node("MCO"));
  Node* MIA(new Node("MIA"));
  Node* CLT(new Node("CLT"));
  Node* SEA(new Node("SEA"));
  Node* PHX(new Node("PHX"));
  Node* EWR(new Node("EWR"));
  Node* FLL(new Node("FLL"));
 

  Edge* ATL_MCO(new Edge(ATL, MCO));
  ATL_MCO->setWeight(90);
  Edge* ATL_FLL(new Edge(ATL, FLL));
  ATL_FLL->setWeight(110);
  Edge* DFW_ATL(new Edge(DFW, ATL));
  DFW_ATL->setWeight(125);
  Edge* DFW_DEN(new Edge(DFW, DEN));
  DFW_DEN->setWeight(130);
  Edge* DEN_LAS(new Edge(DEN, LAS));
  DEN_LAS->setWeight(120);
  Edge* DEN_PHX(new Edge(DEN, PHX));
  DEN_PHX->setWeight(155);
  Edge* LAX_MCO(new Edge(LAX, MCO));
  LAX_MCO->setWeight(290);
  Edge* LAX_MIA(new Edge(LAX, MIA));
  LAX_MIA->setWeight(300);
  //Edge* JFK_LAX(new Edge(JFK, LAX));
  //JFK_LAX->setWeight(310);
  Edge* JFK_CLT(new Edge(JFK, CLT));
  JFK_CLT->setWeight(125);
  Edge* ORD_PHX(new Edge(ORD, PHX));
  ORD_PHX->setWeight(230);
  Edge* ORD_LAX(new Edge(ORD, LAX));
  ORD_LAX->setWeight(270);
  Edge* MCO_DEN(new Edge(MCO, DEN));
  MCO_DEN->setWeight(250);
  Edge* MIA_ORD(new Edge(MIA, ORD));
  MIA_ORD->setWeight(205);
  Edge* MIA_ATL(new Edge(MIA, ATL));
  MIA_ATL->setWeight(120);
  Edge* CLT_ATL(new Edge(CLT, ATL));
  CLT_ATL->setWeight(75);
  Edge* CLT_MCO(new Edge(CLT, MCO));
  CLT_MCO->setWeight(105);
  Edge* SEA_DFW(new Edge(SEA, DFW));
  SEA_DFW->setWeight(240);
  Edge* SEA_MIA(new Edge(SEA, MIA));
  SEA_MIA->setWeight(240);
  Edge* PHX_SEA(new Edge(PHX, SEA));
  PHX_SEA->setWeight(190);
  Edge* PHX_DFW(new Edge(PHX, DFW));
  PHX_DFW->setWeight(140);
  Edge* FLL_EWR(new Edge(FLL, EWR));
  FLL_EWR->setWeight(180);
  Edge* EWR_MCO(new Edge(EWR, MCO));
  EWR_MCO->setWeight(170);
  Edge* EWR_LAX(new Edge(EWR, LAX));
  EWR_LAX->setWeight(360);
  Edge* LAS_LAX(new Edge(LAS, LAX));
  LAS_LAX->setWeight(80);
  Edge* JFK_MCO(new Edge(JFK, MCO));
  JFK_MCO->setWeight(300);
  
  ret->addNode(ATL);
  ret->addNode(DFW);
  ret->addNode(DEN);
  ret->addNode(LAX);
  ret->addNode(JFK);
  ret->addNode(ORD);
  ret->addNode(MCO);
  ret->addNode(LAS);
  ret->addNode(MIA);
  ret->addNode(CLT);
  ret->addNode(SEA);
  ret->addNode(PHX);
  ret->addNode(EWR);
  ret->addNode(FLL);

  ret->addEdge(ATL_FLL);
  ret->addEdge(ATL_MCO);
  ret->addEdge(DFW_ATL);
  ret->addEdge(DFW_DEN);
  ret->addEdge(DEN_LAS);
  ret->addEdge(DEN_PHX);
  ret->addEdge(LAX_MCO);
  ret->addEdge(LAX_MIA);
  //ret->addEdge(JFK_LAX);
  ret->addEdge(JFK_CLT);
  ret->addEdge(JFK_MCO);
  ret->addEdge(ORD_LAX);
  ret->addEdge(ORD_PHX);
  ret->addEdge(MCO_DEN);
  ret->addEdge(MIA_ATL);
  ret->addEdge(MIA_ORD);
  ret->addEdge(CLT_ATL);
  ret->addEdge(CLT_MCO);
  ret->addEdge(SEA_DFW);
  ret->addEdge(SEA_MIA);
  ret->addEdge(PHX_DFW);
  ret->addEdge(PHX_SEA);
  ret->addEdge(EWR_LAX);
  ret->addEdge(EWR_MCO);
  ret->addEdge(FLL_EWR);
  ret->addEdge(LAS_LAX);
  

  return ret;
}

int main(){

    Graph* graph = mkgraph();
    graph->tick("Start");
    Graph* min_tree = graph->mst_kruskal();
    min_tree->tick("Done");

    cout << "MST span = " << min_tree->getSpan() << endl;
    
    return 0;
}

