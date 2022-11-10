#include "world.h"

World::World(QWidget* parent) : QWidget(parent) {
  pen_B.setColor(Qt::black);
  pen_B.setWidth(2);
  pen_R.setColor(Qt::red);
  pen_R.setWidth(2);
  pen_G.setColor(Qt::green);
  pen_G.setWidth(2);

  std::memset(edge, 0, sizeof(edge));
  std::memset(color_E, 0, sizeof(color_E));
  std::memset(color_N, 0, sizeof(color_N));
  siz_node = siz_step = 0;

  Txt = new QLabel(this);
  Txt->move(0, 300);
  Txt->resize(300, 100);
  Txt->setFont(QFont("Microsoft YaHei", 16, 75));
  Txt->setAlignment(Qt::AlignCenter);
  //  Sample_graph =
  //      "8 0 1 680 0 2 1380 0 3 730 0 4 530 1 2 2600 1 5 960 2 3 2500 3 6 840
  //      4 " "5 820 4 6 570 4 7 650 5 7 500 6 7 1140";
  is_sample = 0;
  resize(300, 400);
  //    repaint();
}

void World::buildgraph(std::string s) {
  std::memset(edge, 0, sizeof(edge));
  std::memset(color_E, 0, sizeof(color_E));
  std::memset(color_N, 0, sizeof(color_N));
  siz_node = siz_step = 0;
  steps.clear();
  std::vector<int> v = getnum(s);
  siz_node = v[0];
  for (int i = 1; i < v.size(); i += 3) {
    edge[v[i]][v[i + 1]] = v[i + 2];
    color_E[v[i]][v[i + 1]] = 1;
    edge[v[i + 1]][v[i]] = v[i + 2];
    color_E[v[i + 1]][v[i]] = 1;
  }
  for (int i = 1; i <= siz_node; i++) {
    color_N[i] = 0;
  }
  if (s == Sample_graph)
    is_sample = 1;
  else
    is_sample = 0;
  update();
}

void World::setStep(std::string s) {
  steps = getnum(s);
  Current_step = steps.begin();
}

void World::nextStep() {
  if (steps.empty() || Current_step == steps.end())
    return;
  //    for (int i=0;i<siz_node;i++) {
  //        for (int j=i+1;j<siz_node;j++)  {
  //            if (color_E[i][j]==3) {
  //                color_E[i][j]=color_E[j][i]=1;
  //            }
  //        }
  //    }
  int n = *Current_step;
  Current_step++;
  while (n--) {
    if (Current_step + 2 > steps.end())
      return;
    int s = *Current_step, t = *(Current_step + 1), type = *(Current_step + 2);
    color_E[s][t] = type;
    color_E[t][s] = type;
    Current_step += 3;
  }

  update();
}

void World::setText(QString s) {
  Txt->setText(s);
}

QPen World::pen(int x) {
  if (x == 2)
    return pen_R;
  if (x == 3)
    return pen_G;
  return pen_B;
}

void World::paintEvent(QPaintEvent* event) {
  int x = 150, y = 150, r = 130;
  int n = siz_node;
  if (n == 0)
    return;
  double angle = 0.0;
  std::vector<QPoint> v;
  if (is_sample) {
    v.push_back(QPoint(150, 170));
    v.push_back(QPoint(240, 160));
    v.push_back(QPoint(150, 270));
    v.push_back(QPoint(30, 190));
    v.push_back(QPoint(130, 100));
    v.push_back(QPoint(230, 80));
    v.push_back(QPoint(50, 110));
    v.push_back(QPoint(150, 30));
    for (int i = 0; i < n; i++) {
      drawNode(v[i], QString::number(i), (!color_N[i]) ? pen_B : pen_R);
    }
  } else
    for (int i = 0; i < n; i++) {
      //        qDebug() <<
      //        QPoint(double(x)+r*cos(angle),double(y)+r*sin(angle));
      v.push_back(
          QPoint(double(x) + r * cos(angle), double(y) + r * sin(angle)));
      drawNode(QPoint(double(x) + r * cos(angle), double(y) + r * sin(angle)),
               QString::number(i), (!color_N[i]) ? pen_B : pen_R);
      angle += 2 * acos(-1) / double(n);
    }
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (color_E[i][j]) {
        drawEdge(v[i], v[j], 10, QString::number(edge[i][j]),
                 pen(color_E[i][j]));
      }
    }
  }
}

void World::drawNode(QPoint t, QString s, QPen pen) {
  QPainter paint(this);
  paint.setPen(pen);
  paint.setRenderHint(QPainter::Antialiasing);
  paint.drawEllipse(t, 10, 10);
  paint.drawText(t + QPoint(-5, 3), s);
}

void World::drawEdge(QPoint t1, QPoint t2, int r, QString s, QPen pen) {
  QPoint tmp = t2 - t1;

  QPainter paint(this);
  paint.setPen(pen);
  paint.setRenderHint(QPainter::Antialiasing);

  paint.drawText((tmp * (1.0 - (siz_node + 1) / 2 / double(siz_node + 1))) + t1,
                 s);

  double angle = atan(fabs((double)tmp.y() / (double)tmp.x()));
  int x = double(r + r / 2) * cos(angle);
  int y = double(r + r / 2) * sin(angle);

  //生成对应边，其中注释内容为箭头标识，可表示有向边
  if (tmp.x() >= 0 && tmp.y() > 0) {
    t1.rx() += x;
    t1.ry() += y;
    t2.rx() -= x;
    t2.ry() -= y;
    paint.drawLine(t1, t2);
    //         paint.drawLine(t2+QPoint(-r*cos(angle-acos(-1)/6),-r*sin(angle-acos(-1)/6)),t2);
    //         paint.drawLine(t2+QPoint(-r*cos(angle+acos(-1)/6),-r*sin(angle+acos(-1)/6)),t2);
  }
  if (tmp.x() < 0 && tmp.y() >= 0) {
    t1.rx() -= x;
    t1.ry() += y;
    t2.rx() += x;
    t2.ry() -= y;
    paint.drawLine(t1, t2);
    //         paint.drawLine(t2+QPoint(+r*cos(angle-acos(-1)/6),-r*sin(angle-acos(-1)/6)),t2);
    //         paint.drawLine(t2+QPoint(+r*cos(angle+acos(-1)/6),-r*sin(angle+acos(-1)/6)),t2);
  }
  if (tmp.x() <= 0 && tmp.y() < 0) {
    t1.rx() -= x;
    t1.ry() -= y;
    t2.rx() += x;
    t2.ry() += y;
    paint.drawLine(t1, t2);
    //        paint.drawLine(t2+QPoint(+r*cos(angle-acos(-1)/6),+r*sin(angle-acos(-1)/6)),t2);
    //        paint.drawLine(t2+QPoint(+r*cos(angle+acos(-1)/6),+r*sin(angle+acos(-1)/6)),t2);
  }
  if (tmp.x() > 0 && tmp.y() <= 0) {
    t1.rx() += x;
    t1.ry() -= y;
    t2.rx() -= x;
    t2.ry() += y;
    paint.drawLine(t1, t2);
    //        paint.drawLine(t2+QPoint(-r*cos(angle-acos(-1)/6),+r*sin(angle-acos(-1)/6)),t2);
    //        paint.drawLine(t2+QPoint(-r*cos(angle+acos(-1)/6),+r*sin(angle+acos(-1)/6)),t2);
  }
  //  qDebug() << tmp / 2 << s;
}
