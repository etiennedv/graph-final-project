# Etienne De Villiers
# CSPB - 2270
# Final Project

### Union Find & Kruskal's Algorithm

## Introduction
I used HW - Graphs as the backbone of my project, which also contained some of the utility functions I needed for implementing the Union Find data structure. A lot of the implementations of this data structure I researched did not use nodes but rather integers to denote nodes and integer pairs to represent edges. I can definitely see the benefit of using that approach as using nodes feels a bit more clunky, at least from my perspective, but the node structure also has many benefits of holding valuable meta data for analyses. 

The main additions I added two new code files UnionFind.cpp/ UnionFind.h, and added kruskal's algorithm as a member of the Graph class in the Graph.cpp/ Graph.h files. There are plenty of other little changes and helper functions added throughout Node and Edge but these were minor. I removed the old tests and added a few tests to see if my implementation was giving the proper result.

## Data Structure: Union Find Implementation
The Union Find data structure is a collection of dis jointed non-overlapping sets. This collection of dis jointed sets is useful for keeping track of nodes and detecting cycles within a graph. The Union Find class I implemented contains two maps: One for keeping track of each node and its parent, and one for each node and its rank. When the class is instantiated, the parent map is iniitalized to each node being its own parent, and the rank map is initialized to 0 for each node. One thing to note about the Union Find data structure is that it doesn't actually visually represent the original graph very well.

The Union Find class contains two main member functions. The first, Find_Parent, takes the input node and returns its parent. This function uses path compression to find the root parent of a given node. The root parent will be the node that has itself as a parent. The second function, Union, takes an Edge as input and then checks if the nodes in the pair can be unioned. If they have the same parent, then they cannot be unioned, and this is where a cycle would be detected. If they have different parents, then we look at the rank of each node to determine which subset will be unioned to the other. In my case, the smaller subset is unioned to the larger one. 


## Kruskal's Algorithm
Kruskal's algorithm find the minimum spanning tree of a given graph by utlizing the Union Find data structure and a min heap. To implement kruskal's algorithm, I used a min heap priority queue to hold all the edges in ascending order. The default priority queue is actually a max heap so I had to implement a myComparator class to compare each edge's weight when adding to the queue. From there I created a new instance of Graph that will hold the minimum spanning tree, and then instantiated a Union Find object passing in the vector of all nodes within the Graph. From there a while loop is created that checks if the number of edges in the minimum spanning tree is less than the number of nodes minus 1, since this is how many edges it takes to connect n nodes. Once we have n-1 edges in the spanning tree then all nodes should be connected. Now edges are popped one by one from the min heap and then the nodes in the edges are checked for union, if union returns false, then the edge is not added to the minimum spanning tree. If it is true, then the edge is added and then the next min edge is popped from the queue. Eventually we end up with all the nodes connected in a minimum spanning tree.

<h3 style="text-align: center;">Starting Graph</h3>

<p align="center">
  <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/f15b58b3-820d-4903-8a4f-a163b6a63be6" /> 
</p>


![graphviz (1)](https://github.com/etiennedv/graph-final-project/assets/10566058/a29477fa-d840-48cb-afd5-f9b16a130fcf)

![graphviz (2)](https://github.com/etiennedv/graph-final-project/assets/10566058/5240154a-47da-4d0d-834d-4a4280c75758)

![graphviz (3)](https://github.com/etiennedv/graph-final-project/assets/10566058/d09b7503-ebbb-433c-9be9-ec7308e2928e)

![graphviz (4)](https://github.com/etiennedv/graph-final-project/assets/10566058/2e38c34a-86ef-4f0c-811d-2d9ad9b702a1)

![graphviz (5)](https://github.com/etiennedv/graph-final-project/assets/10566058/54e797f5-9533-4aef-ae3d-3f0336a58043)

<div style="display:flex">
     <div style="flex:1;padding-right:10px;">
          <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/a29477fa-d840-48cb-afd5-f9b16a130fcf" width="200"/>
     </div>
     <div style="flex:1;padding-left:10px;">
          <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/5240154a-47da-4d0d-834d-4a4280c75758" width="300"/>
     </div>
     <div style="flex:1;padding-left:10px;">
          <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/d09b7503-ebbb-433c-9be9-ec7308e2928e" width="400"/>
     </div>
</div>



