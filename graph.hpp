#ifndef TP01_GRAPH_HPP
#define TP01_GRAPH_HPP
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
class Graph {
    int V; // No. of vertices
    std::list<int> *adj; // Pointer to an array containing adjacency lists
    bool isCyclicUtil(int v, bool visited[], bool *rs); // used by isCyclic()
public:
    explicit Graph(int V); // Constructor
    void addEdge(int v, int w); // To add an edge to graph
    bool isCyclic(); // Returns true if there is a cycle in this graph
    void BFS(int s, std::vector<int> &visitedPosts, int layersLimit, Graph *CDGraph);
};
#endif //TP01_GRAPH_HPP
