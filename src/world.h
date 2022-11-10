#ifndef WORLD_H
#define WORLD_H

#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QString>
#include <QWidget>
#include <cmath>
#include <cstring>
#include <string>
#include "_global.h"

class World : public QWidget {
  Q_OBJECT
 public:
  explicit World(QWidget* parent = nullptr);

  void buildgraph(std::string);
  void setStep(std::string);
  void nextStep();
  void setText(QString s);
  QPen pen(int x);

  void paintEvent(QPaintEvent* event);
  QPen pen_B, pen_R, pen_G;
  void drawNode(QPoint t, QString s, QPen pen);
  void drawEdge(QPoint t1, QPoint t2, int r, QString s, QPen pen);

  int edge[20][20];
  int color_E[20][20];
  int color_N[20];

  int is_sample;
  std::vector<int> steps;
  std::vector<int>::iterator Current_step;
  QLabel* Txt;

  int siz_node, siz_step;

  static std::vector<int> getnum(std::string s) {
    int x = 0;
    std::vector<int> v;
    for (int i = 0; i < (int)s.length(); i++) {
      if (s[i] >= '0' && s[i] <= '9') {
        while (s[i] >= '0' && s[i] <= '9' && i < (int)s.length())
          x = x * 10 + s[i] - '0', i++;
        v.push_back(x);
        x = 0;
      }
    }
    return v;
  }
};

#endif  // WORLD_H
