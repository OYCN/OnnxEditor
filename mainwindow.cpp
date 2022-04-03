#include "mainwindow.h"
#include "graphview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(QSize(800, 600));
    GraphView *g = new GraphView;
    this->setCentralWidget(g);
    g->expand(5);
    g->center();
}

MainWindow::~MainWindow()
{
}

