#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <QDebug>
#include <QString>
#include <algorithm>
#include <string>
#include <vector>
#define def auto
using std::string;
using std::vector;

extern int MAXV, stepCnt;
extern std::string Sample_graph;

vector<int> _getNum(const std::string& s);
string _getSteps(const vector<string>& steps);

struct Step {
  QString out;
  int cnt = 0;

  void add(int a, int b, int c) {
    if (std::min(a, b) < 0)
      return;
    auto patch = QString(" %1 %2 %3 ").arg(a).arg(b).arg(c);
    out.append(patch);
    cnt++;
  }

  string get() {
    QString ret;
    ret = QString::number(cnt) + out;
    return ret.toStdString();
  }

  def operator+(const Step& b)->Step {
    // do nothing.
    return {out + b.out, cnt + b.cnt};
  }

  def operator=(const Step& b)->Step& {
    out = b.out, cnt = b.cnt;
    return *this;
  }

  def operator+=(const Step& b)->Step& {
    out += b.out, cnt += b.cnt;
    return *this;
  }

  void clear() {
    out.clear();
    cnt = 0;
  }
};

#endif  // _GLOBAL_H
