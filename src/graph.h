#ifndef GRAPH_H
#define GRAPH_H

#include <queue>
#include <string>
#include <vector>
using std::queue;
using std::string;
using std::vector;
//#include <iostream>
#include "_global.h"

using namespace std;

class eGraph {
  struct Edge {
    int u, v;
  };

 public:
  int n, m;
  vector<Edge> e;
  vector<bool> vis;
  vector<string> steps;

  eGraph(string s) {
    qDebug() << "-------------------------------build eGraph";
    auto vec = getnum(s);
    n = vec[0];
    m = vec.size() / 3;
    //    e.push_back({-1, -1});
    vis.resize(n + 1, false);
    for (int i = 1; i < (int)vec.size(); i++) {
      int a = vec[i++], b = vec[i++];
      e.push_back({a, b});
      //      qDebug() << QString("Edge: %1, %2").arg(a).arg(b);
    }
  }

  void dfs(int u = 0) {
    vis[u] = true;
    int ne;
    //    qDebug() << "visit " << u;
    for (int i = 0; i < m; ++i) {
      if ((u == e[i].u) && !vis[e[i].v])
        ne = e[i].v;
      else if ((u == e[i].v) && !vis[e[i].u])
        ne = e[i].u;
      else
        continue;

      auto patch = QString("1 %1 %2 3").arg(u).arg(ne);
      //      qDebug() << u << ne;
      steps.push_back(patch.toStdString());
      dfs(ne);
    }
  }

  string getSteps() {
    string ret;
    for (int i = 0; i < steps.size(); i++)
      ret += steps[i], ret.push_back('\n');
    return ret;
  }
};

#define MinHeap(T) priority_queue<T, vector<T>, greater<T>>
#define qNode pair<int, int>
class ALGraph {
  struct Edge {
    int u = -1, v = -1, w = -1, next = -1;
  } e[400005];

  int k = 0, n, m, cnt = 0, sum = 0;
  int head[5005]{0}, dis[5005]{0}, vis[5005]{0};
  MinHeap(qNode) q;

 public:
  vector<string> steps;

  ALGraph(string s) {
    qDebug() << "-------------------------------build ALGrap  h";
    auto vec = getnum(s);
    memset(dis, 127, sizeof(dis));
    memset(head, -1, sizeof(head));
    n = vec[0], m = vec.size() / 3;
    for (int i = 1; i < (int)vec.size();) {
      int a = vec[i++], b = vec[i++], c = vec[i++];
      add(a + 1, b + 1, c);
      add(b + 1, a + 1, c);
      //      qDebug() << QString("Edge: %1, %2, %3").arg(a).arg(b).arg(c);
    }
    prim();
    qDebug() << "MST.sum = " << sum;
  }

  void add(int u, int v, int w) {
    e[++k].v = v;
    e[k].u = u;
    e[k].w = w;
    e[k].next = head[u];
    head[u] = k;
  }

  void prim() {
    dis[1] = 0;
    q.push({0, 1});
    QString buf;
    while (!q.empty() && cnt < n) {
      int d = q.top().first, u = q.top().second;
      qDebug() << QString("visit %1->%2").arg(e[u].u - 1).arg(e[u].v - 1);
      buf = QString("1 %1 %2 3 ").arg(e[u].u - 1).arg(e[u].v - 1);
      steps.push_back(buf.toStdString());
      q.pop();
      if (vis[u])
        continue;
      cnt++;
      sum += d;
      vis[u] = 1;
      int stepCnt = 0;
      buf.clear();
      for (int i = head[u]; i != -1; i = e[i].next)
        if (e[i].w < dis[e[i].v]) {
          dis[e[i].v] = e[i].w;
          q.push({dis[e[i].v], e[i].v});
          buf += QString(" %1 %2 2 ").arg(e[i].u - 1).arg(e[i].v - 1);
          //          stepCnt++;`
        }
      if (stepCnt > 0) {
        buf = QString::number(stepCnt) + buf;
        steps.push_back(buf.toStdString());
        qDebug() << buf;
      }
    }
  }

  string getSteps() {
    string ret;
    for (int i = 0; i < steps.size(); i++)
      ret += steps[i], ret.push_back('\n');
    for (string i : steps)
      qDebug() << QString::fromLocal8Bit(i.data());
    return ret;
  }
};

#endif  // GRAPH_H
