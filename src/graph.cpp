#include "graph.h"

Graph::Graph(int x, int y) {
  // init Grid
  grid = new char*[x];
  for (int i = 0; i < y; i++)
    grid[i] = new char[y];
}

char& Graph::Weight(int x, int y) {
  return grid[x][y];
}

int Graph::addVert() {
  vert.push_back(VNode{});
  return vert.size() - 1;
}
