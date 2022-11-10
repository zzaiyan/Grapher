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
  QPen pen_1, pen_2, pen_3;
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
};

#endif  // WORLD_H
