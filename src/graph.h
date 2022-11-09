#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
using std::vector;

constexpr int MAXV = 100;

struct VNode {
  int type, num;
  double pos_x, pos_y;
};

class Graph {
 protected:
  char** grid;
  vector<VNode> vert;

 public:
  //  Graph() : grid(nullptr) {}
  Graph(int x = MAXV, int y = MAXV);
  // operate plugs
  char& Weight(int x, int y);
  int addVert();
  VNode& Vert(int num);
};

#endif  // GRAPH_H
