#ifndef HOME_H
#define HOME_H

#include <QElapsedTimer>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <QWidget>
#include "_global.h"
#include "graph.h"
#include "world.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Home;
}
QT_END_NAMESPACE

class Home : public QWidget {
  Q_OBJECT

 public:
  Home(QWidget* parent = nullptr);
  ~Home();
  World *wid_dij, *wid_dfs, *wid_prim, *wid;
  void Setwid(std::string s);
  QPushButton *btn_nxt, *btn_auto, *btn_rand, *btn_samp, *btn_stop, *btn_reset;
  QTimer* timer;
  //  std::string Sample_graph;
  std::string Cur_graph;

  void nextStep();
  void Init_graph();

  // Data
  eGraph* dGraph;
  ALGraph* pGraph;

 private:
  Ui::Home* ui;
};
#endif  // HOME_H
