#include "graph.h"

void AGraph::AStar(int u = 0) {
  for (int i = 0; i < 8; i++)
    f[i] = g[i] + h[i];
  qDebug() << QString("AStar run from V[%1]").arg(u);
  Step stp, rcv;
  stp.add(0, 0, 4);
  // stp1
  logs.push_back("Checking V[0].neighbors...");
  steps.push_back(stp.get());
  stp.clear();
  for (int i = 1; i <= 4; i++) {
    stp.add(0, i, 2);
    rcv.add(0, i, 1);
  }
  // stp2
  logs.push_back(
      "v[1]: g[1] = 680, h[1] = 1350, f[1] = 2030\n"
      "v[2]: g[2] = 1380, h[2] = 2450, f[2] = 3830\n"
      "v[3]: g[3] = 730, h[3] = 1900, f[3] = 2630\n"
      "v[4]: g[4] = 530, h[4] = 650, f[4] = 1180\n"
      " -- Least of them is f[4].\n");
  steps.push_back(stp.get());
  stp.clear();
  stp.add(0, 4, 3);
  // stp3
  logs.push_back("Select V[4] as Next Hop.");
  steps.push_back(stp.get());
  stp.clear();
  stp.add(4, 4, 4);
  // stp4
  logs.push_back("Checking V[4].neighbors...");
  steps.push_back(stp.get());
  stp.clear();
  for (int i = 5; i <= 7; i++) {
    stp.add(4, i, 2);
    rcv.add(4, i, 1);
  }
  // stp5
  logs.push_back(
      "v[5]: g[5] = 1350, h[5] = 500, f[5] = 1850\n"
      "v[6]: g[6] = 1100, h[6] = 1140, f[6] = 2240\n"
      "v[7]: g[7] = 1180, h[7] = 0, f[7] = 1180\n"
      " -- Least of them is f[7].\n");
  steps.push_back(stp.get());
  stp.clear();
  stp.add(4, 7, 3);
  // stp6
  logs.push_back("Select V[7] as Next Hop.");
  steps.push_back(stp.get());
  stp.clear();
  stp.add(7, 7, 4);
  // stp7
  logs.push_back(
      "Arriving the End!\n"
      "Path: V[0]->V[4]->V[7]\n");
  steps.push_back(stp.get());
  rcv.add(0, 4, 3);
  rcv.add(4, 7, 3);
  // stp8
  steps.push_back(rcv.get());
}
