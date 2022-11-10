#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
using std::vector;
//#include <iostream>
#include "_global.h"

using namespace std;

struct Edge {
  int u, v;
};

class Graph {
 public:
  int n, m;
  vector<Edge> e;
  vector<bool> vis;

  Graph() {
    vis.resize(n + 1, false);
    e.resize(m + 1);
  }

  bool find_edge(int u, int v) {
    for (int i = 1; i <= m; ++i) {
      if (e[i].u == u && e[i].v == v) {
        return true;
      }
    }
    return false;
  }

  void dfs(int u) {
    if (vis[u])
      return;
    vis[u] = true;
    // do sth.
    for (int i = 1; i <= m; ++i) {
      if (e[i].u == u) {
        dfs(e[i].v);
      }
    }
  }
};

// int main() {
//   cin >> n >> m;

//  vis.resize(n + 1, false);
//  e.resize(m + 1);

//  for (int i = 1; i <= m; ++i)
//    cin >> e[i].u >> e[i].v;

//  return 0;
//}

#endif  // GRAPH_H
