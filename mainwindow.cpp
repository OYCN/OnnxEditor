/**
 * @file mainwindow.cpp
 * @brief 
 * @author oPluss (opluss@qq.com)
 * 
 * @copyright Copyright (c) 2022  oPluss
 * 
 * @par Modify log:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2022-04-07 <td>1.0     <td>oPluss     <td>Initial
 * </table>
 */

#include "mainwindow.hpp"

#include "graphview.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->resize(QSize(800, 600));
  GraphView *g = new GraphView;
  this->setCentralWidget(g);
  g->expand(5);
  g->center();
}

MainWindow::~MainWindow() {}
