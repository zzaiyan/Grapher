#include "home.h"
#include "ui_home.h"

#define ran(x) ((rand() * RAND_MAX % (x) + rand()) % (x))

Home::Home(QWidget* parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  setFixedSize(1000, 600);
  setWindowTitle("Grapher");
  srand(time(NULL));

  timer = new QTimer();
  timer->setInterval(1000 * 0.5);

  Cur_graph = Sample_graph;
  wid_dfs = new World(this);
  wid_dfs->setText("DFS");
  wid_prim = new World(this);
  wid_prim->setText("Prim");
  wid_dij = new World(this);
  wid_dij->setText("Dijkstra");
  wid_dfs->move(20, 0);
  wid_prim->move(350, 0);
  wid_dij->move(680, 0);
  Init_graph();

  btn_rand = new QPushButton(this);
  btn_rand->setText("随机数据");
  btn_rand->resize(100, 50);
  btn_samp = new QPushButton(this);
  btn_samp->setText("样例数据");
  btn_samp->resize(100, 50);
  btn_nxt = new QPushButton(this);
  btn_nxt->setText("单步演示");
  btn_nxt->resize(100, 50);
  btn_auto = new QPushButton(this);
  btn_auto->setText("自动演示");
  btn_auto->resize(100, 50);
  btn_stop = new QPushButton(this);
  btn_stop->setText("停止自动演示");
  btn_stop->resize(100, 50);
  btn_reset = new QPushButton(this);
  btn_reset->setText("重置");
  btn_reset->resize(100, 50);

  btn_samp->move(350, 430);
  btn_rand->move(550, 430);
  btn_reset->move(225, 510);
  btn_nxt->move(225 + 150, 510);
  btn_auto->move(225 + 300, 510);
  btn_stop->move(225 + 450, 510);

  connect(timer, &QTimer::timeout, this, [=]() { nextStep(); });

  connect(btn_samp, &QPushButton::clicked, this, [=]() {
    Cur_graph = Sample_graph;
    Init_graph();
  });

  connect(btn_rand, &QPushButton::clicked, this, [=]() {
    std::string s;
    int n = ran(5) + 5;  //节点个数最小为5，最大为8
    int m = ran(n) + n;  //边数最多为2n-1
    s += std::to_string(n) + " ";
    bool tag[n][n];
    memset(tag, 0, sizeof(tag));
    for (int i = 0; i < n; i++)
      tag[i][i] = 1;
    for (int i = 0; i < m; i++) {
      int x = 0, y = 0, dis = ran(20) + 1;
      while (tag[x][y])
        x = ran(n), y = ran(n);
      s += std::to_string(x) + " " + std::to_string(y) + " " +
           std::to_string(dis) + " ";
    }
    Cur_graph = s;  //更新Cur_graph为新生成的数据
                    //        Cur_graph="5 0 1 1 0 2 1 0 3 1 1 4 1 ";
    Init_graph();
  });

  connect(btn_reset, &QPushButton::clicked, this, [=]() { Init_graph(); });

  connect(btn_nxt, &QPushButton::clicked, this, [=]() {
    nextStep();
    timer->stop();
  });

  connect(btn_auto, &QPushButton::clicked, this, [=]() { timer->start(); });

  connect(btn_stop, &QPushButton::clicked, this, [=]() { timer->stop(); });

  //  qDebug() << this->x() << this->y();
}

Home::~Home() {
  delete ui;
}

void Home::nextStep() {
  wid_dfs->nextStep();
  wid_prim->nextStep();
  wid_dij->nextStep();
}

void Home::Init_graph() {
  wid_dfs->buildgraph(Cur_graph);
  wid_prim->buildgraph(Cur_graph);
  wid_dij->buildgraph(Cur_graph);

  std::string s_dfs, s_prim, s_dij;

  dGraph = new eGraph(Cur_graph);
  pGraph = new MGraph(Cur_graph);
  mGraph = new MGraph(Cur_graph);

  dGraph->dfs();
  s_dfs = dGraph->getSteps();

  pGraph->prim();
  s_prim = pGraph->getSteps();

  mGraph->Dijkstra();
  s_dij = mGraph->getSteps();

  wid_dfs->setStep(s_dfs);  //设置dfs算法步骤信息,即传递对应字符串
  wid_prim->setStep(s_prim);  //设置prim算法步骤信息
  wid_dij->setStep(s_dij);    //设置dijkstra算法步骤信息
  timer->stop();
}
