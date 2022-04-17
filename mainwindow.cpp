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

#include <QtWidgets/QFileDialog>

#include "graph/graphview.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mLogger(this), mParser(&mLogger) {
  this->resize(QSize(800, 600));
  GraphView *g = new GraphView;
  this->setCentralWidget(g);
  mScene = g->getScene();

  bool ret = false;

  do {
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Open Onnx"));
    fileDialog->setDirectory("~");
    // fileDialog->setFilter(filter);
    fileDialog->setNameFilters({"Onnx(*.onnx)", "All files(*.*)"});
    if (fileDialog->exec() == QDialog::Accepted) {
      QString path = fileDialog->selectedFiles()[0];
      ret = mParser.open(path.toStdString());
    } else {
      break;
    }
  } while (!ret);

  if (ret) {
    if (!applyByParser()) {
      QMessageBox::critical(this, "Error", "We can't draw this network");
      exit(0);
    }
    mScene->layout();
  }

  g->expand(5);
  g->center();
}

MainWindow::~MainWindow() {}

bool MainWindow::applyByParser() {
  QMap<QString, GraphNode *> map;

  // For Inputs
  qDebug() << "Add Input Node";
  auto inputs = mParser.getInputs();
  for (auto i : inputs) {
    auto n = mScene->addNode("Input");
    // register this
    if (map.contains(i.c_str())) {
      QMessageBox::critical(this, "Error",
                            "Already has input with " + QString(i.c_str()));
      exit(0);
    }
    map[i.c_str()] = n;
  }
  qDebug() << "Add Input Node Done";

  // For Initializers
  qDebug() << "Add Initializers Node";
  auto initializers = mParser.getInitializers();
  for (auto i : initializers) {
    auto n = mScene->addNode("Weight");
    // register this
    if (map.contains(i.c_str())) {
      QMessageBox::critical(this, "Error",
                            "Already has input with " + QString(i.c_str()));
      exit(0);
    }
    map[i.c_str()] = n;
  }
  qDebug() << "Add Initializers Node Done";

  // For Nodes
  qDebug() << "Add Op Node";
  size_t size = mParser.getNodeSize();
  qDebug() << "Size of Node:" << size;
  for (size_t i = 0; i < size; i++) {
    auto node = mParser.getNode(i);
    auto n = mScene->addNode(node.mType.c_str());
    // find inputs
    for (auto o : node.mInputs) {
      if (!map.contains(o.c_str())) {
        QMessageBox::critical(this, "Error",
                              "Con't find data with " + QString(o.c_str()));
        exit(0);
      }
      auto t = map[o.c_str()];
      mScene->addEdge(t, n, "");
    }
    // register outputs
    for (auto o : node.mOutputs) {
      if (map.contains("Output")) {
        QMessageBox::critical(this, "Error",
                              "Already has data with " + QString(o.c_str()));
        exit(0);
      }
      map[o.c_str()] = n;
    }
    // qDebug() << "add" << node.mType.c_str();
  }
  qDebug() << "Add Op Node Done";

  // For Outputs
  qDebug() << "Add Output Node";
  auto outputs = mParser.getOutputs();
  for (auto o : outputs) {
    auto n = mScene->addNode(o.c_str());
    // find inputs
    if (!map.contains(o.c_str())) {
      QMessageBox::critical(this, "Error",
                            "Con't find data with " + QString(o.c_str()));
      exit(0);
    }
    auto t = map[o.c_str()];
    mScene->addEdge(t, n, "");
  }
  qDebug() << "Add Output Node Done";

  return true;
}
