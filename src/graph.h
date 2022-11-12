#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <cstring>
#include <queue>
#include <string>
#include <vector>
using std::queue;
using std::string;
using std::vector;
#include "_global.h"

using namespace std;

// use for DFS
class eGraph {
  struct Edge {
    int start, end;
  };

 public:
  int n, m;
  vector<Edge> e;
  vector<int> vis;
  vector<string> steps;
  vector<QString> logs;

  eGraph(string s) {
    auto vec = _getNum(s);
    n = vec[0];
    m = vec.size() / 3;
    m <<= 1;
    //    e.push_back({-1, -1});
    vis.resize(n + 1, false);
    for (int i = 1; i < (int)vec.size(); i++) {
      int a = vec[i++], b = vec[i++];
      e.push_back({a, b});
      e.push_back({b, a});
      //      qDebug() << QString("Edge: %1, %2").arg(a).arg(b);
    }
  }

  void printLogs(int i) {
    if (i <= n)
      qDebug() << logs[i];
  }

  void log(int* arr, int sz, QString head) {
    head.append(" = {");
    //
    for (int i = 0; i < sz; i++) {
      head += QString(" %1,").arg(arr[i]);
    }
    logs.push_back(head.left(head.length() - 1) + " }");
    qDebug() << logs.back();
  }

  Step load, recv, his;
  void dfs() {
    load.clear();
    recv.clear();
    his.clear();
    dfs(0);
    //    node.add(n - 1, n - 1, 4);
    steps.push_back(his.get());
  }
  void dfs(int u) {
    vis[u] = true;
    log(vis.data(), n, "DFS: vis");
    int ne;
    load.clear();
    //    qDebug() << "visit " << u;
    his.add(u, u, 4);

    for (int i = 0; i < m; ++i) {
      if (u == e[i].start && !vis[e[i].end]) {
        load.add(u, e[i].end, 2);
        recv.add(u, e[i].end, 1);
      }
    }

    for (int i = 0; i < m; ++i) {
      if (u == e[i].start && !vis[e[i].end])
        ne = e[i].end;
      else
        continue;

      steps.push_back((recv + his).get());

      steps.push_back((recv + his + load).get());
      his.add(u, ne, 3);
      steps.push_back((recv + load + his).get());

      dfs(ne);
    }
  }

  string getSteps() { return _getSteps(steps); }
};

constexpr int MAXN = 20;

// use for Prim and Dijkstra
class MGraph {
  int g[MAXN][MAXN];  //为稠密阵所以用邻接矩阵存储
  int dist[MAXN];     //用于记录每一个点距离第一个点的距离
  int path[MAXN];
  bool st[MAXN];  //用于记录该点的最短距离是否已经确定

  int n, m;

  vector<string> steps;

  vector<QString> logs;

 public:
  MGraph(const string& s) {
    memset(g, 0x3f, sizeof g);  //初始化图 因为是求最短路径
                                //所以每个点初始为无限大
    auto vec = _getNum(s);
    n = vec[0], m = vec.size() / 3;
    for (int i = 1; i < (int)vec.size();) {
      int a = vec[i++], b = vec[i++], c = vec[i++];
      //      qDebug() << QString("Edge: %1, %2, %3").arg(a).arg(b).arg(c);
      g[a + 1][b + 1] = g[b + 1][a + 1] = c;
    }
  }

  void printLogs(int i) {
    if (i <= n)
      qDebug() << logs[i];
  }

  void log(int* arr, int sz, QString head) {
    head.append(" = {");
    //
    for (int i = 1; i <= sz; i++) {
      head += QString(" %1,").arg(arr[i]);
    }
    logs.push_back(head.left(head.length() - 1) + " }");
    qDebug() << logs.back();
  }

  void prim() {
    //初始化距离数组为一个很大的数（10亿左右）
    memset(dist, 0x3f, sizeof(dist));
    memset(path, 0, sizeof(path));
    int res = 0;
    Step load, recv, his, node;
    dist[1] = 0;  //从 1 号节点开始生成
    node.add(0, 0, 4);
    for (int i = 0; i < n; i++) {  //每次循环选出一个点加入到生成树
      int t = -1;
      for (int j = 1; j <= n; j++)  //每个节点一次判断
      {
        if (!st[j] && (t == -1 || dist[j] < dist[t]))
          //如果没有在树中，且到树的距离最短，则选择该点
          t = j;
      }

      //如果孤立点，直返输出不能，然后退出
      if (dist[t] == 0x3f3f3f3f) {
        qDebug() << "Isolated Point!";
        return;
      }

      st[t] = 1;  // 选择该点
      dist[t] = 0;
      node.clear();
      node.add(t - 1, t - 1, 4);

      res += dist[t];
      for (int i = 1; i <= n; i++) {
        //更新生成树外的点到生成树的距离
        if (dist[i] > g[t][i] && !st[i]) {
          //从 t 到节点 i 的距离小于原来距离，则更新。
          dist[i] = g[t][i];  //更新距离
          path[i] = t;  //从 t 到 i 的距离更短，i 的前驱变为 t.
        }
      }
      Step nextPath;
      int now = t, pre = path[t];
      while (pre > 0) {
        nextPath.add(pre - 1, now - 1, 3);  // Path Edges
        now = pre, pre = path[pre];
      }

      steps.push_back((load + his).get());
      his += nextPath;
      steps.push_back((load + his).get());
      his += node;
      steps.push_back((his).get());

      for (int r = 1; r <= n; r++) {
        auto check = [&](int t, int r) -> bool {
          return t != r && g[t][r] < 0x3f3f3f3f;
        };
        if (check(t, r)) {
          load.add(t - 1, r - 1, 2);  // Pre Load Edges
          recv.add(t - 1, r - 1, 1);
        }
      }
      log(dist, n, "Prim: lowCost");
    }
    steps.push_back((recv + his).get());
    //    qDebug() << "MST.len = " << res;
  }

