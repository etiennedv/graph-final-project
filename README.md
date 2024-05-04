### Etienne De Villiers
### CSPB - 2270
### Final Project

# Union Find & Kruskal's Algorithm

## Introduction
I used HW - Graphs as the backbone of my project, which also contained some of the utility functions I needed for implementing the Union Find data structure. A lot of the implementations of this data structure I researched did not use nodes but rather integers to denote nodes and integer pairs to represent edges. I can definitely see the benefit of using that approach as using nodes feels a bit more clunky, at least from my perspective, but the node structure also has many benefits of holding valuable meta data for analyses. 

The main additions I added two new code files UnionFind.cpp/ UnionFind.h, and added kruskal's algorithm as a member of the Graph class in the Graph.cpp/ Graph.h files. There are plenty of other little changes and helper functions added throughout Node and Edge but these were minor. I removed the old tests and added a few tests to see if my implementation was giving the proper result.

## Data Structure: Union Find Implementation
The Union Find data structure is a collection of dis jointed non-overlapping sets. This collection of dis jointed sets is useful for keeping track of nodes and detecting cycles within a graph. The Union Find class I implemented contains two maps: One for keeping track of each node and its parent, and one for each node and its rank. When the class is instantiated, the parent map is iniitalized to each node being its own parent, and the rank map is initialized to 0 for each node. One thing to note about the Union Find data structure is that it doesn't actually visually represent the original graph very well.

The Union Find class contains two main member functions. The first, Find_Parent, takes the input node and returns its parent. This function uses path compression to find the root parent of a given node. The root parent will be the node that has itself as a parent. The second function, Union, takes an Edge as input and then checks if the nodes in the pair can be unioned. If they have the same parent, then they cannot be unioned, and this is where a cycle would be detected. If they have different parents, then we look at the rank of each node to determine which subset will be unioned to the other. In my case, the smaller subset is unioned to the larger one. 


## Kruskal's Algorithm
Kruskal's algorithm find the minimum spanning tree of a given graph by utlizing the Union Find data structure and a min heap. To implement kruskal's algorithm, I used a min heap priority queue to hold all the edges in ascending order. The default priority queue is actually a max heap so I had to implement a myComparator class to compare each edge's weight when adding to the queue. From there I created a new instance of Graph that will hold the minimum spanning tree, and then instantiated a Union Find object passing in the vector of all nodes within the Graph. From there a while loop is created that checks if the number of edges in the minimum spanning tree is less than the number of nodes minus 1, since this is how many edges it takes to connect n nodes. Once we have n-1 edges in the spanning tree then all nodes should be connected. Now edges are popped one by one from the min heap and then the nodes in the edges are checked for union, if union returns false, then the edge is not added to the minimum spanning tree. If it is true, then the edge is added and then the next min edge is popped from the queue. Eventually we end up with all the nodes connected in a minimum spanning tree.


## Visualization
Starting with the input graph here with all nodes and edges present with respective weights.
<p align="center">
  <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/f15b58b3-820d-4903-8a4f-a163b6a63be6"/> 
</p>

---

### Step 1:
The empty minimum spanning tree is created, and the first edge is added to the tree. This edge is the top of the min heap, so it has the smallest weight. 
<p align="center">
  <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/a29477fa-d840-48cb-afd5-f9b16a130fcf" /> 
</p>

---

### Step 2:
The second edge is now popped and added to the tree. The parents of these nodes are not the same, so they are unioned.
<p align="center">
  <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/5240154a-47da-4d0d-834d-4a4280c75758" /> 
</p>

---

### Step 3:
Now the third edge is added to the tree. So far all of the edges popped are part of the same subset.
<p align="center">
  <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/d09b7503-ebbb-433c-9be9-ec7308e2928e" /> 
</p>

---

### Step 4:
The fourth edge is popped and this one is now part of a different subset so it is not connected yet. 
<p align="center">
  <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/2e38c34a-86ef-4f0c-811d-2d9ad9b702a1" /> 
</p>

---

### Step 5:
The fifth and final edge is popped and unions the subsets together. 
<p align="center">
  <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/54e797f5-9533-4aef-ae3d-3f0336a58043" /> 
</p>

---

### Result
Here is the original orientation of the input graph with the minimum spanning tree edges in red. 
<p align="center">
  <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/8a866acb-ec73-4365-a200-c909e2303aae" /> 
</p>

---

## Try it!
You can run the main.cpp file in the app folder using "make && ./run_app"

For this graph I created nodes with busy airports in the US using each airports 3 letter code. Then I added some popular destinations out of that airport to other airports in the list, and added weights that denoted flight time. 


<p align="center">
  <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/ad7cd63e-c573-475c-b4b9-a16797b90926" /> 
</p>

---

And here is the minimum spanning tree. When running my implementation of kruskal'a algorithm I seem to be having trouble with larger graphs and not getting the right number of nodes. Here I'm off by one, missing JFK Airport. This mst also has two edges going to PHX, where there should only be one in this case, since the edge is redundant. I'd expect the edge between den->phx should be deleted and the edge from LAX to JFK added since its the only way of getting to JFK, but that shouldn't matter. When DEN and PHX are added, DEN's parent is LAX with rank 2, and PHX's parent is ATL with rank 1. 
<p align="center">
  <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/cd8d71fc-6ce8-4e6b-9fa5-fe0211bb8099" /> 
</p>

---

Something about JFK only having one edge and being off on its own was throwing my algorithm for a loop. I added an edge from JFK to CLT and deleted the problematic edge from DEN to PHX and re-ran kruskal's algorithm.
Here is the starting graph:
<p align="center">
  <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/b80d02a3-b05c-4ff7-8567-f30ceb43b894" /> 
</p>


Rerunning mst_kruskal:
<p align="center">
  <img src="https://github.com/etiennedv/graph-final-project/assets/10566058/a61b595a-516c-41a2-8423-b703b078acba" /> 
</p>
Now there is a proper Minimum Spanning Tree, with all nodes connected and no cycles formed as well. I'm not sure why the edge from DEN to PHX was causing a problem, or why removing it and adding an edge from JFK to CLT fixed it. I will have to do more investigating.

## Conclusion/Reflection
I would really have liked to do more with this project and figure out why my algorithm was not running the way it should have for ALL graphs, but I had very limited time and spent the majority of the project wrestling with setting up a VScode C++ environment locally instead of using jupyter hub and then learning how cmake works so I can actually build the project. The rest of my time was spent trying to figure out the union find data structure and implementing kruskal's algorithm using the node structure of the homework. I have a lot of ideas to improve this project, like instead of creating an entire graph structure for the MST, using the edge colors to represent the MST of the given graph so that it retains the overall layout/structure of the original graph. Overall I think I could have explored using python better at this stage of my C++ experience, but I think I learned a lot of valuable C++ skills here. 






