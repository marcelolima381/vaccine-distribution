#include "graph.hpp"

Graph::Graph(int V) {
  this->V = V;
  adj = new std::list<int>[V];
}

void Graph::addEdge(int v, int w) {
  adj[v].push_back(w); // Add w to v’s list.
}

/*
 * @param s Graph Index
 * @param visitedPosts: visitedPosts vector
 * @param layersLimit Limit of layers that can be reached by any CD
 * @param CDGraph: graph to be covered
 * */
void Graph::BFS(int s, std::vector<int> &visitedPosts, int layersLimit, Graph *CDGraph) {

  // Mark all the vertices as not visited
  bool *visited = new bool[V];
  for (int i = 0; i < V; i++) {
    visited[i] = false;
  }

  // Create a queue for BFS
  std::list<int> queue;

  // Mark the current node as visited and enqueue it
  visited[s] = true;
  queue.push_back(s);

  // 'i' will be used to get all adjacent vertices of a vertex
  std::list<int>::iterator i;
  int lastFromLayer = s, lastOfNextLayer = -1, layerCounter = 0;

  while (!queue.empty()) {
    // Dequeue a vertex from queue
    s = queue.front();
    queue.pop_front();

    // Get all adjacent vertices of the dequeued
    // vertex s. If a adjacent has not been visited,
    // then mark it visited and enqueue it
    for (i = adj[s].begin(); i != adj[s].end(); ++i) { //Adjacent to s from start to finish
      CDGraph->addEdge(s, *i); //Adding the edge (s, i) to the CD graph [i (main)]
      if (!visited[*i]) { //Edge has not yet been visited
        queue.push_back(*i); //FIFO
        visited[*i] = true;
        lastOfNextLayer = *i;
        if (layerCounter < layersLimit) { //Still visiting points
          visitedPosts.push_back(*i);
        }
      }
    }

    if (s == lastFromLayer) { //Mark the layer change
      layerCounter++;
      lastFromLayer = lastOfNextLayer;
    }
  }
}

bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack) {
  if (!visited[v]) {
    // Mark the current node as visited and part of recursion stack
    visited[v] = true;
    recStack[v] = true;

    // Recur for all the vertices adjacent to this vertex
    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
      if (!visited[*i] && isCyclicUtil(*i, visited, recStack)) {
        return true;
      }
      else if (recStack[*i]) {
        return true;
      }
    }

  }
  recStack[v] = false; // Remove the vertex from recursion stack
  return false;
}

/*
 * @return returns true if the graph contains a cycle, else false.
 * */
bool Graph::isCyclic() { //CD * isCyclic (complexity)
  // Mark all the vertices as not visited and not part of recursion stack
  bool *visited = new bool[V];
  bool *recStack = new bool[V];
  for (int i = 0; i < V; i++) {
    visited[i] = false;
    recStack[i] = false;
  }

  /*
   * Call the recursive helper function to detect
   * cycle in different DFS trees
   * */
  for (int i = 0; i < V; i++)
    if (isCyclicUtil(i, visited, recStack)) {
      return true;
    }

  return false;
}