  int dijkstra() {
    memset(dist, 0x3f, sizeof(dist));  //初始化距离  0x3f代表无限大
    memset(path, 0, sizeof(path));

    dist[1] = 0;  //第一个点到自身的距离为0
    Step load, recv, his, node;

    node.add(0, 0, 4);
    for (int i = 0; i < n; i++) {   //有n个点所以要进行n次 迭代
      int t = 0;                    // t存储当前访问的点
      for (int j = 1; j <= n; j++)  //这里的j代表的是从1号点开始
        if (!st[j] && (t == 0 || dist[t] > dist[j])) {
          t = j;
        }

      //依次更新每个点所到相邻的点路径值
      for (int j = 1; j <= n; j++) {
        if (dist[t] + g[t][j] < dist[j]) {
          // Select 1~t + t~j
          path[j] = t;
          dist[j] = dist[t] + g[t][j];
        }
        //        dist[j] = min(dist[j], dist[t] + g[t][j]);
      }

      st[t] = true;
      node.clear();
      node.add(t - 1, t - 1, 4);

      Step nextPath;
      int now = t, pre = path[t];
      while (pre > 0) {
        nextPath.add(pre - 1, now - 1, 3);  // Path Edges
        now = pre, pre = path[pre];
      }
      //      if (i > 0)
      steps.push_back((load + his).get());
      his += nextPath;
      steps.push_back((load + his).get());
      his += node;
      steps.push_back((his).get());

      for (int r = 1; r <= n; r++) {
        auto check = [&](int t, int r) -> bool {
          return t != r && g[t][r] < 0x3f3f3f3f;
        };
        if (check(t, r)) {
          load.add(t - 1, r - 1, 2);  // Pre Load Edges
          recv.add(t - 1, r - 1, 1);
        }
      }
      log(dist, n, "Dijk: dist");
    }

    steps.push_back((recv + his).get());
    if (dist[n] == 0x3f3f3f3f)
      return -1;  //如果第n个点路径为无穷大即不存在最低路径
    return dist[n];
  }

  string getSteps() { return _getSteps(steps); }
};

class AGraph {
  struct Edge {
    int start, end;
  };

 public:
  int n, m;
  vector<Edge> e;
  vector<bool> vis;
  vector<string> steps;
  vector<QString> logs;

  int f[8]{0};
  int g[8]{0};
  int h[8]{1100, 1350, 2450, 1900, 650, 500, 1140, 0};

  AGraph(string s) {
    auto vec = _getNum(s);
    n = vec[0];
    m = vec.size() / 3;
    m <<= 1;
    //    e.push_back({-1, -1});
    vis.resize(n + 1, false);
    for (int i = 1; i < (int)vec.size(); i++) {
      int a = vec[i++], b = vec[i++];
      e.push_back({a, b});
      e.push_back({b, a});
      //      qDebug() << QString("Edge: %1, %2").arg(a).arg(b);
    }
  }

  Step load, recv, his;
  void dfs() {
    load.clear();
    recv.clear();
    his.clear();
    dfs(0);
    steps.push_back(his.get());
  }

  void AStar(int u);

  void printLogs(int i) {
    if (i < (int)logs.size())
      qDebug() << logs[i].toStdString().data();
  }

  void dfs(int u) {
    vis[u] = true;
    int ne;
    load.clear();
    //    qDebug() << "visit " << u;
    his.add(u, u, 4);

    for (int i = 0; i < m; ++i) {
      if (u == e[i].start && !vis[e[i].end]) {
        load.add(u, e[i].end, 2);
        recv.add(u, e[i].end, 1);
      }
    }

    for (int i = 0; i < m; ++i) {
      if (u == e[i].start && !vis[e[i].end])
        ne = e[i].end;
      else
        continue;

      steps.push_back((recv + his).get());

      steps.push_back((recv + his + load).get());
      his.add(u, ne, 3);
      steps.push_back((recv + load + his).get());

      dfs(ne);
    }
  }

  string getSteps() { return _getSteps(steps); }
};

#endif  // GRAPH_H
